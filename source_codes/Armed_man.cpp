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
    wep.magnify(2);
    man.magnify(2);
    SDL_Event event;
    //wep.setmaincenter(Vflt2(-10, wep.image.getdst().h/2));
    SDL_Surface* surf = SDL_CreateRGBSurface(0, 2, 2, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 0, 155, 200);
    TEXTURE point(surf, win.getren());
    point.queryF();
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos(x, y);
        double anglm = angle_bn(man.body[Head].Position, mousepos);
        bool movement = true;
        if(event.button.button == 1)man.body[Upper_bod].Position = mousepos;
        bool reverted = (wep.Position.getx() > mousepos.getx());
        Vflt2 gunbarrel(
            wep.Position.getx() + wep.Dimension.getx() / 1.3 * cos(torad(wep.angle)),
            wep.Position.gety() - wep.Dimension.getx() / 1.3 * sin(torad(wep.angle))
        );
        wep.Position = man.body[Lower_armL].Position + Vflt2(man.body[Lower_armL].Dimension.gety() / 4 * cos(torad(anglm)), -man.body[Lower_armL].Dimension.gety() / 4 * sin(torad(anglm)));
        double anglegun = angle_bn(man.body[Lower_armR].Position, gunbarrel);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]){man.animate2();}
        else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]){man.animate();}
        else if(event.type != SDL_KEYDOWN){
                man.stabilize();
                movement = false;
        }
        TXT txt("Pos", win.getren(), 15, 255, 0, 0, 255);
        txt.board.set_dstpos(gunbarrel.getx(), gunbarrel.gety());
        point.set_dstpos(gunbarrel.getx(), gunbarrel.gety());
        man.body[Head].angle = anglm;
        man.body[Upper_armL].angle = anglm;
        man.body[Upper_armR].angle = anglm + 45;
        man.body[Lower_armL].angle = man.body[Upper_armL].angle + 90;
        man.body[Lower_armR].angle = anglegun + 90;
        wep.set_target(mousepos);
        //wep.Position = man.body[HandL].Position;
        wep.aim();
        man.draw();
        wep.draw();
        point.drawC();
        txt.board.drawC();
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
}