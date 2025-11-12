#pragma once
#include <SDL2/SDL_ttf.h>
#include <iostream>
class FONT
{
    public:
    FONT();    
    const FONT& operator=(const FONT& f);    
    /* inline */ void delpath();    
    /* inline */ void delfont();
    int setpath(const char* fpath);            // std::cout << " different pathes editing\n";
    FONT(const FONT& f);    
    TTF_Font* getfont() const;
    int getptsize() const;
    const char* getpath() const;
    /* inline */ int TEXT_size(const char* thetext, int* w, int *h) const;
    void setptsize(int pt_size);    
    FONT(const char* fontpath, int pt_size);
    static int INIT();
    bool checkpath();
    bool checkfont();
    void display() const;
    void setStyle(int style);
    int getStyle();

    /*
    Constant	                Effect
    TTF_STYLE_NORMAL	        Default
    TTF_STYLE_BOLD	            Bold text
    TTF_STYLE_ITALIC	        Slanted text
    TTF_STYLE_UNDERLINE	        Underline
    TTF_STYLE_STRIKETHROUGH	    Strike line
    */
    ~FONT();    
    friend std::ostream& operator<<(std::ostream&, const FONT&);
    private:
    TTF_Font* fontdata = NULL; // 4 bytes
    char* path = NULL; // 4 bytes
    int ptsize; // 4 bytes
    // total = 12 bytes
    TTF_Font* setfont(const char* fontpath = "../Fonts/nyala.ttf");
};

//SDL_TTF.h
/* inline */ SDL_Surface* solid_renderText(TTF_Font* font, const char* text, const SDL_Color& fg);
/* inline */ SDL_Surface* shaded_renderText(TTF_Font* font, const char* text, const SDL_Color& fg,
     const SDL_Color& bg);
/* inline */ SDL_Surface* blended_renderText(TTF_Font* font, const char* text, const SDL_Color& fg);
/* inline */ SDL_Surface* LCD_renderText(TTF_Font* font, const char* text, const SDL_Color& fg, 
    const SDL_Color& bg);
SDL_Surface* renderText(TTF_Font* font, const char* text, const SDL_Color& fg, int drawtype = 1);
SDL_Surface* renderText(TTF_Font* font, const char* text, const SDL_Color& fg, 
    const SDL_Color& bg, int drawtype = 2);