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
    int sides, sidelength;
    cout<<" Enter sides: ";cin>>sides;
    cout<<" Enter sidelength: ";cin>>sidelength;
    WINDOW win;
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    TEXTURE* point = new TEXTURE[sides];
    Vflt2* vertices = new Vflt2[sides];
    for(int i = 0; i < sides; i++)
    {
        point[i].setren(win.getren());
        point[i].setpath("../Images/point.jpg");
        point[i].load();
        point[i].queryF();
        point[i].setcenter();
    }
    SDL_Event event;
    pos.pos = Vflt2(40, 40);
    pos.vel = Vflt2_0;
    Vflt2 center(320, 240);
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
        center = pos.pos;
        vertices = n_gonr(center, sides, sidelength);
        for(int i = 0; i < sides; i++)
        {
            point[i].set_dstpos(vertices[i].getx(), vertices[i].gety());
            point[i].set_dstdim((vertices[i] - vertices[i != sides-1 ? i + 1 : 0]).getmag(), point[i].getdst().h);
            point[i].setangle(-1 * angler(vertices[i], vertices[i != sides-1 ? i + 1 : 0]));
            point[i].drawC();
        }
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
}