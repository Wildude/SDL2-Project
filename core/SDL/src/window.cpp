#include "../include/window.hpp"
SDL_Renderer* WINDOW::getren() const
{
    return renderer;
}
SDL_Window* WINDOW::getwin() const
{
    return window;
}
WINDOW::~WINDOW()
{
    SDL_DestroyWindow(window);
    if(renderer)SDL_DestroyRenderer(renderer);
}
WINDOW::WINDOW(): title(NULL), x(SDL_WINDOWPOS_CENTERED), y(SDL_WINDOWPOS_CENTERED),
w(640), h(480), flag(SDL_WINDOW_SHOWN){
    INIT();
    renderer = NULL;
}
WINDOW::WINDOW(const char* title_): WINDOW(){
    title = title_;
}
WINDOW::WINDOW(const char* title_, Uint32 flag_): WINDOW(title_){
    flag = flag_;
}
WINDOW::WINDOW(const char* title_, int w_, int h_): WINDOW(title_){
    w = w_; h = h_;
}
WINDOW::WINDOW(const char* title_, int x_, int y_, int w_, int h_, Uint32 flag_) :
title(title_), x(x_), y(y_), w(w_), h(h_), flag(flag_)
{
    INIT();
    renderer = NULL;
}
int WINDOW::getx() const {return x;}
int WINDOW::gety() const {return y;}
int WINDOW::getw() const {return w;}
int WINDOW::geth() const {return h;}
int WINDOW::getcx() {return w/2;}
int WINDOW::getcy() {return h/2;}
SDL_Point WINDOW::getc() {return SDL_Point({w/2, h/2});}
SDL_Point WINDOW::getc() const {return SDL_Point({w/2, h/2});}
std::string WINDOW::gettitle() const {return title;}
inline void WINDOW::pst()
{
    return SDL_RenderPresent(renderer);
}
inline int WINDOW::clr(const SDL_Color& col)
{
    set_rencol(col.r, col.b, col.g, col.a);
    return SDL_RenderClear(renderer);
}
SDL_Renderer* WINDOW::setRGB(Uint8 r , Uint8 g , Uint8 b , Uint8 a )
{
    col.r = r;
    col.g = g;
    col.b = b;
    col.a = a;
    return renderer;
}
int WINDOW::pstcol(SDL_Color* color )
{
    if(!color)return 0;
    return pstcol(color->r, color->g, color->b, color->a);
}
int WINDOW::pstcol(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_Color col = {r, g, b, a};
    int ret = SDL_SetRenderDrawColor(renderer, r, g, b, a);
    clr();
    pst();
    return ret;
}
SDL_Renderer* WINDOW::setcol(const SDL_Color& color)
{
    setRGB(color.r, color.g, color.b, color.a);
    return renderer;
}
int WINDOW::set_rencol(SDL_Color*col_p )
{
    SDL_Color color = (col_p ? *col_p : col);
    return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}
int WINDOW::set_rencol(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    return SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
void WINDOW::set_clrcol(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    col = SDL_Color({r, g, b, a});
}
SDL_Renderer* WINDOW::crtren(SDL_Window* window_ , int index , Uint32 flag )
{
    renderer = SDL_CreateRenderer((window_ ? window_ : window), index, flag);
    return renderer;
}
int WINDOW::INIT()
{
    return (SDL_WasInit(SDL_INIT_VIDEO) ? SDL_WasInit(SDL_INIT_VIDEO) : SDL_Init(SDL_INIT_VIDEO));
}
void WINDOW::setwin(const char* title_ , int x_ , int y_ , int w_ , int h_ , Uint32 flag_ )
{
    title = title_;
    x = x_;
    y = y_;
    w = w_;
    h = h_;
    flag = flag_;
}
int WINDOW::crtB()
{
    crtwin(title, x, y, w, h, flag);
    crtren();
    if(!window || !renderer)return 0;
    else return 1;
}
int WINDOW::crtBn()
{
    crtwin();
    crtren();
    if(!window || !renderer)return 0;
    else return 1;
}
SDL_Window* WINDOW::crtwin(const char* title_ , int x_ , int y_ , int w_ , int h_ , Uint32 flag_ )
{
    window = SDL_CreateWindow((const char*)(title_ ? title_ : title), x_, y_, w_, h_, flag_);
    return window;
}
void WINDOW::setdim(int w_ , int h_ )
{
    w = w_;
    h = h_;
}
void WINDOW::setpos(int x_ , int y_ )
{
    x = x_;
    y = y_;
}
void WINDOW::setflag(Uint32 flag_ )
{
    flag = flag_;
}