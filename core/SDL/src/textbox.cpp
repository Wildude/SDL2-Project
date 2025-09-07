#include "../include/textbox.hpp"
#include <fstream>
const std::string filepath = "../files/";
const std::string textbox_path = "tbox.log";
std::ofstream textbox_file;
void TextBox::setbox(int x, int y, int w, int h)
{
    box = {x, y, w, h};
}
TextBox::TextBox(): box({0, 0, 0, 0}), 
col1({0, 0, 0, 255}), col2({255, 255, 255, 255}), 
text(""), font(){
    // cout << " creating textbox\n";
    checkfile();
    textbox_file << " creating textbox\n";
    setbox(0, 0, 0, 0);
    col1 = {0, 0, 0, 255};
    col2 = {255, 255, 255, 255};
}
void TextBox::checkfile(){
    if(!textbox_file.is_open()){
        textbox_file.open(filepath + textbox_path, std::ios::app);
    }
}
SDL_Surface* TextBox::solid_render(const char* text_ , SDL_Color* col )
{
    return TTF_RenderText_Solid(font.getfont(), (text_ ? text_ : text.c_str()), (col ? *col : col1));
}
SDL_Surface* TextBox::shaded_render(const char* text_ , SDL_Color* cola , SDL_Color* colb )
{
    return TTF_RenderText_Shaded(font.getfont(), (text_ ? text_ : text.c_str()), (cola ? *cola : col1), (colb ? *colb : col2));
}
SDL_Surface* TextBox::blended_render(const char* text_ , SDL_Color* col )
{
    return TTF_RenderText_Blended(font.getfont(), (text_ ? text_ : text.c_str()), (col ? *col : col1));
}
SDL_Surface* TextBox::LCD_render(const char* text_ , SDL_Color* cola , SDL_Color* colb )
{
    return TTF_RenderText_LCD(font.getfont(), (text_ ? text_ : text.c_str()), (cola ? *cola : col1), (colb ? *colb : col2));
}
SDL_Surface* TextBox::blended_render_utf8(const char* text_ , SDL_Color* col ){
    return TTF_RenderUTF8_Blended(font.getfont(), (text_ ? text_ : text.c_str()), (col ? *col : col1));
}
SDL_Surface* TextBox::blended_render_unicode(const char* text_ , SDL_Color* col ){
    return TTF_RenderUNICODE_Blended(font.getfont(), (const Uint16*)(text_ ? text_ : text.c_str()), (col ? *col : col1));
}
TextBox::TextBox(const std::string& text_, int x, int y, int w, int h, const FONT& font_, SDL_Color* cola , SDL_Color* colb ) : TextBox()
{
    text = text_;
    font = font_;
    col1 = (cola ? *cola : SDL_Color({0, 0, 0, 0}));
    col2 = (colb ? *colb : SDL_Color({(Uint8)(255 - col1.r), (Uint8)(255 - col1.g), (Uint8)(255 - col1.b), (Uint8)(255 - col1.a)}));
    box = {x, y, w, h};
}
TextBox::TextBox(const std::string& text_, const FONT& font_): TextBox(){
    text = text_;
    font = font_;
    col1 = SDL_Color({0, 0, 0, 0});
    col2 = SDL_Color({(Uint8)(255 - col1.r), (Uint8)(255 - col1.g), (Uint8)(255 - col1.b), (Uint8)(255 - col1.a)});
    font.TEXT_size(text.c_str(), &box.w, &box.h);
    box.x = 0;
    box.y = 0;
}
TextBox::TextBox(const char* path, int ptsize ): TextBox(){
    font = FONT(path, ptsize);
}
void TextBox::setcol1(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    col1.r = r;
    col1.g = g;
    col1.b = b;
    col1.a = a;
}
void TextBox::setcol2()
{
    setcol2(255 - col1.r, 255 - col1.g, 255 - col1.b, 255 - col1.a);
}
void TextBox::setcol2(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    col2.r = r;
    col2.g = g;
    col2.b = b;
    col2.a = a;
}
void TextBox::setfont(const FONT& font_){
    font = font_;
    font.TEXT_size(text.c_str(), &box.w, &box.h);
}
void TextBox::settext(const char* text_)
{
    if(text != std::string(text_)){
        text = text_;
        font.TEXT_size(text.c_str(), &box.w, &box.h);
    }   
}
void TextBox::settext(const std::string& text_)
{
    if(text != text_){
        text = text_;
        font.TEXT_size(text.c_str(), &box.w, &box.h);
    }
}
void TextBox::setboxpos(int x, int y)
{
    box.x = x;
    box.y = y;
}
void TextBox::draw(SDL_Renderer* rend, SDL_Texture*& board, short drawtype )
{
    checkfile();
    textbox_file << " drawing textbox\n";
    SDL_Surface* surf;
    switch (drawtype)
    {
    case 0:
        textbox_file << " solid render\n";
        surf = solid_render(text.c_str(), &col1);
        break;
    case 1:
        textbox_file << " shaded render\n";
        surf = shaded_render(text.c_str(), &col1, &col2);
        break;
    case 2:
        textbox_file << " blended render\n";
        surf = blended_render(text.c_str(), &col1);
        break;
    case 3:
        textbox_file << " LCD render\n";
        surf = LCD_render(text.c_str(), &col1, &col2);
        break;
    default:
        textbox_file << " blended render\n";
        surf = blended_render(text.c_str(), &col1);
        break;
    }
    if(!surf){
        textbox_file << " Error drawing to surface: " << SDL_GetError() << std::endl;
        // was on font_file <<
        return;
    }
    if(!board)SDL_DestroyTexture(board);
    board = SDL_CreateTextureFromSurface(rend, surf);
    if(!board){
        textbox_file << " Texture creation error: " << SDL_GetError() << std::endl;
        return;
    }
    else textbox_file << " Texture creation success\n";
    if(SDL_RenderCopy(rend, board, NULL, &box) < 0){
        textbox_file << " RenderCopy error: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_DestroyTexture(board);
    textbox_file << " destroyed texture\n";
    SDL_FreeSurface(surf);
    textbox_file << " destroyed surface\n";
}
void TextBox::printbox(){
    std::cout << box.x << ", " << box.y << ", " << box.w << ", " << box.h;
}
const SDL_Rect& TextBox::getBoxc() const{
    return box;
}
const FONT& TextBox::getFontc() const{
    return font;
}
const SDL_Color& TextBox::getCol1c() const{
    return col1;
}
const SDL_Color& TextBox::getCol2c() const{
    return col2;
}
SDL_Rect& TextBox::getBox(){
    return box;
}
FONT& TextBox::getFont(){
    return font;
}
SDL_Color& TextBox::getCol1(){
    return col1;
}
SDL_Color& TextBox::getCol2(){
    return col2;
}
// pointers
SDL_Rect* TextBox::getBoxP(){
    return &box;
}
FONT* TextBox::getFontP(){
    return &font;
}
SDL_Color* TextBox::getCol1P(){
    return &col1;
}
SDL_Color* TextBox::getCol2P(){
    return &col2;
}
const char* TextBox::getText() const{
    return text.c_str();
}
std::string& TextBox::getTextRef(){
    return text;
}
TextBox::~TextBox(){
    textbox_file << " destroying textbox\n";
    textbox_file.close();
}
std::ostream& operator<<(std::ostream& os, const TextBox& box){
    os << '\"' << box.getText() << '\"'
    << ' ' 
    << '(' 
    << box.getBoxc().x << ',' 
    << box.getBoxc().y << ',' 
    << box.getBoxc().w << ',' 
    << box.getBoxc().h << ')'
    << ' ' << box.getFontc() << ' '
    << '{'  
    << (int)box.getCol1c().r << ','
    << (int)box.getCol1c().g << ','
    << (int)box.getCol1c().b << ','
    << (int)box.getCol1c().a << '}'
    << ' ' << '{'
    << (int)box.getCol2c().r << ','
    << (int)box.getCol2c().g << ','
    << (int)box.getCol2c().b << ','
    << (int)box.getCol2c().a << '}';
    return os;
}