#include <anim.hpp>
#include <texture2D.hpp>
#include <window.hpp>
#include <inputManager.hpp>
int main(int argn, char** args){
    WINDOW win("Animation test1");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    std::string path = "../Images/Sprites/skullGuy.png"; // path to atlas
    Texture2D atlas(path.c_str(), win.getren());
    LinearSprite anim1(atlas, 170); // frame width = 170
    InputManager input;
    float deltaT = 0.01;
    while(!input.shouldQuit()){
        input.update();
        if(input.isKeyReady(SDL_SCANCODE_UP, 30))deltaT *= 10;
        if(input.isKeyReady(SDL_SCANCODE_DOWN, 30))deltaT /= 10;
        anim1.Animate(deltaT);
        anim1.draw(win.getren());
        win.pst();
        win.clr();
        SDL_Delay(16);
    }
    return 0;    
}