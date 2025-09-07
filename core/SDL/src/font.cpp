#include "../include/font.hpp"
#include <cstring>
#include <fstream>
std::ofstream font_file("fontfile.log");
#define DEF_FONT "../Fonts/nyala.ttf"
#define CHANGE_DEF_FONT(FONT_X) DEF_FONT = FONT_X
//static const string DEFONT = "../Fonts/nyala.ttf";    
FONT::FONT(){
    // std::cout<<" constructor called for font\n";
    INIT();
    ptsize = 12;
}
const FONT& FONT::operator=(const FONT& f)
{
    // std::cout<<" assignment called for font\n";
    if(this == &f)return *this;
    int result = setpath(f.path);
    if(result == 0 && ptsize != f.ptsize){
        // std::cout << "\n pt assigned";
        ptsize = f.ptsize;
        setfont(path);
    }
    else if(result == 1){
        ptsize = f.ptsize;
        setfont(path);
    }
    // std::cout<<"\n ptsize: " << ptsize << std::endl;
    // std::cout<<" path: " << (path ? path : "NULL") << std::endl;
    return *this;
}
void FONT::delpath(){
    if(path)delete[] path;
    path = NULL;
}
void FONT::delfont(){
    if(fontdata){
        TTF_CloseFont(fontdata);
        fontdata = NULL;
    }
}
int FONT::setpath(const char* fpath){
    // std::cout << " setting path: \n";
    if(fpath){
        if(path && strcmp(fpath, path) == 0){
            // std::cout << " same pathes, quiting\n";
            return 0;
        }
        // std::cout << " different pathes editing\n";
        if(path)delete[] path;
        path = new char[strlen(fpath) + 1];
        strcpy(path, fpath);       
        return 1;
    }
    else{
        // std::cout << " new path empty, deleting path\n";
        if(path)delete[] path;
        path = NULL;
        delfont();
        return -1;
    }
}
FONT::FONT(const FONT& f)
{
    *this = f;
}
FONT::FONT(const FONT& f, int style)
{
    *this = f;
    setStyle(style);
}
TTF_Font* FONT::getfont() const
{
    TTF_Font* font = fontdata;
    return font;
}
int FONT::getptsize() const
{
    return ptsize;
}
const char* FONT::getpath() const{
    return path;
}
int FONT::TEXT_size(const char* thetext, int* w, int *h) const
{
    return TTF_SizeText(getfont(), thetext, w, h);
}
void FONT::setptsize(int pt_size) {
    ptsize = pt_size;
}
FONT::FONT(const char* fontpath, int pt_size): FONT()
{
    setpath(fontpath);
    setptsize(pt_size);
    setfont(path);
}
int FONT::INIT()
{
    return (TTF_WasInit() ? TTF_WasInit() : TTF_Init());
}
bool FONT::checkpath(){
    font_file << " checking font path: ";
    if(!path){
        font_file << "fontpath is NULL\n";
        delfont();
        return false;
    }
    font_file << " good\n";
    return true;
}
bool FONT::checkfont(){
    font_file << " checking font: ";
    if(!fontdata){
        font_file << "fontdata is NULL\n";
        delpath();
        return false;
    }
    font_file << " good\n";
    return true;
}
void FONT::display() const{
    std::cout << " checkfont: " << (fontdata != NULL ? "true\n" : "false\n");
    std::cout << " ptsize: " << ptsize << std::endl;
    std::cout << " path: " << path << std::endl;
}
void FONT::setStyle(int style){
    TTF_SetFontStyle(fontdata, style);
}
int FONT::getStyle() {
    int style = TTF_GetFontStyle(fontdata);
    std::cout << " style:";
    if (style == TTF_STYLE_NORMAL) std::cout << " NORMAL";
    else {
        if (style & TTF_STYLE_BOLD) std::cout << " BOLD";
        if (style & TTF_STYLE_ITALIC) std::cout << " ITALIC";
        if (style & TTF_STYLE_UNDERLINE) std::cout << " UNDERLINE";
        if (style & TTF_STYLE_STRIKETHROUGH) std::cout << " STRIKETHROUGH";
    }
    std::cout << "\n";
    return style;
}

/*
Constant	                Effect
TTF_STYLE_NORMAL	        Default
TTF_STYLE_BOLD	            Bold text
TTF_STYLE_ITALIC	        Slanted text
TTF_STYLE_UNDERLINE	        Underline
TTF_STYLE_STRIKETHROUGH	    Strike line
*/
FONT::~FONT()
{
    font_file.close();
    TTF_CloseFont(fontdata);
    delete[] path;
}
TTF_Font* FONT::setfont(const char* fontpath )
{
    // std::cout<<" setting font: "<<fontpath<<" with ptsize: "<< ptsize <<std::endl;
    delfont();
    fontdata = TTF_OpenFont(fontpath, ptsize);
    if(!fontdata){
        std::cout <<" font loading error: "<<SDL_GetError()<<std::endl; 
        font_file << " font loading error: " << SDL_GetError() << std::endl;
        
        return NULL;
    }
    return fontdata;
}
std::ostream& operator<<(std::ostream& os, const FONT& font){
    os << '<' << font.getpath() << ">(x" << font.getptsize() << ')';
    return os;
}
/* inline */ SDL_Surface* solid_renderText(TTF_Font* font, const char* text, const SDL_Color& fg){
    return TTF_RenderText_Solid(font, text, fg);
}
/* inline */ SDL_Surface* shaded_renderText(TTF_Font* font, const char* text, const SDL_Color& fg, const SDL_Color& bg){
    return TTF_RenderText_Shaded(font, text, fg, bg);
}
/* inline */ SDL_Surface* blended_renderText(TTF_Font* font, const char* text, const SDL_Color& fg){
    return TTF_RenderText_Blended(font, text, fg);
}
/* inline */ SDL_Surface* LCD_renderText(TTF_Font* font, const char* text, const SDL_Color& fg, const SDL_Color& bg){
    return TTF_RenderText_LCD(font, text, fg, bg);
}
SDL_Surface* renderText(TTF_Font* font, const char* text, const SDL_Color& fg, int drawtype){
    switch (drawtype){
        case 0:
        return solid_renderText(font, text, fg);
        case 1:
        return blended_renderText(font, text, fg);
        case 2:
        {
            SDL_Color bg = SDL_Color({(Uint8)(fg.r - (Uint8)255), (Uint8)(fg.g - (Uint8)255), (Uint8)(fg.b - (Uint8)255), (Uint8)(fg.a - (Uint8)255)});
            return shaded_renderText(font, text, fg, bg);
        }
        case 3:
        {
            SDL_Color bg = SDL_Color({(Uint8)(fg.r - (Uint8)255), (Uint8)(fg.g - (Uint8)255), (Uint8)(fg.b - (Uint8)255), (Uint8)(fg.a - (Uint8)255)});
            return LCD_renderText(font, text, fg, bg);
        }
        default:
        return blended_renderText(font, text, fg);
    }
}
SDL_Surface* renderText(TTF_Font* font, const char* text, const SDL_Color& fg, const SDL_Color& bg, int drawtype){
    switch (drawtype){
        case 0:
        return renderText(font, text, fg, 0);
        case 1:
        return renderText(font, text, fg, 1);
        case 2:
        return shaded_renderText(font, text, fg, bg);
        case 3:
        return LCD_renderText(font, text, fg, bg);
        default:
        return LCD_renderText(font, text, fg, bg);
    }
}