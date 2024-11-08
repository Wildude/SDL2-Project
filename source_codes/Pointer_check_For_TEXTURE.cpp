//g++ -I../src/Include -L../src/Lib -o ../Executables/Pointer_check_For_TEXTURE.exe Pointer_check_For_TEXTURE.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win("POINTER CHECK");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    SDL_Surface* surf = SDL_CreateRGBSurface(0, 10, 10, 8, 0, 0, 0, 0);
    TEXTURE redbox, bluebox;
    redbox.setren(win.getren());
    bluebox.setren(win.getren());
    SDL_SetSurfaceColorMod(surf, 255, 0, 0);
    redbox.surfcpy(surf);
    SDL_SetSurfaceColorMod(surf, 0, 0, 255);
    bluebox.surfcpy(surf);
    redbox.queryF();
    bluebox.queryF();
    redbox.set_cenpos(win.getw() / 4, win.geth() / 2);
    bluebox.set_cenpos(0.75 * win.getw(), win.geth() / 2);
    ofstream file("../Files/Data/logsT.txt");
    SDL_Event event;
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos(x, y);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE]){
            file << " ============================================================= " << endl;
            file << " BEFORE: " << endl;
            file << " ============================================================= " << endl;
            redbox.displayf(file);
            bluebox.displayf(file);
            swap(redbox, bluebox);
            file << " ============================================================= " << endl;
            file << " AFTER: " << endl;
            file << " ============================================================= " << endl;
            redbox.displayf(file);
            bluebox.displayf(file);
            return 0;
        }
        if(event.button.button == 1)redbox.set_cenpos(x, y);
        if(event.button.button == 3)bluebox.set_cenpos(x, y);
        redbox.drawC();
        bluebox.drawC();
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
}