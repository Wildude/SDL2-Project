#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win;
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    physx_surface surface(Vflt2(0, win.geth() - 100), Vflt2(win.getw(), win.geth()));
    surface.setmag(1);
    surface.image.setren(win.getren());
    surface.setcolor(255, 0, 0);
    surface.query();
    weapon wep;
    wep.load("../Images/Weapons/AK 47/AK_47.png", win.getren());
    wep.setmaincenter(Vflt2(9, 6));
    wep.Position = Vflt2(win.getw()/2, win.geth()/2);
    wep.setbool(true);
    //wep.Velocity = Vflt2(5, -10);
    SDL_Event event;
    ofstream file;
    //wep.Angular_acceleration = 1;
    while(event.type != SDL_QUIT){
        // wep.Acceleration = Vflt2(0, -1);
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RETURN])wep.Position = Vflt2(win.getw()/2, win.geth()/2);
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos(x, y);
        if(event.button.button == 1)
        wep.Position = mousepos;
        wep.set_target(mousepos);
        if(wep.Position.gety() + wep.Dimension.gety() >= surface.pos1.gety()){
            surface.touch(wep);
        }
        // cout << wep.Acceleration << endl;
        // cout << wep.Velocity << endl;
        /*
        ofstream file("../Files/Data/logs.txt");
        wep.display(file);
        file.close();
        */
        wep.draw();
        wep.aim();
        surface.draw();
        win.pst();
        win.clr();
        SDL_Delay(10);
        /*
        file.open("../Files/Data/logs2.txt");
        wep.displayf(file);
        wep.image.displayf(file);
        file.close();
        */
    }
}