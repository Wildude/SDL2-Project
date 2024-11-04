//g++ -I../src/Include -L../src/Lib -o ../Executables/ Armed_man.exe Armed_man.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win("Armed man");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    simpledoll man(win.getren());
    man.body[Upper_bod].Position = Vflt2(win.getw()/2, win.geth()/2);
    man.magnify(3.33, 3.75);
    weapon wep;
    wep.load("../Images/Weapons/AK 47/AK_47.png", win.getren());
    wep.setmaincenter(Vflt2(9, 6));
    wep.Position = Vflt2(win.getw()/2, win.geth()/2);
    wep.setbool(true);
    wep.magnify(0.5, 1);
    SDL_Event event;
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos(x, y);
        double anglm = angler(man.body[Head].Position, mousepos);
        bool movement = true;
        if(event.button.button == 1)man.body[Upper_bod].Position = mousepos;
        Vflt2 gunbarrel(
            wep.Position.getx() + 20 * cos(torad(wep.angle)),
            wep.Position.gety() - 20 * sin(torad(wep.angle))
        );
        double anglegun = angler(man.body[Lower_armR].Position, gunbarrel);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]){man.animate2();}
        else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]){man.animate();}
        else if(event.type != SDL_KEYDOWN){
                man.stabilize();
                movement = false;
        }
        TXT txt("Pos", win.getren(), 15, 255, 0, 0, 255);
        txt.board.set_dstpos(gunbarrel.getx(), gunbarrel.gety());
        man.body[Lower_armL].angle = anglm + 90;
        man.body[Lower_armR].angle = anglegun + 90;
        wep.set_target(mousepos);
        wep.Position = man.body[HandL].Position;
        wep.aim();
        man.draw();
        wep.draw();
        txt.board.drawC();
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
}