#include <GUI.hpp>
#include <TextBox.hpp>
#include <window.hpp>
#include <InputManager.hpp>
int main(int argn, char** args){
    // std::cout << " revfont\n";
    FONT revFont("../Fonts/ROCKB.ttf", 15);
    // std::cout << " newfont\n";
    FONT newFont("../Fonts/ROCKBI.ttf", 15);
    UIContainer Mcon;
    SDL_Color rfg = {255, 0, 0, 255}, rbg = {0, 255, 255, 255};
    SDL_Color nfg = {255, 255, 0, 255}, nbg = {255, 0, 255, 255};
    std::vector<Label> menu;
    // std::cout <<" adding play\n";
    menu.push_back(Label("Play"));
    menu.push_back(Label("Options"));
    menu.push_back(Label("About"));
    menu.push_back(Label("Exit"));
    UIColor changeColor(nbg, nfg);
    // std::cout << " change font\n";
    UIFont changeFont(newFont);
    UIColor revertCol(rfg, rbg);
    // std::cout << " revert font\n";
    UIFont revertFont(revFont);
    // std::cout << " full reverter\n";
    multiCommand<UIelement> reverter;
    reverter.push(revertCol);
    reverter.push(revertFont);
    for(UIelement& ui : menu){
        Mcon.push(ui);
    }
    // std::cout << " setting font\n";
    Mcon.setCol1(rfg);
    Mcon.setCol2(rbg);
    Mcon.setFont(revFont);
    Mcon.onFocus(&changeColor);
    Mcon.onClick(&changeFont);
    Mcon.onRevert(&reverter);
    InputManager input;
    SDL_Texture* texture;
    bool oldclick = false;
    int size = Mcon.getsize();
    WINDOW win("UIContainer Test");
    Mcon.setPos(win.getw()/2, win.geth()/2);
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    std::vector<UIelement*>& UIlist = Mcon.getList();
    while(!input.shouldQuit()){
        input.update();
        SDL_Point point;
        SDL_GetMouseState(&point.x, &point.y);
        Mcon.update(input);
        Mcon.render(win.getren());
        //Mcon.render(win.getren(), texture);
        win.pst();
        win.clr();
        SDL_Delay(33);
    }
    return 0;
}
