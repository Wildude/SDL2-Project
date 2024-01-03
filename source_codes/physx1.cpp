/*
*
*
* Physics and SDL1: Simple Linear kinematics
*
*
*/
#include "../Files/Headers/BSDLF.h"
#include "../Files/Headers/physics.h"
int main(int arn, char**args)
{
    kinematics pos;
    WINDOW win;
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    TEXTURE box;
    box.setren(win.getren());
    box.setpath("../Images/Box.jpg");
    box.load();
    box.queryF();
    box.setcenter();
    SDL_Event event;
    pos.pos = Vflt2(40, 40);
    pos.vel = Vflt2_0;
    while(event.type != SDL_QUIT)
    {
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])pos.vel += Vflt2(0, 5);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])pos.vel += Vflt2(0, -5);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])pos.vel += Vflt2(-1, 0);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])pos.vel += Vflt2(1, 0);
        bool grav = (pos.pos.gety() < 440);
        bool drag = (!grav && pos.vel.getx());
        pos.up_accF(grav, drag);
        pos.up_vel();
        if(!grav && pos.vel.gety() < 0){pos.vel.gety() = 0;pos.pos.gety() = 440;}
        pos.up_pos();
        box.set_dstpos(pos.pos.getx(), pos.pos.gety());
        box.drawC();
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
}