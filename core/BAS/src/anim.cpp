#include <anim.hpp>
//
/*
Texture2D image;
int frameSize; // or frame width
int width; // total width
float speed; // animation speed
*/
LinearSprite::LinearSprite(): image(), frameSize(0), width(0), speed(10){

}
LinearSprite::LinearSprite(const Texture2D& tex, int fsize)
: image(tex), frameSize(fsize), width(image.getsrc().w), speed(10) {
    image.set_srcdim(frameSize, image.getsrc().h);
    image.set_dstdim(frameSize, image.getsrc().h);
}
void LinearSprite::Animate(float deltaT) {
    if (!frameSize || !image.gettexture()) return;

    static float counter = 0.0f;
    counter += deltaT;

    while (counter >= speed) {  
        image.getsrc().x += frameSize;
        counter -= speed;   // keep leftover time
    }

    if (image.getsrc().x >= width)
        image.getsrc().x = 0;
}

void LinearSprite::draw(SDL_Renderer* rend){
    if(!image.gettexture())return;
    image.draw(rend);
}
void LinearSprite::setSpeed(float s){
    speed = s > 0 ? s : 1; 
}
Texture2D& LinearSprite::getImage(){
    return image;
}
float& LinearSprite::getspeed(){
    return speed;
}
float LinearSprite::getspeed() const{
    return speed;
}
void LinearSprite::flip() {
    image.toogleflipH();
}
void LinearSprite::flip(SDL_RendererFlip flipper){
    image.setflip(flipper);
}
void LinearSprite::magnify(int mag){
    image.magnify(mag);
}
void LinearSprite::minify(int mag){
    image.magnify(1.0f/mag);
    frameSize /= mag;
    width /= mag;
}
void LinearSprite::magnifyX(int magx){}
void LinearSprite::magnifyY(int magy){}
void LinearSprite::magnifyXY(int magx, int magy){}
void LinearSprite::minifyX(int minx){}
void LinearSprite::minifyY(int miny){}
void LinearSprite::minifyXY(int minx, int miny){}