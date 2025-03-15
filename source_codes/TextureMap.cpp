//g++ -I../src/Include -L../src/Lib -o ../Executables/TextureMap.exe TextureMap.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
#include <map>
int main(int argn, char** args)
{
    WINDOW win;
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    TEXTURE bridge("../Images/Stages/bridge.png", win.getren());
    bridge.queryF();
    /*
    map<string, TEXTURE*> tex_maps;
    tex_maps["first"] = new TEXTURE("../Images/Stages/bridge.png", win.getren());
    TEXTURE* controller;
    controller = tex_maps["first"];
    controller->queryF();
    */
    SDL_FRect pos = {0, 0, bridge.getdst().w, bridge.getdst().h};
    SDL_Event event;
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        //controller->draw(NULL, &pos);
        bridge.draw();
        pos.x += pos.w;
        pos.y += pos.x / win.getw();
        pos.x = pos.x > win.getw() ? 0 : pos.x;
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
    return 0;
}