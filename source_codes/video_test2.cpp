// Video + Audio Playback with SDL2 and FFmpeg (Non-Deprecated)

extern "C" {
#include <ffmpeg/libavformat/avformat.h>
#include <ffmpeg/libavcodec/avcodec.h>
#include <ffmpeg/libavutil/imgutils.h>
#include <ffmpeg/libavutil/opt.h>
#include <ffmpeg/libavutil/channel_layout.h>
#include <ffmpeg/libswscale/swscale.h>
#include <ffmpeg/libswresample/swresample.h>
}

#include <SDL2/SDL.h>
#include <iostream>

#define SDL_AUDIO_BUFFER_SIZE 1024

struct AudioData {
    uint8_t* pos;
    int len;
};

AudioData audio_data;
AVCodecContext* audio_ctx = NULL;
SDL_AudioDeviceID audio_dev = 0;

void audio_callback(void* userdata, Uint8* stream, int len) {
    if (audio_data.len == 0) {
        SDL_memset(stream, 0, len);
        return;
    }

    len = (len > audio_data.len) ? audio_data.len : len;
    SDL_memcpy(stream, audio_data.pos, len);
    audio_data.pos += len;
    audio_data.len -= len;
}

int SDL_main(int argc, char* argv[]) {
    std::string filename;
    {
        std::string path = "../videos/", file;
        std::cout << " Enter video name: ";
        std::cin >> file;
        filename = path + file;
    }
    avformat_network_init();
    AVFormatContext* fmt_ctx = NULL;
    if (avformat_open_input(&fmt_ctx, filename.c_str(), NULL, NULL) != 0) {
        std::cerr << "Failed to open input file: " << filename << "\n";
        return -1;
    }

    if (avformat_find_stream_info(fmt_ctx, NULL) < 0) {
        std::cerr << "Failed to retrieve input stream information\n";
        return -1;
    }

    int video_stream_idx = -1, audio_stream_idx = -1;
    for (unsigned int i = 0; i < fmt_ctx->nb_streams; i++) {
        if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && video_stream_idx < 0)
            video_stream_idx = i;
        else if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && audio_stream_idx < 0)
            audio_stream_idx = i;
    }

    AVCodecParameters* vparams = fmt_ctx->streams[video_stream_idx]->codecpar;
    const AVCodec* vcodec = avcodec_find_decoder(vparams->codec_id);
    AVCodecContext* vcodec_ctx = avcodec_alloc_context3(vcodec);
    avcodec_parameters_to_context(vcodec_ctx, vparams);
    avcodec_open2(vcodec_ctx, vcodec, NULL);

    AVCodecParameters* aparams = fmt_ctx->streams[audio_stream_idx]->codecpar;
    const AVCodec* acodec = avcodec_find_decoder(aparams->codec_id);
    audio_ctx = avcodec_alloc_context3(acodec);
    avcodec_parameters_to_context(audio_ctx, aparams);
    avcodec_open2(audio_ctx, acodec, NULL);

    SwrContext* swr_ctx = swr_alloc();
    av_opt_set_chlayout(swr_ctx, "in_chlayout", &audio_ctx->ch_layout, 0);
    av_opt_set_chlayout(swr_ctx, "out_chlayout", &audio_ctx->ch_layout, 0);
    av_opt_set_sample_fmt(swr_ctx, "in_sample_fmt", audio_ctx->sample_fmt, 0);
    av_opt_set_sample_fmt(swr_ctx, "out_sample_fmt", AV_SAMPLE_FMT_S16, 0);
    av_opt_set_int(swr_ctx, "in_sample_rate", audio_ctx->sample_rate, 0);
    av_opt_set_int(swr_ctx, "out_sample_rate", audio_ctx->sample_rate, 0);
    swr_init(swr_ctx);

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Window* window = SDL_CreateWindow("FFmpeg Player", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          vcodec_ctx->width, vcodec_ctx->height, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING,
                                             vcodec_ctx->width, vcodec_ctx->height);

    SDL_AudioSpec wanted_spec;
    wanted_spec.freq = audio_ctx->sample_rate;
    wanted_spec.format = AUDIO_S16SYS;
    wanted_spec.channels = audio_ctx->ch_layout.nb_channels;
    wanted_spec.silence = 0;
    wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
    wanted_spec.callback = audio_callback;
    wanted_spec.userdata = NULL;
    audio_dev = SDL_OpenAudioDevice(NULL, 0, &wanted_spec, NULL, 0);
    SDL_PauseAudioDevice(audio_dev, 0);

    AVFrame* frame = av_frame_alloc();
    AVFrame* rgb_frame = av_frame_alloc();
    AVFrame* audio_frame = av_frame_alloc();
    SwsContext* sws_ctx = sws_getContext(vcodec_ctx->width, vcodec_ctx->height, vcodec_ctx->pix_fmt,
                                         vcodec_ctx->width, vcodec_ctx->height, AV_PIX_FMT_YUV420P,
                                         SWS_BILINEAR, NULL, NULL, NULL);

    int num_bytes = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, vcodec_ctx->width, vcodec_ctx->height, 1);
    uint8_t* buffer = (uint8_t*)av_malloc(num_bytes * sizeof(uint8_t));
    av_image_fill_arrays(rgb_frame->data, rgb_frame->linesize, buffer, AV_PIX_FMT_YUV420P,
                         vcodec_ctx->width, vcodec_ctx->height, 1);

    AVPacket* pkt = av_packet_alloc();
    uint8_t* audio_buf = NULL;
    int audio_buf_linesize = 0;
    av_samples_alloc(&audio_buf, &audio_buf_linesize, audio_ctx->ch_layout.nb_channels,
                     192000, AV_SAMPLE_FMT_S16, 0);

    while (av_read_frame(fmt_ctx, pkt) >= 0) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) goto cleanup;

        if (pkt->stream_index == video_stream_idx) {
            avcodec_send_packet(vcodec_ctx, pkt);
            while (avcodec_receive_frame(vcodec_ctx, frame) == 0) {
                sws_scale(sws_ctx, frame->data, frame->linesize, 0, vcodec_ctx->height,
                          rgb_frame->data, rgb_frame->linesize);
                SDL_UpdateYUVTexture(texture, NULL,
                                     rgb_frame->data[0], rgb_frame->linesize[0],
                                     rgb_frame->data[1], rgb_frame->linesize[1],
                                     rgb_frame->data[2], rgb_frame->linesize[2]);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);
            }
        } else if (pkt->stream_index == audio_stream_idx) {
            avcodec_send_packet(audio_ctx, pkt);
            while (avcodec_receive_frame(audio_ctx, audio_frame) == 0) {
                int out_samples = swr_convert(swr_ctx, &audio_buf, 192000,
                                              (const uint8_t**)audio_frame->data, audio_frame->nb_samples);
                int data_size = out_samples * audio_ctx->ch_layout.nb_channels * av_get_bytes_per_sample(AV_SAMPLE_FMT_S16);
                audio_data.pos = audio_buf;
                audio_data.len = data_size;
                while (audio_data.len > 0) SDL_Delay(1);
            }
        }
        av_packet_unref(pkt);
    }

cleanup:
    SDL_CloseAudioDevice(audio_dev);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    av_frame_free(&frame);
    av_frame_free(&rgb_frame);
    av_frame_free(&audio_frame);
    av_packet_free(&pkt);
    avcodec_free_context(&vcodec_ctx);
    avcodec_free_context(&audio_ctx);
    avformat_close_input(&fmt_ctx);
    swr_free(&swr_ctx);
    sws_freeContext(sws_ctx);
    av_free(buffer);
    av_freep(&audio_buf);

    return 0;
}
