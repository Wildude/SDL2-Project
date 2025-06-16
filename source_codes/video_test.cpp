#include <iostream>
#include <SDL2/SDL.h>
#include <conio.h>
extern "C" {
#include <ffmpeg/libavformat/avformat.h>
#include <ffmpeg/libavcodec/avcodec.h>
#include <ffmpeg/libavutil/imgutils.h>
#include <ffmpeg/libswscale/swscale.h>
}

int main(int argc, char* argv[]) {
    std::string filename;
    {
        std::string path = "../videos/", file;
        std::cout << " Enter video name: ";
        std::cin >> file;
        filename = path + file;
    }
    avformat_network_init();

    AVFormatContext* formatCtx = NULL;
    if (avformat_open_input(&formatCtx, filename.c_str(), NULL, NULL) != 0) {
        std::cerr << "Could not open video file: " << filename << std::endl;
        return -1;
    }

    if (avformat_find_stream_info(formatCtx, NULL) < 0) {
        std::cerr << "Could not find stream info.\n";
        return -1;
    }

    int videoStreamIndex = -1;
    for (unsigned int i = 0; i < formatCtx->nb_streams; i++) {
        if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }

    if (videoStreamIndex == -1) {
        std::cerr << "No video stream found.\n";
        return -1;
    }

    AVCodecParameters* codecPar = formatCtx->streams[videoStreamIndex]->codecpar;
    const AVCodec* codec = avcodec_find_decoder(codecPar->codec_id);
    if (!codec) {
        std::cerr << "Unsupported codec.\n";
        return -1;
    }

    AVCodecContext* codecCtx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codecCtx, codecPar);
    if (avcodec_open2(codecCtx, codec, NULL) < 0) {
        std::cerr << "Could not open codec.\n";
        return -1;
    }

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("FFmpeg + SDL2 Video Player",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          codecCtx->width, codecCtx->height,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_RGB24,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             codecCtx->width, codecCtx->height);

    AVFrame* frame = av_frame_alloc();
    AVFrame* frameRGB = av_frame_alloc();

    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24,
                                            codecCtx->width,
                                            codecCtx->height, 1);
    uint8_t* buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));
    av_image_fill_arrays(frameRGB->data, frameRGB->linesize, buffer, AV_PIX_FMT_RGB24,
                         codecCtx->width, codecCtx->height, 1);

    SwsContext* swsCtx = sws_getContext(codecCtx->width, codecCtx->height,
                                        codecCtx->pix_fmt,
                                        codecCtx->width, codecCtx->height,
                                        AV_PIX_FMT_RGB24,
                                        SWS_BILINEAR, NULL, NULL, NULL);

    AVPacket packet;
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        if (av_read_frame(formatCtx, &packet) >= 0) {
            if (packet.stream_index == videoStreamIndex) {
                if (avcodec_send_packet(codecCtx, &packet) == 0) {
                    while (avcodec_receive_frame(codecCtx, frame) == 0) {
                        sws_scale(swsCtx, frame->data, frame->linesize,
                                  0, codecCtx->height,
                                  frameRGB->data, frameRGB->linesize);

                        SDL_UpdateTexture(texture, NULL, frameRGB->data[0], frameRGB->linesize[0]);
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, texture, NULL, NULL);
                        SDL_RenderPresent(renderer);

                        SDL_Delay(33);  // ~30 FPS
                    }
                }
            }
            av_packet_unref(&packet);
        } else {
            running = false;  // End of video
        }
    }

    sws_freeContext(swsCtx);
    av_free(buffer);
    av_frame_free(&frameRGB);
    av_frame_free(&frame);
    avcodec_free_context(&codecCtx);
    avformat_close_input(&formatCtx);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
