#include "../Files/Headers/vector2D.h"
#include <conio.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
using namespace std;
int main(int argn, char** args)
{
    int sides, sidelength;
    cout<<" Enter number of sides: ";
    cin >> sides;
    cout<<" Enter sidelengths: ";
    cin >> sidelength;
    Vint2 center(320, 240);
    int radius = sidelength * (1 / (2 * sinf(3.14 / (float)sides)));
    Vint2* vertices = new Vint2 [sides];
    double cen_angle = (2 * 3.14) / sides;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Polydrawer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    SDL_Texture*** textures = new SDL_Texture** [2];
    textures[0] = new SDL_Texture*[sides];
    textures[1] = new SDL_Texture*[sides];
    SDL_Rect** dsts = new SDL_Rect* [2];
    dsts[0] = new SDL_Rect[sides];
    dsts[1] = new SDL_Rect[sides];
    for(int i = 0; i < sides; i++)vertices[i] = Vint2(center.getx() + radius * cosf(cen_angle * i), center.gety() - radius * sinf(cen_angle * i));
    cout<<" Drawing vertices...\n";
    for(int i = 0; i < sides; i++)
    {
        textures[0][i] = IMG_LoadTexture(renderer, "../Images/point.jpg");
        textures[1][i] = IMG_LoadTexture(renderer, "../Images/point.jpg");
        if(!textures[0][i]){cout<<"err tex1: "<<SDL_GetError()<<endl; return -1;}
        if(!textures[1][i]){cout<<"err tex2: "<<SDL_GetError()<<endl; return -1;}
        SDL_QueryTexture(textures[0][i], NULL, NULL, &dsts[0][i].w, &dsts[0][i].h);
        SDL_QueryTexture(textures[1][i], NULL, NULL, &dsts[1][i].w, &dsts[1][i].h);
        dsts[0][i].x = vertices[i].getx();
        dsts[0][i].y = vertices[i].gety();
        dsts[1][i].x = vertices[i].getx();
        dsts[1][i].y = vertices[i].gety();
        dsts[1][i].w = (vertices[i] - vertices[i != sides-1 ? i + 1 : 0]).getmag();
        SDL_RenderCopy(renderer, textures[0][i], NULL, &dsts[0][i]);
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
    };
    SDL_Point r_center = {0, 0};
    cout<<" Drawing lines...\n";
    for(int i = 0; i < sides;i++)
    {
    	double angle = -1 * angler(vertices[i], vertices[i != sides-1 ? i + 1 : 0]);
    	SDL_RenderCopyEx(renderer, textures[1][i], NULL, &dsts[1][i], angle, &r_center, SDL_FLIP_NONE);
    	SDL_RenderPresent(renderer);
    	SDL_Delay(500);
    }
    getch();
    SDL_Quit();
}