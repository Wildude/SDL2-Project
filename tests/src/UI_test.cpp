#include <GUI.hpp>
#include <TextBox.hpp>
#include <window.hpp>
#include <InputManager.hpp>
int main(int argn, char** args){
    WINDOW win("GUI Test");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    //std::cout << " creating play:\n";
    Label play("play");
    //std::cout << " created play:\n";
    play.setPos(100, 100);
    SDL_Color rfg = {0, 255, 0, 255}, rbg = {0, 0, 255, 255};
    //std::cout << " Creating new Font:\n";
    FONT newFont("../Fonts/ROCKB.ttf", 70);
    //std::cout << " Creating rev Font:\n";
    FONT revFont("../Fonts/nyala.ttf", 70);
    //std::cout << " setting play font:\n";
    play.setFont(revFont);
    play.setCol1(rfg);
    play.setCol2(rbg);
    SDL_Color nfg = {255, 0, 0, 255}, nbg = {0, 0, 255, 255};
    //
    //std::cout << " creating commands:\n";
    UIColor changeColor(nbg, nfg);
    UIFont changeFont(newFont);
    UIColor revertCol(rbg, rfg);
    UIFont revertFont(revFont);
    UIMultiCommand reverter;
    reverter.push(revertCol);
    reverter.push(revertFont);
    play.onFocus(&changeColor);
    //std::cout << " setting click cmd:\n";
    play.onClick(&changeFont);
    //std::cout << " setting revert cmd:\n";
    play.onRevert(&reverter);
    InputManager input;
    SDL_Texture* texture = NULL;
    bool oldclick = false;
    while(!input.shouldQuit()){
        input.update();
        SDL_Point point;
        SDL_GetMouseState(&point.x, &point.y);
        play.update(input);
        play.render(win.getren(), 6);
        //Mcon.render(win.getren(), texture);
        win.pst();
        win.clr();
        SDL_Delay(33);
    }
    return 0;
}
