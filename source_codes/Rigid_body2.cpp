#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win("Rigid Body", 0);
    win.crtB();
    win.pstcol(105, 0, 0, 255);
    doll samp("../Images/Doll2/", win.getren());
    TEXTURE rectangle[4];
    TEXTURE Pt;
    Pt.setren(win.getren());
    SDL_Surface *surf = SDL_CreateRGBSurface(0, 1, 1, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 255, 255, 255);
    for(int i = 0; i < 4; i++){
        rectangle[i].setren(win.getren());
        rectangle[i].surfcpy(surf);
        rectangle[i].queryF();
    }
    SDL_SetSurfaceColorMod(surf, 0, 50, 200);
    Pt.surfcpy(surf);
    Pt.queryF();
    SDL_Event event;
    double angle = 0;
    double angle2 = 0;
    double speed = 1;
    double iterator = speed;
    samp.setbody();
    int chosen = 0;
    Vflt2* rect = new Vflt2[4];
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos = Vflt2(x, y);
        double anglerotate = angler(samp.body[Upper_bod].Position, mousepos);
        samp.body[Upper_bod].angle = anglerotate;
        if(event.button.button == 1){
            samp.body[Upper_bod].Position = mousepos;
        }
        Pt.set_cenpos(samp.body[Upper_bod].Position.getx(), samp.body[Upper_bod].Position.gety());
        Pt.set_dstdim(samp.body[Upper_bod].Dimension.gety(), Pt.getdst().h);
        SDL_SetSurfaceColorMod(surf, 0, 50, 200);
        TEXTURE pt2(surf, win.getren());
        pt2.queryF();
        pt2.set_cenpos(samp.body[Upper_bod].Position.getx(), samp.body[Upper_bod].Position.gety());
        pt2.set_dstdim(samp.body[Upper_bod].Dimension.gety(), Pt.getdst().h);
        Pt.setangle(-(140 + anglerotate));
        pt2.setangle(-(40 + anglerotate));
        Vflt2 lp[2];
        lp[0] = Vflt2(Pt.get_cenpos().x + Pt.getdst().w * cos(torad(Pt.getangle())), Pt.get_cenpos().y - Pt.getdst().w * sin(torad(-Pt.getangle())));
        lp[1] = Vflt2(pt2.get_cenpos().x + pt2.getdst().w * cos(torad(pt2.getangle())), pt2.get_cenpos().y - pt2.getdst().w * sin(torad(-pt2.getangle())));
        SDL_SetSurfaceColorMod(surf, 0, 200, 50);
        TEXTURE pts[2] = {TEXTURE(surf, win.getren()), TEXTURE(surf, win.getren())};
        pts[0].queryF();
        pts[1].queryF();
        Vflt2 pos[2];
        //pt2.setangle(-40);
        rect[0] = Vflt2(samp.body[Upper_bod].image.getdst().x, samp.body[Upper_bod].image.getdst().y);
        rect[1] = Vflt2(samp.body[Upper_bod].image.getdst().x + samp.body[Upper_bod].image.getdst().w, samp.body[Upper_bod].image.getdst().y);
        rect[2] = Vflt2(samp.body[Upper_bod].image.getdst().x + samp.body[Upper_bod].image.getdst().w, samp.body[Upper_bod].image.getdst().y + samp.body[Upper_bod].image.getdst().h);
        rect[3] = Vflt2(samp.body[Upper_bod].image.getdst().x, samp.body[Upper_bod].image.getdst().y + samp.body[Upper_bod].image.getdst().h);
        rotate_rC(rect, anglerotate, 4);
        pos[0] = intersector(samp.body[Upper_bod].Position, lp[0], rect[0], rect[3]);
        pos[1] = intersector(samp.body[Upper_bod].Position, lp[1], rect[1], rect[2]);
        pts[0].set_cenpos(pos[0].getx(), pos[0].gety());
        pts[1].set_cenpos(pos[1].getx(), pos[1].gety());
        samp.draw();
        for(int i = 0; i < 4; i++){
            rectangle[i].set_cenpos(rect[i].getx(), rect[i].gety());
            rectangle[i].set_dstdim((rect[i]-rect[i < 3 ? i + 1 : 0]).getmag(), rectangle[i].getdst().h);
            rectangle[i].setangle(-angler(rect[i], rect[i < 3 ? i + 1 : 0]));
        }
        for(int i = 0; i < 4; i++)rectangle[i].drawC();
        pts[0].magnify(4);
        pts[1].magnify(4);
        Pt.drawC();
        pt2.drawC();
        pts[0].drawC();
        pts[1].drawC();
        win.pst();
        win.clr();
        SDL_Delay(50);
    }
}