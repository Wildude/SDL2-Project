#include "../Headers/inclusions.hpp"
/*
 * Upper bod according to 640 x 480 screen is: (30, 45)
 *
 * 
*/
int main(int argn, char** args)
{
    WINDOW win("Rigid Body", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_FULLSCREEN);
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    simpledoll simp(win.getren());
    SDL_Event event;
    int chosen = 0;
    int iter = 1;
    ofstream file;
    simp.body[Upper_bod].Position = Vflt2(win.getw()/2, win.geth()/2);
    float speed = 10;
    while(event.type != SDL_QUIT){
        //for(int i = 0; i < 15; i++)simp.body[i].Acceleration = Vflt2(0, -10);
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos = Vflt2(x, y);
        double anglerotate;//= angler(simp.body[Head].Position, mousepos);
        double anglern = angler(simp.body[Head].Position, mousepos);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]){simp.magnify(1.5);}
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]){simp.magnify(0.75);}
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W]){
            anglerotate++;
        }
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S]){
            anglerotate--;
        }
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A]){
            for(int i = 0; i < 15; i++)simp.body[i].Velocity = Vflt2(-speed, 0);
            simp.animate2();
            /*
            simp.body[Upper_bod].Velocity = Vflt2(-speed, 0);
            simp.body[Upper_armL].Velocity = Vflt2(-speed, 0);
            simp.body[Upper_armR].Velocity = Vflt2(-speed, 0);
            simp.body[Lower_armL].Velocity = Vflt2(-speed, 0);
            simp.body[Lower_armR].Velocity = Vflt2(-speed, 0);
            */
        }
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D]){
            for(int i = 0; i < 15; i++)simp.body[i].Velocity = Vflt2(speed, 0);
            simp.animate();
            /*
            simp.body[Upper_bod].Velocity = Vflt2(speed, 0);
            simp.body[Upper_armL].Velocity = Vflt2(speed, 0);
            simp.body[Upper_armR].Velocity = Vflt2(speed, 0);
            simp.body[Lower_armL].Velocity = Vflt2(speed, 0);
            simp.body[Lower_armR].Velocity = Vflt2(speed, 0);
            */
        }
        else if(event.type == SDL_KEYUP){
            for(int i = 0; i < 15; i++){if(i != FeetL && i != FeetR && i != Upper_bod)simp.body[i].angle = 0; simp.body[i].Velocity = Vflt2_0;}
            simp.body[FeetL].angle = 225;
            simp.body[FeetR].angle = 315;
        }
        simp.body[Head].angle = anglerotate;
        simp.body[Upper_bod].angle = anglerotate - 90;
        /*
        simp.body[Upper_armL].angle = anglern + 90;
        simp.body[Upper_armR].angle = anglern + 90;
        */
        simp.body[HandL].angle = anglerotate + 90;
        simp.body[HandR].angle = anglerotate + 90;
        /*
        simp.body[Lower_armL].angle = simp.body[Upper_armL].angle;
        simp.body[Lower_armR].angle = simp.body[Upper_armR].angle;
        */
        if(event.button.button == 1){
            // samp.body[Upper_bod].Position = mousepos;
            simp.body[Upper_bod].Position = mousepos;
        }
        //cout << mousepos << endl;
        // samp.draw();
        //cout << simp.body[Head].Dimension << endl;
        TEXTURE board;
        board.setren(win.getren());
        FONT fnt("../Fonts/nyala.ttf");
        TXT(simp.body[Upper_bod].Dimension.tostring().c_str(), win.getren(), 30).board.drawC();
        //ofstream file("../Files/Data/filer.txt");
        board.drawC();
        simp.draw();
        win.pst();
        win.clr();
        SDL_Delay(10);
        iter++;
    }
}