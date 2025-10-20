// Tilemaptest 2.0
// uses multiple layers and tilesets
#include <Tilemap.hpp>
#include <window.hpp>
#include <texture2D.hpp>
int main(int argn, char** args)
{
    WINDOW win("Tilemaptest2");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    float speed = 10;
    SDL_Event event;
    Texture2D man;
    SDL_Surface* surf = SDL_CreateRGBSurface(0, 5, 8, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 255, 0, 0);
    man.surfcpy(surf, win.getren());
    man.queryF();
    man.magnify(2);
    //
    SDL_FPoint vec = {0.0f, 0.0f};
    SDL_Color col = {200, 0, 0, 255};
    man.set_cenpos(win.getw()/2, win.geth()/2);
    Level level;
    level.parseLevel("../Files/XML/16 bit world.tmx", win.getren());
    SDL_Point mousepos;
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        int x, y;
        SDL_GetMouseState(&mousepos.x, &mousepos.y);
        
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        level.render(win.getren());
        man.drawOF(win.getren(), &man.getdst(), 1.0f, 0.0);
        //
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
    return 0;
}