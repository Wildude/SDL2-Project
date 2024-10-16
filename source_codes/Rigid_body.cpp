#include "../Headers/inclusions.hpp"
int make(int x, int ex = 1){
    int power = pow(10, ex);
    for(int )
}
int main(int argn, char** args)
{
    WINDOW win("Rigid Body");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    doll samp("../Images/Doll2/", win.getren());
    simpledoll simp(win.getren());
    TEXTURE rectangle[4];
    TEXTURE Pt;
    Pt.setren(win.getren());
    SDL_Surface *surf = SDL_CreateRGBSurface(0, 1, 1, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 255, 255, 255);
    for(int i = 0; i < 4; i++){
        rectangle[i].setren(win.getren());
        rectangle[i].surfcpy(surf);
        rectangle[i].queryF();
    }
    SDL_SetSurfaceColorMod(surf, 0, 50, 200);
    Pt.surfcpy(surf);
    Pt.queryF();
    SDL_Event event;
    double angle = 0;
    double angle2 = 0;
    double speed = 1;
    double iterator = speed;
    samp.setbody();
    int chosen = 0;
    //Vflt2* rect = new Vflt2[4];
    //for(int i = 0; i < 15; i++)samp.body[i].Dimension *= 1.5;
    int iter = 1;
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])simp.magnify(2);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])simp.magnify(0.5);
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos = Vflt2(x, y);
        double anglerotate = angler(simp.body[Head].Position, mousepos);
        simp.body[Head].angle = anglerotate;
        simp.body[Upper_armL].angle = anglerotate + 90;
        simp.body[Upper_armR].angle = anglerotate + 90;
        simp.body[Lower_armL].angle = anglerotate + 90;
        simp.body[Lower_armR].angle = anglerotate + 90;
        simp.body[HandL].angle = anglerotate + 90;
        simp.body[HandR].angle = anglerotate + 90;
        if(event.button.button == 1){
            // samp.body[Upper_bod].Position = mousepos;
            simp.body[Upper_bod].Position = mousepos;
        }
        simp.body[]
        //cout << mousepos << endl;
        // samp.draw();
        simp.draw();
        win.pst();
        win.clr();
        SDL_Delay(50);
        iter++;
    }
}