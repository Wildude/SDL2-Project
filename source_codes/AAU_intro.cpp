#include "../Files/Headers/Basic.h"
#include <conio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
int main(int argn, char** args)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Event event;
    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_FULLSCREEN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* texture[2];
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    TTF_Init();
    Mix_Chunk* chunk = Mix_LoadWAV("../Audio/Addis_ababa_bete.wav");
    Mix_AllocateChannels(4);
    Mix_PlayChannel(0, chunk, 0);
    TTF_Font* fontdata = TTF_OpenFont("../Fonts/ROCKB.ttf", 20);
    SDL_Color col, col2;
    col.r = 255;
    col.b = 0;
    col.g = 0;
    col.a = 255;
    col2.r = 0;
    col2.g = 100;
    col2.b = 155;
    col2.a = 255;
    SDL_Rect src1, dest1;
    SDL_Rect src, dest;
    dest1.w/=4;
    dest1.h/=4;
    dest.x = 0;
    dest.y = 0;
    src.x = 0;
    src.y = 0;
    int j = 0;
    for(int i = 0; i <= 2280; i += 1)
    {
	int seconds = (2280-i) / 100;
	int mseconds = ((2280-i)/10) % 10;
	TTF_SizeText(fontdata, (strmap::to_str(seconds) + ":" + strmap::to_str(mseconds)).c_str(), &src.w, &src.h);
        SDL_Surface* surface = TTF_RenderText_Blended(fontdata, 
	(strmap::to_str(seconds) + ":" + strmap::to_str(mseconds)).c_str(), (i > 1160 && i < 1600 ? col2 : col));
        texture[1] = SDL_CreateTextureFromSurface(renderer, surface);
        dest.w = src.w;
        dest.h = src.h;
        SDL_PollEvent(&event);
        if(event.key.keysym.scancode == SDL_SCANCODE_UP)dest.y-=10;
        if(event.key.keysym.scancode == SDL_SCANCODE_DOWN)dest.y+=10;
        if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT)dest.x+=10;
        if(event.key.keysym.scancode == SDL_SCANCODE_LEFT)dest.x-=10;
        if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)break;
        if(event.key.keysym.scancode == SDL_SCANCODE_W)dest1.y-=10;
        if(event.key.keysym.scancode == SDL_SCANCODE_A)dest1.x-=10;
        if(event.key.keysym.scancode == SDL_SCANCODE_S)dest1.y+=10;
        if(event.key.keysym.scancode == SDL_SCANCODE_D)dest1.x+=10;
	if(i < 1800)texture[0] = IMG_LoadTexture(renderer, "../Images/AAU.png");
	else {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		texture[0] = IMG_LoadTexture(renderer, "../Images/CS.jpg");
		j = (i == 1801 ? 0 : j);
		}
	SDL_QueryTexture(texture[0], NULL, NULL, &dest1.w, &dest1.h);
	dest1.w += 1 * j;
        dest1.h += 1 * j;
	if(i >= 600 || !i){
		if(i > 600)j++;
        	dest1.x = 320 - (dest1.w/2);
	        dest1.y = 240 - (dest1.h/2);
	}
        SDL_RenderCopy(renderer, texture[0], NULL, &dest1);
        SDL_RenderCopy(renderer, texture[1], &src, &dest);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(10);
	if(event.key.keysym.scancode == SDL_SCANCODE_SPACE){
		getch();
	        SDL_PollEvent(&event);
	}
    }
    TTF_CloseFont(fontdata);
    TTF_Quit();
    SDL_Quit();
}