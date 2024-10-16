//g++ -I../src/Include -L../src/Lib -o ../Executables/surfacer.exe surfacer.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win("surfacer");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    physx_surface surf(Vflt2(0, 0), Vflt2(win.getw(), win.geth()));
    cout << surf.angle << endl;
    surf.setmag(2);
    surf.image.setren(win.getren());
    surf.setcolor(0,0,0);
    surf.query();
    physx_body box;
    SDL_Surface * surface = SDL_CreateRGBSurface(0, 4, 4, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surface, 255, 0, 0);
    box.Position = Vflt2(win.getw()/2, win.geth()/2 - 100);
    box.image.setren(win.getren());
    box.image.surfcpy(surface);
    box.query();
    box.image.magnify(4);
    box.queryset();
    SDL_Event event;
    int iteration = 0;
    box.Velocity = Vflt2(0, 0);
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos = Vflt2(x, y);
        if(event.button.button == 1)box.Position = mousepos;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE])box.Velocity = Vflt2_0;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])surf.pos1.gety()--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A])surf.pos1.getx()--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S])surf.pos1.gety()++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D])surf.pos1.getx()++;
        //
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_I])surf.pos2.gety()--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_J])surf.pos2.getx()--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_K])surf.pos2.gety()++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_L])surf.pos2.getx()++;
        //
        box.Acceleration = Vflt2(0, -10);
        surf.reset();
        surf.draw();
        box.draw();
        surf.touch(box);
        win.pst();
        win.clr();
        SDL_Delay(10);
        iteration++;
        //cout << " iteration: " << iteration << endl;
    }
}