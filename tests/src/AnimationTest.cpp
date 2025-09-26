#include <anim.hpp>
#include <texture2D.hpp>
#include <window.hpp>
#include <inputManager.hpp>
#include <textbox.hpp>
int main(int argn, char** args){
    WINDOW win("Animation test1");
    win.crtB();
    win.pstcol(255, 255, 0, 255);
    std::string path = "../Images/Sprites/skullGuy.png"; // path to atlas
    Texture2D rando("../Images/Weapons/AK 47/AK_47.png", win.getren());
    rando.queryF();
    Texture2D atlas(path.c_str(), win.getren());
    atlas.queryF();
    atlas.set_dstpos(40, 40);
    atlas.magnify(0.25, 0.45);
    LinearSprite anim1(atlas, 170); // frame width = 170
    InputManager input;
    float deltaT = 0.01;
    SDL_Texture* board;
    TextBox tbox("../Fonts/nyala.ttf", 25);
    while(!input.shouldQuit()){
        input.update();
        if(input.isMouseDown(SDL_BUTTON_LEFT)){
            int x, y;
            SDL_GetMouseState(&x, &y);
            anim1.getImage().set_dstpos(x, y);
        }
        if(input.isKeyReady(SDL_SCANCODE_UP, 5))deltaT *= 10;
        if(input.isKeyReady(SDL_SCANCODE_DOWN, 5))deltaT /= 10;
        anim1.Animate(deltaT);
        anim1.draw(win.getren());
        tbox.settext(std::string("speed = ") + std::to_string(deltaT));
        tbox.draw(win.getren(), board);
        //atlas.drawC(win.getren());
        //rando.drawC(win.getren());
        win.pst();
        win.clr();
        SDL_Delay(16);
    }
    return 0;    
}