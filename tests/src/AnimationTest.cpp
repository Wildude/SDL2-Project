#include <anim.hpp>
#include <texture2D.hpp>
#include <window.hpp>
#include <inputManager.hpp>
#include <textbox.hpp>
int main(int argn, char** args){
    WINDOW win("Animation test1");
    win.crtB();
    win.pstcol(255, 255, 0, 255);
    std::string path = "../00 - Character/Mortal - Run - Sheet.png";
    Texture2D atlas(path.c_str(), win.getren());
    atlas.set_dstpos(40, 40);
    LinearSprite anim1(atlas, 64); // frame width = 64 x 2
    anim1.magnify(4);
    InputManager input;
    float deltaT = 1;
    SDL_Texture* board;
    while(!input.shouldQuit()){
        input.update();
        bool animated = false;
        if(input.isMouseDown(SDL_BUTTON_LEFT)){
            SDL_GetMouseState(&anim1.getImage().getdst().x, &anim1.getImage().getdst().y);
        }
        if(input.isKeyDown(SDL_SCANCODE_UP)){
            animated = true;
            anim1.getImage().getdst().y--;
        }
        if(input.isKeyDown(SDL_SCANCODE_DOWN)){
            animated = true;
            anim1.getImage().getdst().y++;
        }

        if(input.isKeyDown(SDL_SCANCODE_RIGHT)){
            animated = true;
            anim1.flip(SDL_FLIP_NONE);
            anim1.getImage().getdst().x++;
        }
        if(input.isKeyDown(SDL_SCANCODE_LEFT)){
            animated = true;
            anim1.flip(SDL_FLIP_HORIZONTAL);
            anim1.getImage().getdst().x--;
        }
        if(animated)anim1.Animate(deltaT);
        anim1.draw(win.getren());
        win.pst();
        win.clr();
        SDL_Delay(16);
    }
    return 0;    
}