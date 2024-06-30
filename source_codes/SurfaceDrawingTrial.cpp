#include "../Headers/inclusions.hpp"
int main(int argn, char** args){
    WINDOW win("Surface drawing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
    FONT stats("../Fonts/ROCK.ttf", 20, 0, 0, 0, 0);
    TEXTURE boards[3];
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    TEXTURE box;
    box.setren(win.getren());
    for(int i = 0; i < 3; i++)boards[i].setren(win.getren());
    SDL_Event event;
    box.set_src(1, 1, 0, 0);
    box.set_dst(1, 1, 320, 240);
    int r = 0, g = 0, b = 0;
    int x, y;
    SDL_Color col = {0, 0, 0, 0};
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        SDL_GetMouseState(&x, &y);
        // Position change keys (Arrow keys)
        if(event.button.button == 1)box.set_cenpos(x, y);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])box.getdst().y -= 5;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])box.getdst().y += 5;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])box.getdst().x -= 5;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])box.getdst().x += 5;
        // Width and Height change keys (W, A, S, D)
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])box.getdst().h++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S])if(box.getdst().h > 1)box.getdst().h--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A])if(box.getdst().w > 1)box.getdst().w--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D])box.getdst().w++;
        // Color change keys (Z and X, C and V, B and N, M and',')
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_Z])if(r)r--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_X])if(r < 255)r++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_C])if(g)g--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_V])if(g < 255)g++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_B])if(b)b--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_N])if(b < 255)b++;
        // angle changers (-, +/=)
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_MINUS])box.setangle(box.getangle() - 1);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_EQUALS])box.setangle(box.getangle() + 1);
        // Updating
        SDL_Surface* surf = SDL_CreateRGBSurface(0, box.getdst().w, box.getdst().h, 8, 0, 0, 0, 0);
        SDL_SetSurfaceColorMod(surf, r, g, b);
        col.r = r;
        col.g = g;
        col.b = b;
        string infos[3] = 
        {
            "Position(x, y): (" + to_string((int)box.getdst().x) + ", " + to_string((int)box.getdst().y) + ")",
            "Size(w x h) : (" + to_string((int)box.getdst().w) + " x " + to_string((int)box.getdst().h) + ")",
            "Color(r, g, b): (" + to_string(r) + ", " + to_string(g) + ", " + to_string(b) + ")"
        };
        box.surfcpy(surf);
        for(int i = 0; i < 3; i++){
            boards[i].surfcpy(stats.blended_render(infos[i].c_str(), (i != 2 ? NULL : &col)));
            boards[i].queryF();
            boards[i].set_dstpos(0, (!i ? 0 : boards[i - 1].getdst().h * i));
            boards[i].setflip(SDL_FLIP_NONE);
            boards[i].drawC();
        }
        // Drawing
        box.setcenter();
        box.drawC();
        win.pst();
        win.clr();
        // Delaying
        SDL_Delay(50);
    }
    return 0;
}