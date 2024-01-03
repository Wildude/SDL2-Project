#include "../Files/headers/vector2D.h"
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <vector>
#include <conio.h>
#include <cstring>
template<class T> void vin(T data_entered)
{
    //validation coming soon
}
int main(int argn, char** args)
{
    int sides, sidelength;
    cout<<" Enter number of vertices (sides): ";
    cin>>sides;
    cout<<" Enter sidelength: ";
    cin>>sidelength;
    Vint2* vertices = new Vint2[sides];
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Center finder", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);
    SDL_Texture** points = new SDL_Texture*[sides];
    SDL_Texture** lines = new SDL_Texture*[sides];
    SDL_Rect* prect = new SDL_Rect[sides];
    SDL_Rect* lrect = new SDL_Rect[sides];
    SDL_Texture* cpoint = IMG_LoadTexture(renderer, "../Images/point.jpg");
    if(!cpoint){cout<< " ret: "<<SDL_GetError()<<endl; return 6;}
    TTF_Init();
    SDL_Color red;
    red.r = red.a = 255;
    red.g = red.b = 0;
    SDL_RenderClear(renderer);
    SDL_Event event;
    SDL_Texture* board;
    SDL_Rect brect;
    double angle = 0;
    Vint2 center_v(320, 240);
    for(int i = 0; i < sides; i++)
    {
        lines[i] = points[i] = IMG_LoadTexture(renderer, "../Images/Box.jpg");
        if(!lines[i]){cout<<" line error\n";return 2;}
        if(!points[i]){cout<<" point error\n"; return 3;}
    }
    while(event.type != SDL_QUIT)
    {
        SDL_RenderClear(renderer);
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        //if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
		angle++;
        //if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])if(angle)angle--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])sidelength++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S])sidelength++;
        vertices = n_gonr(center_v, sides, sidelength);
        rotate_r(center_v, vertices, sides, angle);
        Vint2 mousepos;
        char text[15];
        SDL_GetMouseState(&mousepos.getx(), &mousepos.gety());
        if(in_polyB(vertices, mousepos, sides))
		{
			strcpy(text, "mouse Detected");
		}
        else strcpy(text, "no mouse");
        for(int i = 0; i < sides; i++)
        {
            prect[i].x = lrect[i].x = vertices[i].getx();
            prect[i].y = lrect[i].y = vertices[i].gety();
            prect[i].w = prect[i].h = lrect[i].w = lrect[i].h = 1;
            lrect[i].w = (vertices[i] - vertices[i != sides-1 ? i + 1 : 0]).getmag();
            double angle = -1 * angler(vertices[i], vertices[i != sides-1 ? i + 1 : 0]);
            SDL_Point center = {0, 0};
            SDL_RenderCopy(renderer, points[i], NULL, &prect[i]);
            SDL_RenderCopyEx(renderer, lines[i], NULL, &lrect[i], angle, &center, SDL_FLIP_NONE);
        }
        Vint2 center = C_x_y_find(vertices, sides);
        SDL_Rect crect;
        crect.x = center.getx();
        crect.y = center.gety();
        crect.h = crect.w = 1;
        brect = crect;
        SDL_RenderCopy(renderer, cpoint, NULL, &crect);
        board = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(TTF_OpenFont("../Fonts/Rock.ttf", 14), (const char*)text, red));
        TTF_SizeText(TTF_OpenFont("../Fonts/Rock.ttf", 14), (const char*)text, &brect.w, &brect.h);
        SDL_RenderCopy(renderer, board, NULL, &brect);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    getch();
    SDL_Quit();
}
