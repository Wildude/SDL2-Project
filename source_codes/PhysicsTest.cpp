#include "../Headers/inclusions.hpp"
int main(int arn, char** args)
{
    WINDOW win("Physics test");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    TEXTURE Box;
    Box.setren(win.getren());
    SDL_Surface* surf = SDL_CreateRGBSurface(0, 1, 1, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 255, 0, 0);
    Box.surfcpy(surf);
    Box.queryF();
    physx BoxObj;
    BoxObj.Dimension = Vflt2(1, 1);
    SDL_Event event;
    /*
    physx_surface window[4] = 
    {
        physx_surface(Vflt2_0, Vflt2(640, 0)),
        physx_surface(Vflt2_0, Vflt2(0, 480)),
        physx_surface(Vflt2(0, 480), Vflt2(640, 480)),
        physx_surface(Vflt2(640, 0), Vflt2(640, 480))
    };
    */
    Vflt2 mainpos = Vflt2(win.getw()/2, win.geth()/2);
    while(event.type != SDL_QUIT)
    {
        // int frame1 = SDL_GetTicks64();
        SDL_PollEvent(&event);
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos = Vflt2(x, y);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        // Arrow keys for movement
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])BoxObj.Velocity.gety()++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])BoxObj.Velocity.gety()--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])BoxObj.Velocity.getx()--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])BoxObj.Velocity.getx()++;
        // WASD for size change
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])BoxObj.Dimension.gety()++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A])BoxObj.Dimension.getx()++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S])if(BoxObj.Dimension.gety() > 1)BoxObj.Dimension.gety()--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D])if(BoxObj.Dimension.getx() > 1)BoxObj.Dimension.getx()--;
        // mouse for snapping
        if(event.button.button == 1)BoxObj.Position = mousepos;
        // -/= for angles
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_MINUS])BoxObj.Angular_velocity++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_EQUALS])BoxObj.Angular_velocity--;
        // Null acceleration
        BoxObj.Acceleration -= BoxObj.Acceleration;
        if(BoxObj.Position.gety() < win.geth() - BoxObj.Dimension.gety())BoxObj.Acceleration += Vflt2(0, -10); // appling gravity
        else BoxObj.Position.gety() = win.geth() - BoxObj.Dimension.gety();
        if(BoxObj.Position.gety() == win.geth() - BoxObj.Dimension.gety()){BoxObj.Acceleration += Vflt2(-BoxObj.Velocity.getx(), 0);BoxObj.Velocity.gety() = 0;}
        BoxObj.set_center_of_mass();
        BoxObj.set_mass();
        BoxObj.app_acc();
        BoxObj.app_ang_acc();
        BoxObj.app_ang_vel();
        BoxObj.app_vel();
        Box.set_dst(BoxObj.Dimension.getx(), BoxObj.Dimension.gety(), BoxObj.Position.getx(), BoxObj.Position.gety());
        Box.setangle(BoxObj.angle);
        Box.setcenter();
        Box.drawC();
        win.pst();
        win.clr();
        // int frame2 = SDL_GetTicks64();
        SDL_Delay(1000 / 60);
    }
}
