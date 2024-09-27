#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win("Rigid Body", 0), win2("stats", 700);
    win.crtB();
    win2.crtB();
    win.pstcol(105, 0, 0, 255);
    doll samp("../Images/Doll/", win.getren());
    FONT points("../Fonts/palab.ttf", 20, 0, 0, 250, 120);
    TEXTURE boards[14];
    for(int i = 0; i < 14; i++){
        boards[i].setren(win2.getren());
    }
    SDL_Event event;
    double angle = 0;
    double angle2 = 0;
    double speed = 1;
    double iterator = speed;
    samp.setbody();
    int chosen = 0;
    string infos[14] = 
    {
        "lower body",
        "lower leg R",
        "upper leg R",
        "lower leg L",
        "upper leg L",
        "upper body",
        "lower arm R",
        "upper arm R",
        "lower arm L",
        "upper arm",
        "head",
        "feet R",
        "feet L",
        "mouse"
    };
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos = Vflt2(x, y);
        if(event.button.button == 1){
            samp.body[chosen].Position = mousepos;
        }
        angle += (iterator ? iterator : 0);
        if(angle >= 50){
           iterator = -1 * speed;
        }
        if(angle <= -50){
            iterator = speed;
        }
        // cout << angle << endl;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_1]) chosen = 0;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_2]) chosen = 1;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_3]) chosen = 2;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_4]) chosen = 3;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_5]) chosen = 4;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_6]) chosen = 5;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_7]) chosen = 6;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_8]) chosen = 7;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_9]) chosen = 8;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_0]) chosen = 9;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_MINUS]) chosen = 10;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_EQUALS]) chosen = 11;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_BACKSPACE]) chosen = 12;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])speed++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])if(speed)speed--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])angle2++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])angle2--;
        for(int i = 0; i < 14; i++){
            string added = infos[i] + " : (" + to_string(i < 13 ? samp.body[i].Position.getx() : mousepos.getx()) + ", " + to_string(i < 13 ? samp.body[i].Position.gety() : mousepos.gety()) + ")";
            boards[i].surfcpy(points.blended_render(added.c_str(), NULL));
            boards[i].queryF();
            boards[i].set_dstpos(0, (!i ? 0 : boards[i - 1].getdst().h * i));
            boards[i].setflip(SDL_FLIP_NONE);
            boards[i].drawC();
        }
        samp.draw();
        win.pst();
        win.clr();
        win2.pst();
        win2.clr();
        SDL_Delay(50);
    }
}