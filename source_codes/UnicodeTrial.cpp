#include "../Headers/BSDLF.hpp"
#include "../Headers/vector2D.hpp"
int main(int argn, char** args)
{
    WINDOW win("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_MOUSE_FOCUS);
    FONT unicode("../Fonts/nyala.ttf", 15, 255, 0, 0);
    TEXTURE image;
    TEXTURE board;
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    board.setren(win.getren());
    SDL_Event event;
    wstring expr = L"አማርኛ ለunicode ሙከራ";
    Vint2 mousepos;
    board.surfcpy(unicode.blended_render_unicode((const char*)(expr.c_str())));
    board.queryF();
    board.set_dstpos(320, 240);
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);        
        SDL_GetMouseState(&mousepos.getx(), &mousepos.gety());
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])unicode.setptsize(unicode.getptsize() + 1);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])if(unicode.getptsize() >= 10)unicode.setptsize(unicode.getptsize() - 1);
        if(event.button.button == 1)board.set_dstpos((float)mousepos.getx(), (float)mousepos.gety());
        unicode.setfontD();
        board.setflip(SDL_FLIP_NONE);
        board.surfcpy(unicode.blended_render_unicode((const char*)(expr.c_str())));
        board.queryC();
        board.drawC();
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
    return 0;
}