#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win("Math test");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    int w = 5;
    SDL_Event event;
    Vflt2 polypos = Vflt2(win.getw()/2, win.geth()/2);
    float bigMag = 450;
    int sides = 3;
    float sidelength = 100;
    float pangle = 0;
    int r = 0, g = 0, b = 0;
    int iterator = 0;
    TEXTURE lp;
    lp.setren(win.getren());
    SDL_Surface* surface = SDL_CreateRGBSurface(0, w, w, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surface, 200, 200, 200);
    lp.surfcpy(surface);
    lp.queryF();
    float langle = 0;
    float magaz = 200;
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        int x, y;
        SDL_GetMouseState(&x, &y);
        // WASD
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])sides++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A])if(w > 1)w--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S])if(sides > 3)sides--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D])w++;
        // ZX
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_Z])if(sidelength > 25)sidelength--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_X])sidelength++;  
        // -/=
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_MINUS])pangle++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_EQUALS])pangle--;
        //
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])langle--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])langle++;  
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])if(magaz > 25)magaz--;  
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])magaz++;  
        //
        Vflt2 linepos = polypos - Vflt2(25, -25);
        Vflt2 sidelinepos = Vflt2(500 * 2 * cos(torad(langle)), -500 * 2 * sin(torad(langle)));
        TEXTURE sideline, mouser;
        sideline.setren(win.getren());
        mouser.setren(win.getren());
        lp.set_dst(2000, w, linepos.getx(), linepos.gety());
        lp.setangle(-langle);
        Vflt2 mousepos = Vflt2(x, y);
        if(event.button.button == 1)
        polypos = mousepos;
        Vflt2* vertices = n_gonr<float>(polypos, sides, sidelength);
        rotate_rC(vertices, pangle, sides);
        TEXTURE* polygon = new TEXTURE[sides], *lines = new TEXTURE[sides];
        SDL_Surface* surf = SDL_CreateRGBSurface(0, w, w, 8, 0, 0, 0, 0);
        r += (iterator % 10 ? 1 : 0);
        g += (iterator % 20 ? 1 : 0);
        b += (iterator % 30 ? 1 : 0);
        SDL_SetSurfaceColorMod(surf, r, g, b);
        for(int i = 0; i < sides; i++){
            polygon[i].setren(win.getren());
            lines[i].setren(win.getren());
            polygon[i].surfcpy(surf);
            polygon[i].queryF();
            polygon[i].set_dst(w, w, vertices[i].getx(), vertices[i].gety());
            polygon[i].set_dstdim((vertices[i] - vertices[i != sides - 1 ? i + 1 : 0]).getmag(), w);
            polygon[i].setangle(-angler(vertices[i], vertices[i != sides - 1 ? i + 1 : 0]));
            polygon[i].drawC();
        }
        SDL_SetSurfaceColorMod(surf, r-100, g-100, b-100);
        float* mag = new float[sides];
        for(int i = 0; i < sides; i++){
            lines[i].surfcpy(surf);
            lines[i].queryF();
            lines[i].set_dst(w, w, vertices[i].getx(), vertices[i].gety());           
            mag[i] = p_l_mag<float>(vertices[i], sidelinepos, langle - 90);
            lines[i].set_dstdim(mag[i], w);
            lines[i].setangle(-langle);
            lines[i].drawC();
        }
        SDL_SetSurfaceColorMod(surf, r-150, g-150, b-150);
        sideline.surfcpy(surf);
        sideline.queryF();
        sideline.set_dst(magaz, w, sidelinepos.getx(), sidelinepos.gety());
        sideline.setangle(-langle - 90);
        sideline.drawC();
        TEXTURE mostpos;
        mostpos.setren(win.getren());
        SDL_SetSurfaceColorMod(surf, 255, 0, 0);
        mouser.surfcpy(surf);
        mouser.queryF();
        mouser.set_dst(p_l_mag<float>(mousepos, sidelinepos, langle - 90), w, x, y);
        mouser.setangle(-langle);
        mouser.drawC();
        mostpos.surfcpy(surf);
        mostpos.queryF();
        float smag = numeric_limits<float>::max();
        int index = -1;
        for(int i = 0; i < sides; i++){
            if(smag > mag[i]){
                smag = mag[i];
                index = i;
            }
        }
        Vflt2 mostposvec = vertices[index];
        mostpos.set_dst(w, w, mostposvec.getx(), mostposvec.gety());
        for(int i = 0; i < sides; i++){
            cout << ' ' << i << ": " << mag[i] << endl;
        }
        cout << "==========================\n";
        mostpos.drawC();
        lp.drawC();
        win.pst();
        win.clr();
        SDL_Delay(50);
        iterator++;
    }
    return 0;
}