#include "../Headers/BSDLF.hpp"
#include <vector>
#include "../Headers/vector2D.hpp"
int main(int argn, char** args){
    WINDOW win("Graph drawer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    TEXTURE axes[2];
    axes[0].setren(win.getren());
    axes[1].setren(win.getren());
    SDL_Event event;
    int w = 2;
    vector<TEXTURE> points;
    float x = -win.getw()/2;
    float dx = 1;
    int r = 0, g = 0, b = 0;
    vector<TEXTURE> verticals;
    while(event.type != SDL_QUIT && x != win.getw()){
        float y = 100 * sin(x * 0.05);
        SDL_PollEvent(&event);
        // if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])w++;
        // if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])w--;
        SDL_Surface* surf = SDL_CreateRGBSurface(0, w, w, 8, 0, 0, 0, 0);
        SDL_SetSurfaceColorMod(surf, 255, 0, 0);
        axes[0].surfcpy(surf);
        axes[0].query();
        axes[0].setcenter(0, w/2);
        axes[0].set_dstdim(win.getw(), w);
        axes[0].set_cenpos(0, win.geth()/2);
        SDL_SetSurfaceColorMod(surf, 0, 255, 0);
        axes[1].surfcpy(surf);
        axes[1].query();
        axes[1].setcenter(w/2, 0);
        axes[1].set_dst(w, win.geth());
        axes[1].set_cenpos(win.getw()/2, 0);
        axes[0].drawC();
        axes[1].drawC();
        SDL_SetSurfaceColorMod(surf, r, g, b);
        points.push_back(TEXTURE());
        points.at(points.size() - 1).setren(win.getren());
        points.at(points.size() - 1).surfcpy(surf);
        verticals.push_back(TEXTURE());
        SDL_SetSurfaceColorMod(surf, 0, 0, 255);
        verticals.at(verticals.size() - 1).setren(win.getren());
        verticals.at(verticals.size() - 1).surfcpy(surf);
        verticals.at(verticals.size() - 1).query();
        verticals.at(verticals.size() - 1).set_dstdim(w, abs(y));
        verticals.at(verticals.size() - 1).setcenter(w/2, 0);
        verticals.at(verticals.size() - 1).set_cenpos(x + win.getw()/2, win.geth()/2);
        if(y > 0)verticals.at(verticals.size() - 1).setangle(180);
        points.at(points.size() - 1).query();
        points.at(points.size() - 1).set_dstdim(w, w);
        points.at(points.size() - 1).setcenter(0, w/2);
        points.at(points.size() - 1).set_cenpos(x + win.getw()/2, win.geth()/2 - y);
        if(points.size() > 1){
            Vflt2 pos1 = Vflt2(points.at(points.size() - 1).getdst().x, points.at(points.size() - 1).getdst().y), pos2 = Vflt2(points.at(points.size() - 2).getdst().x, points.at(points.size() - 2).getdst().y);
            points.at(points.size() - 1).set_dstdim((pos1 - pos2).getmag(), w);
            points.at(points.size() - 1).setangle(-1 * angler(pos1, pos2));
        }
        points.at(points.size() - 1).drawC();
        verticals.at(verticals.size() - 1).drawC();
        win.pst();
        // win.clr();
        SDL_Delay(50);
        x += dx * w;
    }
    SDL_Delay(500);
    return 0;
}