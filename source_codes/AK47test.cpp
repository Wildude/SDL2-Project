// AK47test
#include "../Headers/inclusions.hpp"
int main(int argn, char** args){
    int mag = 2;
    WINDOW win("AK47_test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600);
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    AUDIO ak47("../Audio/Weapons/AK 47/ak47.wav");
    TEXTURE gun;
    gun.setren(win.getren());
    gun.load("../Images/Weapons/AK 47/AK_47.png");
    gun.queryF();
    gun.set_srcdim(65, 26);
    gun.magnify(mag);
    gun.setcenter(9 * mag, 6 * mag);
    gun.set_cenpos(win.getw()/2, win.geth()/2);
    //
    SDL_Surface* surf = SDL_CreateRGBSurface(0, mag, mag, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 255, 10, 20);
    TEXTURE box[2];
    box[0].setren(win.getren());
    box[0].surfcpy(surf);
    box[0].queryF();
    //
    SDL_SetSurfaceColorMod(surf, 10, 10, 200);
    box[1].setren(win.getren());
    box[1].surfcpy(surf);
    box[1].queryF();
    box[1].magnify(mag);
    //
    box[0].magnify(mag);
    SDL_Event event;
    bool lor = false;
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos = Vflt2(x, y);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RETURN])
        {
            gun.set_cenpos(mousepos.getx(), mousepos.gety());
            //gun1.set_cenpos(mousepos.getx(), mousepos.gety());
        }
        Vflt2 cenpos = Vflt2(gun.get_cenpos().x, gun.get_cenpos().y);
        double r_angle = angler(cenpos, mousepos);
        if(mousepos.getx() < cenpos.getx()){
            lor = true;
            gun.set_srcpos(65, 0);
            gun.setcenter(gun.getdst().w - 9 * mag, 6 * mag);
            gun.set_cenpos(cenpos.getx(), cenpos.gety());
            gun.setangle(-r_angle + 180);
        }
        else {
            lor = false;
            gun.set_srcpos(0, 0);
            gun.setcenter(9 * mag, 6 * mag);
            gun.set_cenpos(cenpos.getx(), cenpos.gety());
            gun.setangle(-r_angle);
        }
        gun.setflip(SDL_FLIP_NONE);
        Vflt2 cenposfire;
        gun.drawC();
        if(event.button.button == SDL_BUTTON_LEFT || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE]){
            if(chann_playing(0))haltchann(0);
            ak47.playt(0, 100);
            TEXTURE bullet, fire;
            bullet.setren(win.getren());
            bullet.load("../Images/Weapons/bullet/bullet.bmp");
            bullet.queryF();
            bullet.magnify(mag);
            bullet.setcenter();
            bullet.set_cenpos(cenpos.getx() + (gun.getdst().w - 80 * mag) * cos(torad(r_angle)), cenpos.gety() - (10 * mag) - (gun.getdst().w - 80 * mag) * sin(torad(r_angle)));
            bullet.setangle(-(r_angle - 40));
            fire.setren(win.getren());
            fire.load("../Images/Weapons/fire/fire.png");
            fire.queryF();
            fire.set_srcdim(20, 13);
            fire.magnify(mag + 1, mag + 2);
            fire.set_srcpos((lor ? 20 : 0), 0);
            fire.setcenter((lor ? fire.getdst().w - (mag + 1) : mag + 1), 6 * (mag + 2));
            fire.set_cenpos(cenpos.getx() + (gun.getdst().w - 9 * mag) * cos(torad(r_angle)), cenpos.gety() - (gun.getdst().w - 9 * mag) * sin(torad(r_angle)));
            cenposfire = Vflt2(fire.get_cenpos().x, fire.get_cenpos().y);
            cout << fire.getcenter().x << ' ' << fire.getcenter().y << endl;
            // cout << cenposfire << endl;
            // cout << r_angle << endl;
            fire.setangle(gun.getangle());
            bullet.drawC();
            fire.drawC();
        }
        box[0].set_dstpos(gun.get_cenpos().x, gun.get_cenpos().y);
        box[0].set_dstdim((cenpos - mousepos).getmag(), box[0].getdst().h);
        box[0].setangle(r_angle);
        // box[0].drawC();
        //
        box[1].set_dstpos(gun.get_cenpos().x, gun.get_cenpos().y);
        box[1].set_dstdim((cenpos - mousepos).getmag(), box[1].getdst().h);
        box[1].setangle(-r_angle);
        // box[1].drawC();
        //
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
}