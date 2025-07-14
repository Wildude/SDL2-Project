// Tilemaptest 2.0
// uses multiple layers and tilesets
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win("Tilemaptest2");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    float speed = 10;
    SDL_Event event;
    TEXTURE man;
    SDL_Surface* surf = SDL_CreateRGBSurface(0, 5, 8, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 255, 0, 0);
    man.surfcpy(surf, win.getren());
    man.queryF();
    man.magnify(2);
    //
    Vflt2 vel(0, 0);
    SDL_Color col = {200, 0, 0, 255};
    man.set_cenpos(win.getw()/2, win.geth()/2);
    Level level;
    level.parseLevel("../Files/XML/16 bit world.tmx", win.getren());
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos(x, y);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        level.render(win.getren());
        man.drawOF(win.getren());
        //
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
    return 0;
}