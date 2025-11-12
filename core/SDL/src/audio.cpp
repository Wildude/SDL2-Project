#include "../include/audio.hpp"
#include <SDL2/SDL.h>
#include <fstream>
//std::ofstream audio_file("aud.log");
AUDIO::AUDIO(int freq, Uint16 format, int channels, int chunksize){
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(freq, format, channels, chunksize);
}
AUDIO::AUDIO(){
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
}
AUDIO::AUDIO(const std::string& path){
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    load(path);
    //allocate_channels(4);
}
void AUDIO::load(const char* path){
    chunk = Mix_LoadWAV(path);
    if(!chunk)std::cout << SDL_GetError() << "\a\n";
}
void AUDIO::load(const std::string& path){
    load(path.c_str());
}
int AUDIO::setvol(int vol){
    return Mix_VolumeChunk(chunk, vol);
}
int AUDIO::play(int chann, int loops ){
    return Mix_PlayChannel(chann, chunk, loops);
}
int AUDIO::playt(int chann, int time, int loops ){
    return Mix_PlayChannelTimed(chann, chunk, loops, time);
}
int AUDIO::halt(int chann){
    return Mix_HaltChannel(chann);
}
AUDIO::~AUDIO(){
    Mix_FreeChunk(chunk);
    Mix_CloseAudio();
}