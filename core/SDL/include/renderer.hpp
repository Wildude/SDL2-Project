#pragma once
#include <iostream>
#include <SDL2/SDL.h>
class RENDERER
{
    SDL_Renderer* renderer;
    SDL_Color col;
    Uint32 flag;
    int index;
    public:
    RENDERER();
    void setflag(Uint32 flag_ = SDL_RENDERER_TARGETTEXTURE);
    void pst();
    int clr();
    SDL_Renderer* getren() const ;
    SDL_Renderer* setren(SDL_Renderer* rend = NULL);
    SDL_Renderer* setRGB(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0);
    int pstcol(SDL_Color* color = NULL);
    int pstcol(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    SDL_Renderer* setcol(SDL_Color& color);
    int set_rencol(SDL_Color*col_p = NULL);
    SDL_Renderer* crt(SDL_Window* window_ = NULL);
    SDL_Renderer* crtren(SDL_Window* window_ = NULL, int index_ = -1, Uint32 flag_ = SDL_RENDERER_ACCELERATED);
    void drawline(const SDL_Point& v1, const SDL_Point& v2);
    void drawrect(const SDL_Rect& cam);
    // filled rectangle and point remaining
};

template <class T> T clamp(T val, T in, T out){
    val = val > out ? out : val < in ? in : val;
    return val;
}
int setRenCol(SDL_Renderer* renderer, const SDL_Color& col);
int setRenCol(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
// color manipulations:
SDL_Color brightenColor(const SDL_Color& color, float intensity = 0.5);
SDL_Color greenToRed(const SDL_Color& color, float t = 1.0);
SDL_Color darken(const SDL_Color& color, float t = 0.5);
SDL_Color addGreyTint(const SDL_Color& color, float t = 0.5);
// Draw thick line between (x1, y1) and (x2, y2)
void DrawThickLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness = 1);
void drawHorizontalLine(SDL_Renderer* renderer, int x1, int x2, int y);

void fillFlatBottomTriangle(SDL_Renderer* renderer, SDL_Point v0, SDL_Point v1, SDL_Point v2);
void fillFlatTopTriangle(SDL_Renderer* renderer, SDL_Point v0, SDL_Point v1, SDL_Point v2);

void fillTriangle(SDL_Renderer* renderer, SDL_Point p0, SDL_Point p1, SDL_Point p2);