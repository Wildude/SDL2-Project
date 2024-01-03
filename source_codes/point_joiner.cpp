#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include "../Files/Headers/vector2D.h"
#include <SDL2/SDL_ttf.h>
int main(int arn, char** args)
{
    Vint2 v1, v2;
    cout<<" Enter two vectors:\n";
    cout<<" V1(x,y): ";
    cin>>v1;
    cout<<" V2(x,y): ";
    cin>>v2;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("drawer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Texture* texture[2] = {IMG_LoadTexture(renderer, "../Images/point.jpg"), IMG_LoadTexture(renderer, "../Images/point.jpg")};
    SDL_Color col1, col2;
    col1.r = col2.b = 200;
    col1.b = col1.g = col2.r = col2.g = 0;
    col1.a = col2.a = 200;
    SDL_Texture* board[2] = {SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(TTF_OpenFont("../Fonts/ROCK.ttf", 12), "point 1", col1)), SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(TTF_OpenFont("../Fonts/ROCK.ttf", 12), "point 2", col2))};
    if(!board[0]||!board[1])
    {
        cout<<SDL_GetError();
        return -1;
    }
    SDL_Rect bdest[2];
    TTF_SizeText(TTF_OpenFont("../Fonts/Rock.ttf", 12), "point 1", &bdest[0].w, &bdest[0].h);
    TTF_SizeText(TTF_OpenFont("../Fonts/Rock.ttf", 12), "point 2", &bdest[1].w, &bdest[1].h);
    SDL_Rect dest[2];
    SDL_QueryTexture(texture[0], NULL, NULL, &dest[0].w, &dest[0].h);
    SDL_QueryTexture(texture[1], NULL, NULL, &dest[1].w, &dest[1].h);
    SDL_Event event;
    SDL_Texture* liner = IMG_LoadTexture(renderer, "../Images/point.jpg");
    if(!liner)
    {
        cout<<" liner error: "<<SDL_GetError()<<endl;
        return -1;
    }
    SDL_Color coln;
    coln.r = coln.b = 0;
    coln.g = coln.a = 200;
    SDL_Texture* notice = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(TTF_OpenFont("../Fonts/Rock.ttf", 14), "Line drawn", coln));
    if(!notice)
    {
        cout<<" notice error: "<<SDL_GetError()<<endl;
        return -1;
    }
    SDL_Rect destl, destn;
    TTF_SizeText(TTF_OpenFont("../Fonts/Rock.ttf", 14), "Line drawn", &destn.w, &destn.h);
    destn.x = 600 - destn.w;
    destn.y = 100;
    while(event.type != SDL_QUIT)
    {
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.button == 1)
            {
                v1.getx() = event.motion.x;
                v1.gety() = event.motion.y;
            }
            if(event.button.button == 3)
            {
                v2.getx() = event.motion.x;
                v2.gety() = event.motion.y;
            }
        }
        double angle = -1 * angler(v1, v2);
        //if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])angle++;
        //if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])angle--;
        destl.x = v1.getx();
        destl.y = v1.gety();
        destl.w = (v1 - v2).getmag();
        destl.h = 1;
        dest[0].x = bdest[0].x = v1.getx();
        dest[0].y = bdest[0].y = v1.gety();
        dest[1].x = bdest[1].x = v2.getx();
        dest[1].y = bdest[1].y = v2.gety();
        SDL_RenderCopy(renderer, texture[0], NULL, &dest[0]);
        SDL_RenderCopy(renderer, board[0], NULL, &bdest[0]);
        SDL_RenderCopy(renderer, texture[1], NULL, &dest[1]);
        SDL_RenderCopy(renderer, board[1], NULL, &bdest[1]);
        SDL_Point center = {0, 0};
        SDL_RenderCopyEx(renderer, liner, NULL, &destl, angle, &center, SDL_FLIP_NONE);
        static bool toogle = false;
        if(event.type == SDL_KEYDOWN)toogle = (!toogle);
        if(toogle)SDL_RenderCopy(renderer, notice, NULL, &destn);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(10);
    }
    TTF_Quit();
    SDL_Quit();
}
