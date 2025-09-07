#pragma once
#include <SDL2/SDL.h>
#include <iostream>
class WINDOW
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    const char* title;
    int x, y, w, h;
    Uint32 flag;
    SDL_RendererFlip flip;
    SDL_Color col = {0, 0, 0, 0};
    public:
    SDL_Renderer* getren() const;
    SDL_Window* getwin() const;
    ~WINDOW();
    WINDOW();
    WINDOW(const char* title_);
    WINDOW(const char* title_, Uint32 flag_);
    WINDOW(const char* title_, int w_, int h_);
    WINDOW(const char* title_, int x_, int y_, int w_, int h_, Uint32 flag_);
    int getx() const ;
    int gety() const ;
    int getw() const ;
    int geth() const ;
    int getcx();
    int getcy();
    SDL_Point getc();
    SDL_Point getc() const ;
    std::string gettitle() const ;
    /* inline */ void pst();
    /* inline */ int clr(const SDL_Color& col = {255, 255, 255, 255});
    SDL_Renderer* setRGB(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0);
    int pstcol(SDL_Color* color = NULL);
    int pstcol(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    SDL_Renderer* setcol(const SDL_Color& color);
    int set_rencol(SDL_Color*col_p = NULL);
    int set_rencol(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void set_clrcol(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    SDL_Renderer* crtren(SDL_Window* window_ = NULL, int index = -1, Uint32 flag = SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    static int INIT();
    void setwin(const char* title_ = NULL, int x_ = SDL_WINDOWPOS_CENTERED, int y_ = SDL_WINDOWPOS_CENTERED, int w_ = 640, int h_ = 480, Uint32 flag_ = SDL_WINDOW_SHOWN);
    int crtB();
    int crtBn();
    SDL_Window* crtwin(const char* title_ = NULL, int x_ = SDL_WINDOWPOS_CENTERED, int y_ = SDL_WINDOWPOS_CENTERED, int w_ = 640, int h_ = 480, Uint32 flag_ = SDL_WINDOW_SHOWN);
    void setdim(int w_ = 640, int h_ = 480);
    void setpos(int x_ = SDL_WINDOWPOS_CENTERED, int y_ = SDL_WINDOWPOS_CENTERED);
    void setflag(Uint32 flag_ = SDL_WINDOW_SHOWN);
};