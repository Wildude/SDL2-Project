#include "../include/box.hpp"
void Box::updatebox(){
    switch (anchor){
        case TOP_LEFT:
        padding.x = 0;
        padding.y = 0;
        break;
        case CENTER:
        padding.x = 
        padding.y =
        padding.w =
        padding.h = 
        std::max(std::max(padding.x, padding.y),std::max(padding.w, padding.h));
        break;
        case BOTTOM_RIGHT:
        padding.w = 0;
        padding.h = 0;
        break;
        case TOP:
        padding.y = 0;
        break;
        case BOTTOM:
        padding.h = 0;
        break;
        case LEFT:
        padding.x = 0;
        break;
        case RIGHT:
        padding.w = 0;
        break;
        case TOP_RIGHT:
        padding.w = 0;
        padding.y = 0;
        break;
        BOTTOM_LEFT:
        padding.x = 0;
        padding.h = 0;
        break;
        default:
        break;
    }   
}
Box::Box() {
    padding = {0, 0, 0, 0};
    border = {0, 0, 0, 0};
    margin = {0, 0, 0, 0};
}
const Box& Box::operator=(const Box& box){
    if(this != &box){
        contentRect = box.contentRect;
        padding = box.padding;
        border = box.border;
        margin = box.margin;
        borderColor = box.borderColor;
        backgroundColor = box.backgroundColor;
        anchor = box.anchor;
    }
    return *this;
}
Box::Box(const Box& box){
    *this = box;
}
Box::Box(int x, int y, int w, int h){
    contentRect = {x, y, w, h};
}
float Box::padavgx(){
    return (padding.x + padding.w)/2.0f;
}
float Box::padavgy(){
    return (padding.y + padding.h)/2.0f;
}
float Box::padavg(){
    return (padavgx() + padavgy())/2;
}
float Box::borderavgx(){
    return (border.x + border.w)/2.0f;
}
float Box::borderavgy(){
    return (border.y + border.h)/2.0f;
}
float Box::borderavg(){
    return (borderavgx() + borderavgy())/2;
}
float Box::marginavgx(){
    return (margin.x + margin.w)/2.0f;
}
float Box::marginavgy(){
    return (margin.y + margin.h)/2.0f;
}
float Box::marginavg(){
    return (marginavgx() + marginavgy())/2;
}
void Box::setanchor(Anchor Nanchor){
    anchor = Nanchor;
    updatebox();
}
const SDL_Rect& Box::getcontent(){
    return contentRect;
}
void Box::setpos(SDL_Point point){
    setpos(point.x, point.y);
}
void Box::setpos(int x, int y){
    contentRect.x = x;
    contentRect.y = y;
}
void Box::setSize(int w, int h){
    contentRect.w = w;
    contentRect.h = h;
}
void Box::setpadding(int x , int y , int w , int h ){
    if(x == -1 && y == -1 && w == -1 && h == -1){
        padding.x =
        padding.y = 
        padding.w = 
        padding.h = 
        std::max(std::max(padding.x, padding.y), std::max(padding.w, padding.h));
        // cout << " previous pad\n";
        return;
    }
    else if(y == -1 && w == -1 && h == -1){
        padding.x = 
        padding.y =
        padding.w =
        padding.h = x;
        // cout << " center pad\n";
        return;
    }
    else if(w == -1 && h == -1){
        padding.x = padding.w = x;
        padding.y = padding.h = y;
        // cout << " 2x center pad\n";
        return;
    }
    else if(h == -1){
        padding.x = x;
        padding.y = padding.h = y;
        padding.w = w;
        // cout << " 3x pad\n";
        return;
    }
    else{
        padding.x = x;
        padding.y = y;
        padding.w = w;
        padding.h = h;
        // cout << " 4x pad\n";
        return;
    }
}
void Box::setborder(int x , int y , int w , int h ){
    if(x == -1 && y == -1 && w == -1 && h == -1){
        border.x =
        border.y =
        border.w =
        border.h =
        std::max(std::max(border.x, border.y), std::max(border.w, border.h));
        return;
    }
    else if(y == -1 && w == -1 && h == -1){
        border.x =
        border.y =
        border.w =
        border.h = x;
        return;
    }
    else if(w == -1 && h == -1){
        border.x = border.w = x;
        border.y = border.h = y;
        return;
    }
    else if(h == -1){
        border.x = x;
        border.y = border.h = y;
        border.w = w;
        return;
    }
    else{
        border.x = x;
        border.y = y;
        border.w = w;
        border.h = h;
        return;
    }
}
void Box::setmargin(int x , int y , int w , int h ){
    if(x == -1 && y == -1 && w == -1 && h == -1){
        margin.x =
        margin.y =
        margin.w =
        margin.h =
        std::max(std::max(margin.x, margin.y), std::max(margin.w, margin.h));
        return;
    }
    else if(y == -1 && w == -1 && h == -1){
        margin.x =
        margin.y =
        margin.w =
        margin.h = x;
        return;
    }
    else if(w == -1 && h == -1){
        margin.x = margin.w = x;
        margin.y = margin.h = y;
        return;
    }
    else if(h == -1){
        margin.x = x;
        margin.y = margin.h = y;
        margin.w = w;
        return;
    }
    else{
        margin.x = x;
        margin.y = y;
        margin.w = w;
        margin.h = h;
        return;
    }
}
const SDL_Rect& Box::getpadding(){
    return padding;
}
const SDL_Rect& Box::getmargin(){
    return margin;
}
const SDL_Rect& Box::getborder(){
    return border;
}
// Final computed size including all layers
SDL_Rect Box::fullRect() const {
    SDL_Rect rect;
    rect.x = contentRect.x
                - padding.x - border.x - margin.x;
    rect.y = contentRect.y
                - padding.y - border.y - margin.y;
    rect.w = contentRect.w
                + padding.x + padding.w
                + border.x + border.w
                + margin.x + margin.w;
    rect.h = contentRect.h
                + padding.y + padding.h
                + border.y + border.h
                + margin.y + margin.h;
    return rect;
}

SDL_Rect Box::paddingBox() const {
    SDL_Rect rect = contentRect;
    rect.x -= padding.x;
    rect.y -= padding.y;
    rect.w += padding.x + padding.w;
    rect.h += padding.y + padding.h;
    return rect;
}

SDL_Rect Box::borderBox() const {
    SDL_Rect pad = paddingBox();
    pad.x -= border.x;
    pad.y -= border.y;
    pad.w += border.x + border.w;
    pad.h += border.y + border.h;
    return pad;
}

SDL_Rect Box::marginBox() const {
    SDL_Rect border = borderBox();
    border.x -= margin.x;
    border.y -= margin.y;
    border.w += margin.x + margin.w;
    border.h += margin.y + margin.h;
    return border;
}