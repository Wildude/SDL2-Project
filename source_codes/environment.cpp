//g++ -I../src/Include -L../src/Lib -o ../Executables/ environment.exe environment.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win("Environment");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    TEXTURE env("../Images/Stages/sprite_check2.png", win.getren());
    env.queryF();
    env.set_srcdim(60, 90);
    SDL_Event event;
    Vint2 iter(0, 0);
    simpledoll doll(win.getren());
    doll.magnify(3.33, 3.75);
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos(x, y);
        bool movement = true;
        if(event.button.button == 1){doll.body[Upper_bod].Position = mousepos;}
        else{
            //
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]){doll.animate2();}
            else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]){doll.animate();}
            else if(event.type != SDL_KEYDOWN){
                doll.stabilize();
                movement = false;
            }
        }
        //
        env.set_srcpos(iter.getx(), iter.gety());
        env.drawC();
        doll.draw();
        win.pst();
        win.clr();
        if(movement)iter.getx()++;
        if(iter.getx() > 600){iter.getx() = 0; iter.gety() += 90;}
        SDL_Delay(10);
    }
}