#pragma once
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
//#include <cstring>
//std::ofstream texture_file("texfile.log");
class Texture2D
{
    SDL_Texture* texture = NULL; // 4 bytes (pointer)
    // SDL_Renderer* renderer; // 4 bytes (pointer) // x
    SDL_Rect src = {0, 0, 0, 0}; // 16 bytes (4 * 4 int) // x
    SDL_FRect dst = {0, 0, 0, 0}; // 16 bytes (4 * 4 float) //x
    SDL_FPoint center = {0, 0}; // 8 bytes (4 + 4 float) //x
    // SDL_RendererFlip flip = SDL_FLIP_NONE; // 4 bytes (optional)
    char* path = NULL;
    // double angle = 0; // 8 bytes
    // total = 
    public:
    Texture2D();
    Texture2D(const Texture2D& t); // copy constructor
    void copy(const Texture2D& t, SDL_Renderer* rend);
    Texture2D(const char* filepath, SDL_Renderer* ren);
    const Texture2D& operator=(const Texture2D& t);
    Texture2D(SDL_Surface* surf, SDL_Renderer* rend);
    SDL_Renderer* crtren(SDL_Window* win = NULL, int index = -1, Uint32 flag = SDL_RENDERER_ACCELERATED);
    SDL_Renderer* getren() const;
    void setangle(double angle_);
    double getangle();
    void displayf(std::ofstream& out);
    void display(std::ostream& os = std::cout);
    const SDL_FPoint& getcenter();
    SDL_Texture* gettexture();
    ~Texture2D();
    void setflip(const SDL_RendererFlip& flag_);
    const char* setpath(const char* fpath);
    const char* getpath();
    static int INIT();
    const SDL_Rect& set_srcpos(int x = 0, int y = 0);
    const SDL_Rect& set_srcdim(int w, int h);
    const SDL_FRect& set_dstpos(float x = 0, float y = 0);
    SDL_FPoint get_cenpos();
    const SDL_FRect& set_cenpos(float x, float y);
    const SDL_FRect& set_dstdim(int w = 0, int h = 0);
    void magnify(float w = 1, float h = -1);
    const SDL_Rect& set_src(int w, int h, float x = -1, float y = -1);
    const SDL_FRect& set_dst(int w, int h, float x = -1, float y = -1);
    const SDL_Rect& set_src(const SDL_Rect& src_);
    const SDL_FRect& set_dst(const SDL_FRect& dst_);
    SDL_FRect& getdst(); // const;
    SDL_Rect& getsrc(); // const;
    const SDL_FRect& getdst() const;
    const SDL_Rect& getsrc() const;
    SDL_Rect retquery(); // no optimization;
    const SDL_FPoint& setcenter(float x, float y);
    const SDL_FPoint& setcenter();
    int query(int* w = NULL, int * h = NULL);
    int queryR(SDL_Rect* src_ = NULL);
    void delTex();
    SDL_Texture* load(const char* filepath, SDL_Renderer* rend);
    SDL_Texture* surfcpy(SDL_Surface*& surf, SDL_Renderer* rend);
    int rencpy(SDL_Renderer* rend, SDL_FRect* dst_ = NULL, SDL_Rect* src_ = NULL, SDL_RendererFlip flag = SDL_FLIP_NONE, SDL_FPoint* center_ = NULL, double angle = 0);
    int queryF();
    int queryC();
    int queryN();
    static int drawRect(const SDL_Rect& rect, SDL_Renderer* rend, int ptsize = 1);
    static int drawRectP(const SDL_Rect& rect, SDL_Renderer* rend, int ptsize = 1);
    // don't use
    int drawPX(SDL_Renderer* rend, SDL_FRect* rect = NULL, float scale = 0.5);
    int drawOF(SDL_Renderer* rend, SDL_FRect* rect = NULL, float scale = 1, double angle = 0);
    int drawC(SDL_Renderer* rend, SDL_FRect* rect = NULL, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int drawO(SDL_Renderer* rend, SDL_FRect* rect = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int drawI(const char* filepath, SDL_Renderer* rend, bool clrer = 1, SDL_FRect* rect = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int draw(SDL_Renderer* rend, SDL_FRect* rect = NULL, bool clrer = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int drawRect(SDL_Rect rect);
};
// total = 60 bytes (without optional members)
class SDLImage{
    SDL_Texture* texture;
    int w, h;
    inline void delTex(){
        if(texture){
            SDL_DestroyTexture(texture);
            texture = NULL;
        }
    }
    public:
    SDLImage();
    SDLImage(const char*, SDL_Renderer*);
    SDLImage(SDL_Texture*);
    SDLImage(const SDLImage&);
    SDLImage& operator=(const SDLImage&);
    void load(const char*, SDL_Renderer*);
    void load(SDL_Texture*);
    SDL_Texture* gettex() const;
    int query(int&, int&) const;
    int queryF();
    void draw(const SDL_Rect&, const SDL_Rect&, SDL_Renderer*);
    void drawSRC(const SDL_Rect&, SDL_Renderer*);
    void drawDST(const SDL_Rect&, SDL_Renderer*);
    void drawSRCpos(const SDL_Point&, SDL_Renderer*);
    void drawDSTpos(const SDL_Point&, SDL_Renderer*);
    void drawSRCdim(const SDL_Point&, SDL_Renderer*);
    void drawDSTdim(const SDL_Point&, SDL_Renderer*);
    void drawSRCp(int, int, SDL_Renderer*);
    void drawDSTp(int, int, SDL_Renderer*);
    void drawSRCd(int, int, SDL_Renderer*);
    void drawDSTd(int, int, SDL_Renderer*);
    void drawSRCpd(int, int, int, int, SDL_Renderer*);
    void drawDSTpd(int, int, int, int, SDL_Renderer*);
    void draw(SDL_Renderer*);
    ~SDLImage();
    friend class LinearSprite;
};