#pragma once
#include "font.hpp"
#include <iostream>
//#include <fstream>
//const std::string filepath = "../files/";
//const std::string textbox_path = "tbox.log";
//std::ofstream textbox_file;
class TextBox{
    private:
    SDL_Rect box; // 16 bytes
    SDL_Color col1, col2; // 2 * 4 bytes
    std::string text; // 24 bytes
    FONT font; // 12 bytes
    // total = 66 bytes
    void setbox(int x, int y, int w, int h);
    public:
    TextBox();
    void checkfile();
    SDL_Surface* solid_render(const char* text_ = NULL, SDL_Color* col = NULL);
    SDL_Surface* shaded_render(const char* text_ = NULL, SDL_Color* cola = NULL, SDL_Color* colb = NULL);
    SDL_Surface* blended_render(const char* text_ = NULL, SDL_Color* col = NULL);
    SDL_Surface* LCD_render(const char* text_ = NULL, SDL_Color* cola = NULL, SDL_Color* colb = NULL);
    SDL_Surface* blended_render_utf8(const char* text_ = NULL, SDL_Color* col = NULL);
    SDL_Surface* blended_render_unicode(const char* text_ = NULL, SDL_Color* col = NULL);
    TextBox(const std::string& text_, int x, int y, int w, int h, const FONT& font_, SDL_Color* cola = NULL, SDL_Color* colb = NULL);
    TextBox(const std::string& text_, const FONT& font_);
    TextBox(const char* path, int ptsize = 12);
    void setcol1(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void setcol2();
    void setcol2(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void setfont(const FONT& font_);
    void settext(const char* text_);
    void settext(const std::string& text_);
    void setboxpos(int x, int y);
    void draw(SDL_Renderer* rend, SDL_Texture*& board, short drawtype = 2);
    void printbox();
    const SDL_Rect& getBoxc() const;
    const FONT& getFontc() const;
    const SDL_Color& getCol1c() const;
    const SDL_Color& getCol2c() const;
    SDL_Rect& getBox();
    FONT& getFont();
    SDL_Color& getCol1();
    SDL_Color& getCol2();
    // pointers
    SDL_Rect* getBoxP();
    FONT* getFontP();
    SDL_Color* getCol1P();
    SDL_Color* getCol2P();
    const char* getText() const;
    std::string& getTextRef();
    ~TextBox();
    friend std::ostream& operator<<(std::ostream&, const TextBox&);
};