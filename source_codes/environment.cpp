//g++ -I../src/Include -L../src/Lib -o ../Executables/ environment.exe environment.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win("Environment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE);
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    TEXTURE environment[15];
    TEXTURE road[11];
    TEXTURE building("../Images/Stages/sky_scrapper.png", win.getren());
    for(int i = 0; i < 11; i++){
        road[i].setren(win.getren());
        //SDL_Surface* surf = SDL_CreateRGBSurface(0, 90, 60, 8, 0, 0, 0, 0);
        //SDL_SetSurfaceColorMod(surf, i * 50, (i + 1) * 50, (i % 2) * 50);
        road[i].load("../Images/Stages/road.png");
        road[i].queryF();
        road[i].setcenter(0, road[i].getdst().h);
        road[i].set_cenpos(i * road[i].getdst().w, win.geth());
    }
    for(int i = 0; i < 15; i++){
        environment[i].setren(win.getren());
        //SDL_Surface* surf = SDL_CreateRGBSurface(0, 1, 1, 8, 0, 0, 0, 0);
        //SDL_SetSurfaceColorMod(surf, i * 10 + 10, (i % 2) * 10 + 10, (i % 3) * 10 + 20);
        environment[i].load("../Images/Stages/sky_scrapper.png");
        //environment[i].surfcpy(surf);
        environment[i].queryF();
    }
    for(int i = 0; i < 15; i++){
        environment[i].magnify(2, 6);
        environment[i].setcenter(0, environment[i].getdst().h);
        environment[i].display();
        //cout << " (" << i * (environment[i].getdst().w + environment[i].getdst().w / 20) << ", " << win.geth() << ")" << endl;
        environment[i].set_cenpos(i * (environment[i].getdst().w + environment[i].getdst().w / 20), win.geth());
    }
    SDL_Event event;
    Vint2 iter(0, 0);
    simpledoll doll(win.getren());
    doll.magnify(3.33, 3.75);
    int counter = 0;
    Vflt2 movement_vel;
    doll.body[Upper_bod].Position.gety() = win.geth() - (doll.body[Upper_bod].Dimension.gety() / 2 + doll.body[Lower_bod].Dimension.gety() + doll.body[Upper_legR].Dimension.gety() + doll.body[Lower_legL].Dimension.gety() + doll.body[FeetL].Dimension.gety());
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos(x, y);
        bool movement = true, place = false;
        if(event.button.button == 1){doll.body[Upper_bod].Position = mousepos;}
        else{
            //
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]){
                movement_vel = Vflt2(-10, 0);
                doll.animate2();
            }
            else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]){
                movement_vel = Vflt2(10, 0);
                doll.animate();
            }
            /*
            else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]){
                movement_vel = Vflt2(0, 10);
                doll.animate3();
            }
            else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]){
                movement_vel = Vflt2(0, -10);
                doll.animate3();
            }
            */
            /*
            else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]){
                for(int i = 0; i < 15; i++)doll.body[i].Velocity = Vflt2(0, -10);
                doll.animate();
            }
            */
            else if(event.type != SDL_KEYDOWN){
                doll.stabilize();
                movement_vel = Vflt2_0;
                movement = false;
            }
        }
        cout << " size: " << 15 << endl;
        for(int i = 0; i < 15; i++){
            if(environment[i].getdst().x + environment[i].getdst().w <= 0){
                environment[i].set_cenpos(environment[i ? i - 1 : 14].getdst().x + environment[i ? i - 1 : 14].getdst().w + environment[i].getdst().w / 20, environment[i].get_cenpos().y);
            }
            if(environment[i].getdst().x > win.getw()){
                environment[i].set_cenpos(environment[i == 14 ? 0 : i + 1].getdst().x - environment[i].getdst().w, environment[i].get_cenpos().y);
            }
            environment[i].set_cenpos(environment[i].get_cenpos().x - movement_vel.getx(), environment[i].get_cenpos().y + movement_vel.gety());
        }
        for(int i = 0; i < 11; i++){
            if(road[i].getdst().x + road[i].getdst().w <= 0){
                road[i].set_cenpos(road[i ? i - 1 : 10].getdst().x + road[i ? i - 1 : 10].getdst().w, road[i].get_cenpos().y);
            }
            if(road[i].getdst().x > win.getw()){
                road[i].set_cenpos(road[i == 10 ? 0 : i + 1].getdst().x - road[i].getdst().w, road[i].get_cenpos().y);
            }
            road[i].set_cenpos(road[i].get_cenpos().x - movement_vel.getx(), road[i].get_cenpos().y + movement_vel.gety());
        }
        for(int i = 0; i < 15; i++){environment[i].drawC();}
        for(int i = 0; i < 11; i++)road[i].drawC();
        doll.stabilizeV();
        doll.draw();
        TXT txt("blackout", win.getren(), 30, 255, 0, 0, 255);
        txt.board.set_dstpos(0, 0);
        txt.board.drawC();
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
}