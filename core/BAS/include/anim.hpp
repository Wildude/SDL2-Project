// Animation header
/*
* Sprite animations are processed here:
*/

#include <texture2D.hpp>
class LinearSprite{
    Texture2D image;
    int frameSize; // or frame width
    int width; // total width
    float speed; // animation speed
    public:
    LinearSprite(); // Empty constructor
    LinearSprite(const Texture2D&, int); // texture reference and framesize
    void flip();
    void flip(SDL_RendererFlip);
    //LinearSprite(const char*, int); // provide path and framesize
    void Animate(float); // animate with deltaT
    float& getspeed();
    float getspeed() const;
    void setSpeed(float); // set animation speed
    void draw(SDL_Renderer*);
    Texture2D& getImage();
    void magnify(int mag);
    void minify(int min);
    void magnifyX(int magx);
    void magnifyY(int magy);
    void magnifyXY(int magx, int magy);
    void minifyX(int minx);
    void minifyY(int miny);
    void minifyXY(int minx, int miny);
};