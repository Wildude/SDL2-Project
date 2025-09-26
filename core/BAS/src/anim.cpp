#include <anim.hpp>
//
LinearSprite::LinearSprite(){
    frameSize = 0;
    speed = 1;
}
LinearSprite::LinearSprite(const char* path, SDL_Renderer* rend, int fsize)
: image(path, rend), frameSize(fsize) {}
LinearSprite::LinearSprite(const SDLImage& tex, int fsize)
: image(tex), frameSize(fsize), speed(1) {}
void LinearSprite::Animate(float deltaT, SDL_Renderer* rend){
    if(!frameSize || !image.gettex())return;
    static float counter = 0;
    SDL_Rect src = {0, 0, frameSize, image.h};
    src.h = image.h;
    src.w = frameSize;
    counter += speed * deltaT;
    if((int)counter >= 1){
        src.x += frameSize;
        counter = 0;
    }
    if(src.x >= image.w)src.x = 0;
    image.drawSRC(src, rend);
}
void LinearSprite::Animate(float deltaT, const SDL_Rect& dst, SDL_Renderer* rend){
    if(!frameSize || !image.gettex())return;
    static float counter = 0;
    SDL_Rect src = {0, 0, frameSize, image.h};
    src.h = image.h;
    src.w = frameSize;
    counter += speed * deltaT;
    if((int)counter >= 1){
        src.x += frameSize;
        counter = 0;
    }
    if(src.x >= image.w)src.x = 0;
    image.draw(dst, src, rend);
}
void LinearSprite::draw(SDL_Renderer* rend){
    if(!image.gettex())return;
    image.draw(rend);
}
void LinearSprite::setSpeed(float s){
    speed = s > 0 ? s : 1; 
}
SDLImage& LinearSprite::getImage(){
    return image;
}