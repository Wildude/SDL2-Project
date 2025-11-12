#pragma once
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
//#include <cstring>
//std::ofstream texture_file("texfile.log");
class Texture2D
{
    SDL_Texture* texture;
    SDL_Rect src;
    SDL_Rect dst;
    SDL_Point center;
    SDL_RendererFlip flip;
    char* path;
    double angle;
    // total = 
    public:
    Texture2D();
    Texture2D(const Texture2D& t); // copy constructor
    void copy(const Texture2D& t, SDL_Renderer* rend);
    Texture2D(const char* filepath, SDL_Renderer* ren);
    const Texture2D& operator=(const Texture2D& t);
    Texture2D(SDL_Surface* surf, SDL_Renderer* rend);
    void setangle(double angle);
    double getangle() const;
    double& getangle();
    void setcenter(const SDL_Point&);
    void setcenter(int x, int y);
    void setcenter();
    const SDL_Point& getcenter() const;
    SDL_Point& getcenter();
    void displayf(std::ofstream& out);
    void display(std::ostream& os = std::cout);
    SDL_Texture* gettexture();
    ~Texture2D();
    void setflip(SDL_RendererFlip flag_);
    void toogleflipH();
    void toogleflipV();
    SDL_RendererFlip getflip() const;
    const char* setpath(const char* fpath);
    const char* getpath();
    static int INIT();
    const SDL_Rect& set_srcpos(int x = 0, int y = 0);
    const SDL_Rect& set_srcdim(int w, int h);
    const SDL_Rect& set_dstpos(float x = 0, float y = 0);
    SDL_Point get_cenpos();
    const SDL_Rect& set_cenpos(float x, float y);
    const SDL_Rect& set_dstdim(int w = 0, int h = 0);
    void magnify(float w = 1, float h = -1);
    const SDL_Rect& set_src(int w, int h, float x = -1, float y = -1);
    const SDL_Rect& set_dst(int w, int h, float x = -1, float y = -1);
    const SDL_Rect& set_src(const SDL_Rect& src_);
    const SDL_Rect& set_dst(const SDL_Rect& dst_);
    SDL_Rect& getdst(); // const;
    SDL_Rect& getsrc(); // const;
    const SDL_Rect& getdst() const;
    const SDL_Rect& getsrc() const;
    int query(int* w = NULL, int * h = NULL);
    int queryR(SDL_Rect& src_);
    void delTex();
    SDL_Texture* load(const char* filepath, SDL_Renderer* rend);
    SDL_Texture* surfcpy(SDL_Surface*& surf, SDL_Renderer* rend);
    int rencpy(SDL_Renderer* rend, SDL_Rect* dst_, SDL_Rect* src_, SDL_RendererFlip flag, SDL_Point* center_, double angle);
    int queryF();
    int queryC();
    static int drawRect(const SDL_Rect& rect, SDL_Renderer* rend, int ptsize = 1);
    static int drawRectP(const SDL_Rect& rect, SDL_Renderer* rend, int ptsize = 1);
    // don't use
    int draw(SDL_Renderer* rend);
    int drawPX(SDL_Renderer* rend, SDL_Rect* rect, float scale);
    int drawOF(SDL_Renderer* rend, SDL_Rect* rect, float scale, double angle);
    int drawC(SDL_Renderer* rend, SDL_Rect* rect, double angle, SDL_RendererFlip flip);
    int drawO(SDL_Renderer* rend, SDL_Rect* rect, SDL_RendererFlip flip);
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