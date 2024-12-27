//g++ -I../src/Include -L../src/Lib -o ../Executables/ Armed_man.exe Armed_man.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win("Armed man");
    win.crtB();
    win.pstcol(150, 100, 55, 255);
    simpledoll man(win.getren());
    man.body[Upper_bod].Position = Vflt2(win.getw()/2, win.geth()/2);
    man.magnify(3.33, 3.75);
    weapon wep;
    wep.load("../Images/Weapons/AK 47/AK_47.png", win.getren());
    wep.setmaincenter(Vflt2(9, 6));
    wep.Position = Vflt2(win.getw()/2, win.geth()/2);
    wep.setbool(true);
    wep.magnify(0.5, 1);
    wep.magnify(1.5);
    man.body[Head].image.load("../Images/Characters/head.png");
    man.body[Lower_bod].image.load("../Images/Characters/lower_bod.png");
    man.body[Lower_armL].image.load("../Images/Characters/lower_arm.png");
    man.body[Upper_armL].image.load("../Images/Characters/upper_arm.png");

    man.body[Lower_armR].image.load("../Images/Characters/lower_arm.png");
    man.body[Upper_armR].image.load("../Images/Characters/upper_arm.png");

    man.body[Upper_legL].image.load("../Images/Characters/upper_leg.png");
    man.body[Lower_legL].image.load("../Images/Characters/lower_leg.png");

    man.body[Upper_legR].image.load("../Images/Characters/upper_leg.png");
    man.body[Lower_legR].image.load("../Images/Characters/lower_leg.png");

    man.body[FeetL].image.load("../Images/Characters/Feet.png");
    man.body[HandL].image.load("../Images/Characters/hand.png");

    man.body[FeetR].image.load("../Images/Characters/Feet.png");
    man.body[HandR].image.load("../Images/Characters/hand.png");
    man.body[Upper_bod].image.load("../Images/Characters/upper_bod.png");
    man.queryset();
    man.magnify(2);
    SDL_Event event;
    //wep.setmaincenter(Vflt2(-10, wep.image.getdst().h/2));
    SDL_Surface* surf = SDL_CreateRGBSurface(0, 2, 2, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 0, 155, 200);
    TEXTURE point(surf, win.getren());
    point.queryF();
    bool keyStates[SDL_NUM_SCANCODES] = {false};
    bool mouseButtons[5] = {false}; // Left, right, middle, etc.
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos(x, y);
        if (event.type == SDL_QUIT) {
            break;
        }
        if (event.type == SDL_KEYDOWN) {
            keyStates[event.key.keysym.scancode] = true;
        } 
        if (event.type == SDL_KEYUP) {
            keyStates[event.key.keysym.scancode] = false;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            mouseButtons[event.button.button] = true;
        } 
        if (event.type == SDL_MOUSEBUTTONUP) {
            mouseButtons[event.button.button] = false;
        }
        if (event.type == SDL_MOUSEMOTION) {
            printf("Mouse moved to (%d, %d)\n", event.motion.x, event.motion.y);
        }
        if(keyStates[SDL_SCANCODE_RIGHT]){
            man.animate();
        }
        if(keyStates[SDL_SCANCODE_LEFT]){
            man.animate2();
        }
        double anglm = angle_bn(man.body[Head].Position, mousepos);
        bool movement = true;
        if(event.button.button == 1)man.body[Upper_bod].Position = mousepos;
        bool reverted = (wep.Position.getx() > mousepos.getx());
        Vflt2 gunbarrel(
            wep.Position.getx() + wep.Dimension.getx() / 1.3 * cos(torad(wep.angle - (reverted ? 180 : 0))),
            wep.Position.gety() - wep.Dimension.getx() / 1.3 * sin(torad(wep.angle - (reverted ? 180 : 0)))
        );
        wep.Position 
        = 
        man.body[reverted ? Lower_armR : Lower_armL].Position 
        + 
        Vflt2
        (
            man.body[reverted ? Lower_armR : Lower_armL].Dimension.gety() / 4 * cos(torad(anglm)), 
            -man.body[reverted ? Lower_armR : Lower_armL].Dimension.gety() / 4 * sin(torad(anglm))
        );
        double anglegun = angle_bn(man.body[reverted ? Lower_armR : Lower_armL].Position, gunbarrel);
        /*
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]){man.animate2();}
        else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]){man.animate();}
        else if(event.type != SDL_KEYDOWN){
                man.stabilize();
                movement = false;
        }
        */
        TXT txt("Pos", win.getren(), 15, 255, 0, 0, 255);
        txt.board.set_dstpos(gunbarrel.getx(), gunbarrel.gety());
        point.set_dstpos(gunbarrel.getx(), gunbarrel.gety());
        man.body[Head].angle = anglm;
        man.body[Upper_armL].angle = (reverted ? anglm + 135  : anglm);
        man.body[Upper_armR].angle = (reverted ? anglm + 180 : anglm + 45);
        man.body[Lower_armL].angle = (reverted ? anglegun + 90 : man.body[Upper_armL].angle + 90);
        man.body[Lower_armR].angle = (!reverted ? anglegun + 90 : man.body[Upper_armR].angle - 90);
        wep.set_target(mousepos);
        //wep.Position = man.body[HandL].Position;
        wep.aim();
        man.drawI();
        wep.draw();
        point.drawC();
        txt.board.drawC();
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
}