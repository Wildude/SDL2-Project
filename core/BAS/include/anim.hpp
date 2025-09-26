// Animation header
/*
* Sprite animations are processed here:
*/

#include <texture2D.hpp>
class SDL_Renderer;
class LinearSprite{
    SDLImage image;
    int frameSize; // or frame width
    float speed; // animation speed
    public:
    LinearSprite(); // Empty constructor
    LinearSprite(const char*, SDL_Renderer*, int); // provide path, renderer and framesize
    LinearSprite(const SDLImage&, int); // texture reference and framesize
    //LinearSprite(const char*, int); // provide path and framesize
    void Animate(float, SDL_Renderer*); // animate with deltaT
    void Animate(float, const SDL_Rect&, SDL_Renderer*); // animate with deltaT
    void setSpeed(float); // set animation speed
    void draw(SDL_Renderer*);
    SDLImage& getImage();
};