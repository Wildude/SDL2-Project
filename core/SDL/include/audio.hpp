#pragma once
#include <SDL2/SDL_mixer.h>
//#include <SDL2/SDL.h>
#include <iostream>
//#include <fstream>
//std::ofstream audio_file("aud.log");
class AUDIO
{
    private:
    Mix_Chunk* chunk = NULL;
    public:
    AUDIO(int freq, Uint16 format, int channels, int chunksize);
    AUDIO();
    AUDIO(const std::string& path);
    void load(const char* path);
    void load(const std::string& path);
    int setvol(int vol);
    int play(int chann, int loops = 1);
    int playt(int chann, int time, int loops = 1);
    int halt(int chann);
    ~AUDIO();
};