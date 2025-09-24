#include <anim.hpp>
//
LinearSprite::LinearSprite(){
    frameSize = 0;
    speed = 1;
}
LinearSprite::LinearSprite(const Texture2D& tex, int fsize): image(tex), frameSize(fsize), speed(1) {}
void LinearSprite::Animate(float deltaT){
    if(!frameSize || !image.gettexture())return;
    int w, h;
    if(image.query(&w, &h) < 0)return;
    SDL_Rect src = image.getsrc();
    src.h = h;
    src.w = frameSize;
    src.x += (speed * deltaT);
    if(src.x >= w)src.x = 0;
    image.set_src(src);
}
void LinearSprite::draw(SDL_Renderer* rend){
    if(!image.gettexture())return;
    image.drawC(rend);
}
void LinearSprite::setSpeed(float s){
    speed = s > 0 ? s : 1; 
}