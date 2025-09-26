// Animation header
/*
* Sprite animations are processed here:
*/

#include <texture2D.hpp>
class SDL_Renderer;
class LinearSprite{
    Texture2D image;
    int frameSize; // or frame width
    float speed; // animation speed
    public:
    LinearSprite(); // Empty constructor
    LinearSprite(const Texture2D&, int); // texture reference and framesize
    //LinearSprite(const char*, int); // provide path and framesize
    void Animate(float); // animate with deltaT
    void setSpeed(float); // set animation speed
    void draw(SDL_Renderer*);
    Texture2D& getImage();
};