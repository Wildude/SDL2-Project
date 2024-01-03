#include "../Files/Headers/vector2D.h"
#include "../Files/Headers/BSDLF.h"
int main(int argn, char** args)
{
    int distance = 100, mag = 4;
    double angle = 0;
    WINDOW win("Rotator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    win.crtB();
    TEXTURE cen, tar;
    cen.setren(win.getren());
    tar.setren(win.getren());
    cen.load("../Images/point_red.jpg");
    tar.load("../Images/point.jpg");
    cen.queryF();
    tar.queryF();
    SDL_Event event;
    Vint2 center(win.getw() / 2, win.geth()/2);
    FONT style("../Fonts/Rock.ttf", 15, 0, 255, 0, 255);
    while(event.type != SDL_QUIT)
    {
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])distance += 5;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S])if(distance - 5)distance -= 5;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])angle++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])angle--;
        TEXTURE board;
        board.setren(win.getren());
        string text = " Magnitude of line: " + strmap::to_str(distance);
        board.surfcpy(style.blended_render(text.c_str()));
        board.queryF();
        Vint2 target(center.getx() + distance * cos(torad(0)), center.gety() - distance * sin(torad(0)));
        rotate_r(center, target, angle);
        cen.set_dstpos(center.getx(), center.gety());
        tar.set_dstpos(target.getx(), target.gety());
        cen.set_dstdim(cen.getsrc().w * mag, cen.getsrc().h * mag);
        tar.set_dstdim(tar.getsrc().w * mag, tar.getsrc().h * mag);
        cen.setcenter();
        tar.setcenter();
        cen.set_dstdim((center - target).getmag(), cen.getsrc().h * mag);
        cen.setangle(-1 * angler(center, target));
        cen.drawC();
        tar.drawC();
        board.drawC();
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
}
