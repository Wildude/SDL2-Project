#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win("Rigid Body");
    win.crtB();
    win.pstcol(105, 0, 0, 255);
    doll samp("../Images/Doll/", win.getren());
    SDL_Event event;
    double angle = 0;
    double angle2 = 0;
    double speed = 1;
    double iterator = speed;
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos = Vflt2(x, y);
        if(event.button.button == 1){
            samp.body[3].Position = mousepos;
        }
        angle += (iterator ? iterator : 0);
        if(angle >= 50){
           iterator = -1 * speed;
        }
        if(angle <= -50){
            iterator = speed;
        }
        // cout << angle << endl;
        samp.body[5].angle = 90 + angler(samp.body[5].Position, mousepos);
        samp.body[3].angle = angle;
        samp.body[2].angle = angle2;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])speed++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])if(speed)speed--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])angle2++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])angle2--;
        samp.setbody();
        samp.draw();
        win.pst();
        win.clr();
        SDL_Delay(50);
    }
}