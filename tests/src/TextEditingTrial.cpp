//g++ -I../src/Include -L../src/Lib -o ../Executables/TextEditingTrial.exe TextEditingTrial.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
//
/*
* FINAL UPDATES
* - was able to distinguish between text editing and normal polling mode
* - Need to fix update() in TextInputHandler so that it doesn't completely overrides that's of InputHandler
* - After that need to fix the toggling issue (such a headache)
* - Once all is completed move to HUD + SDL text editing functions (advanced)
* 
*/
#include <window.hpp>
#include <textInputHandler.hpp>
#include <textlist.hpp>
#include <map>
int main(int argn, char** args)
{
    WINDOW win("Text Editing trial");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    SDL_Color col = {200, 0, 0, 255};
    SDL_Point textpos = {win.getw()/4, win.geth()/4};
    TextBox list("Text Editing Trial", FONT("../Fonts/nyala.ttf", 16));
    list.setboxpos(textpos.x, textpos.y);
    int quant = 3;
    TextInputHandler input;
    SDL_Point mousepos;
    SDL_Texture* board = NULL;
    SDL_Texture* board2 = NULL;
    while(!input.shouldQuit()){
        input.update();
        if(input.isKeyDown(SDL_SCANCODE_ESCAPE))break;
        //
        if(input.isKeyDown(SDL_SCANCODE_UP))textpos.y -= 1;
        if(input.isKeyDown(SDL_SCANCODE_DOWN))textpos.y += 1;
        if(input.isKeyDown(SDL_SCANCODE_LEFT))textpos.x -= 1;
        if(input.isKeyDown(SDL_SCANCODE_RIGHT))textpos.x += 1;
        //
        if(input.isMouseDown(SDL_BUTTON_LEFT)){
            input.setTextUse(true);
        }
        if(input.isMouseDown(SDL_BUTTON_RIGHT)){
            input.setTextUse(false);
        }
        list.setboxpos(textpos.x, textpos.y);
        list.settext(std::string(" text: " + input.getText()).c_str());
        list.draw(win.getren(), board);
        list.setboxpos(textpos.x, textpos.y + quant * 20);
        list.settext(std::string(" textinput?: " + (input.getTextState() ? std::string("true") : std::string("false"))).c_str());
        list.draw(win.getren(), board2);
        win.pst();
        win.clr();
        SDL_Delay(16);
    }
    return 0;
}