#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win("Spiral Test");
    win.crtB();
    // win.pstcol(255, 255, 255, 255);
    vector<TEXTURE> locus;
    int iterator = 10;
    int r = 0, g = 0, b = 0;
    int w = 2;
    SDL_Surface* surf = SDL_CreateRGBSurface(0, w, w, 8, 0, 0, 0, 0);
    SDL_Event event;
    while(event.type != SDL_QUIT)
    {
        SDL_PollEvent(&event);
        r += (!iterator % 3 || !iterator % 2 ? 50 : 0);
        g += (!iterator % 5 || !iterator % 7 ? 50 : 0);
        b += (!iterator % 11 || !iterator % 13 ? 50 : 0);
        if(r >= 255)r = 0;
        if(g >= 255)g = 0;
        if(b >= 255)b = 0;
        SDL_SetSurfaceColorMod(surf, 255 - r, 255 - g, 255 - b);
        ///*
        if(iterator <= 2900)
        {
            locus.push_back(TEXTURE());
            locus.at(locus.size() - 1).setren(win.getren());
            locus.at(locus.size() - 1).surfcpy(surf);
            locus.at(locus.size() - 1).queryF();
            locus.at(locus.size() - 1).set_dst(w, w, win.getw()/2 + iterator/10 * cos(torad(iterator)), win.geth()/2 - iterator/10 * sin(torad(iterator)));
            /*
            if(locus.size() > 1){
                Vflt2 p1 = Vflt2(locus.at(locus.size() - 1).getdst().x, locus.at(locus.size() - 1).getdst().x);
                Vflt2 p2 = Vflt2(locus.at(locus.size() - 2).getdst().x, locus.at(locus.size() - 2).getdst().x);
                locus.at(locus.size() - 1).set_dstdim((p1 - p2).getmag(), w);
                locus.at(locus.size() - 1).setangle(-1 * angler(p1, p2));
            }
            */
            locus.at(locus.size() - 1).drawC();
        }
        //*/
        /*
        else{
            win.clr();
            for(int i = 0; i < 50; i++){
                Vflt2 p1 = Vflt2(locus[i].getdst().x, locus[i].getdst().x);
                Vflt2 p2 = Vflt2(locus[i != locus.size() - 1 ? i + 1 : i].getdst().x, locus[i != locus.size() - 1 ? i + 1 : i].getdst().x);
                locus[i].set_dstdim((p1 - p2).getmag(), w);
                locus[i].setangle(-1 * angler(p1, p2));
                locus[i].drawC();
            }
        }*/
        win.pst();
        SDL_Delay(50);
        iterator += 10;
    }
}