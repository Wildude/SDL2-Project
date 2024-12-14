//g++ -I../src/Include -L../src/Lib -o ../Executables/ circ_rect_anim.exe circ_rect_anim.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW window("Circle-Rectangle-Animation");
    window.crtB();
    window.pstcol(255, 255, 255, 255);
    Vflt2 center = Vflt2(window.getw()/2 , window.geth()/2);
    float radius = 99;
    SDL_Event event;
    double angle = 0;
    TEXTURE rects[4];
    for(int i = 0; i < 4; i++)rects[i].setren(window.getren());
    SDL_Surface* surf = SDL_CreateRGBSurface(0, 1, 1, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 0, 0, 0);
    TXT texts[4] = {
        TXT(string("rect0").c_str(), window.getren(), 20, 200, 0, 0, 255),
        TXT(string("rect1").c_str(), window.getren(), 20, 60, 100, 50, 255),
        TXT(string("rect2").c_str(), window.getren(), 20, 120, 0, 100, 255),
        TXT(string("rect3").c_str(), window.getren(), 20, 180, 200, 0, 255)
    };
    for(int i = 0; i < 4; i++){
        SDL_SetSurfaceColorMod(surf, i * 60, (i % 2) * i * 100, (i % 3) * i * 50);
        texts[i].board.set_dstpos(0, texts[i].board.getdst().h * i);
        texts[i].setcol1(255);
        rects[i].surfcpy(surf);
        rects[i].queryF();
        rects[i].magnify(5);
    }
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])radius++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])radius--;
        radius = radius < 49 ? 49 : radius;
        Vflt2 arcpoint = Vflt2(center.getx() + radius * cos(torad(angle)), center.gety() - radius * sin(torad(angle)));
        rects[0].set_dstpos(center.getx(), center.gety());
        rects[1].set_dstpos(center.getx(), arcpoint.gety());
        rects[2].set_dstpos(arcpoint.getx(), arcpoint.gety());
        rects[3].set_dstpos(arcpoint.getx(), center.gety());
        //
        rects[0].set_dstdim((center - arcpoint).getmag());
        rects[1].set_dstdim((center - arcpoint).getmag());
        rects[2].set_dstdim((center - arcpoint).getmag());
        rects[3].set_dstdim((center - arcpoint).getmag());
        //
        rects[0].setangle(-angle_bn(center, Vflt2(center.getx(), arcpoint.gety())));
        rects[1].setangle(-angle_bn(Vflt2(center.getx(), arcpoint.gety()), arcpoint));
        rects[2].setangle(-angle_bn(arcpoint, Vflt2(arcpoint.getx(), center.gety())));
        rects[3].setangle(-angle_bn(Vflt2(arcpoint.getx(), center.gety()), center));
        //
        for(int i = 0; i < 4; i++){rects[i].drawC();texts[i].board.drawC();}
        window.pst();
        window.clr();
        SDL_Delay(10);
        angle++;
    }
    return 1;
}