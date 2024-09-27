// AK47test
#include "../Headers/inclusions.hpp"
int main(int argn, char** args){
    int mag = 2;
    WINDOW win("AK47_test", 0);
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    TEXTURE gun;
    gun.setren(win.getren());
    gun.load("../Images/Weapons/AK 47/AK 47.png");
    gun.queryF();
    gun.set_dstpos(win.getw()/2, win.geth()/2);
    gun.magnify(mag);
    gun.setcenter(9 * mag, 6 * mag);
    SDL_Surface* surf = SDL_CreateRGBSurface(0, mag, mag, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 255, 10, 20);
    TEXTURE box;
    box.setren(win.getren());
    box.surfcpy(surf);
    box.queryF();
    SDL_Event event;
    TEXTURE gun2;
    gun2.setren(win.getren());
    gun2.load("../Images/Weapons/AK 47/AK 47.png");
    gun2.queryF();
    gun2.set_dstpos(win.getw()/2, win.geth()/2);
    gun2.magnify(mag);
    gun2.setcenter(9 * mag, 6 * mag);
    gun2.setflip(SDL_FLIP_VERTICAL);
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos = Vflt2(x, y);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RETURN])gun.set_cenpos(mousepos.getx(), mousepos.gety());
        Vflt2 gunside = Vflt2(gun.getdst().x + gun.getcenter().x, gun.getdst().y + gun.getcenter().y);
        gun.setflip(SDL_FLIP_NONE);
        gun.setangle(angle_bn(gunside, mousepos));
        if(mousepos.getx() < gunside.getx()){
            // gun.setflip(SDL_FLIP_VERTICAL);
            // gun.setangle(gun.getangle());
        }
        bool lmb = true;
        if(event.button.button == 1 || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE] || lmb){
            TEXTURE bullet, fire;
            // lmb = true;
            bullet.setren(win.getren());
            bullet.load("../Images/Weapons/bullet.png");
            bullet.queryF();
            bullet.set_dstpos(gun.getdst().x + 27 * mag * cos(torad(-gun.getangle())), gun.getdst().y - 5 * mag * sin(torad(-gun.getangle())));
            bullet.setangle(-1 * (gun.getangle() - 40));
            bullet.magnify(mag);
            fire.setren(win.getren());
            fire.load("../Images/Weapons/fire/fire.png");
            fire.queryF();
            fire.setcenter(1 * mag, 6 * mag);
            fire.set_cenpos(gunside.getx() + (gun.getdst().w - 9 * mag) * cos(torad(gun.getangle())), gunside.gety() + (gun.getdst().w - 9 * mag) * sin(torad(gun.getangle())));
            fire.setangle(gun.getangle());
            fire.magnify(mag);
            bullet.drawC();
            fire.drawC();
        }
        gun2.set_cenpos(gun.get_cenpos().x, gun.get_cenpos().y);
        gun2.setangle(gun.getangle());
        gun2.drawC();
        gun.drawC();
        box.set_dstpos(gunside.getx(), gunside.gety());
        box.set_dstdim((gunside - mousepos).getmag(), box.getdst().h);
        box.setangle(gun.getangle());
        box.drawC();
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
}