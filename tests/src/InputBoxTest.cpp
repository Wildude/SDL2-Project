// testing states and transitions between states:
#include <GUI.hpp>
#include <TextBox.hpp>
#include <window.hpp>
#include <InputManager.hpp>
WINDOW win("InputBox Test");
SDL_Texture* texture;
int main(int argn, char** argc){
    // std::cout << " revfont\n";
    FONT revFont("../Fonts/ROCKB.ttf", 15);
    // std::cout << " newfont\n";
    FONT newFont("../Fonts/ROCKBI.ttf", 15);

    SDL_Color rfg = {0, 0, 0, 255}, rbg = {255, 255, 255, 255};
    SDL_Color nfg = {255, 0, 0, 255}, nbg = {0, 0, 255, 255};
    //
    UIColor changeColor(nfg, nbg);
    // std::cout << " change font\n";
    UIFont changeFont(newFont);
    UIColor revertCol(rfg, rbg);
    // std::cout << " revert font\n";
    UIFont revertFont(revFont);
    // std::cout << " full reverter\n";
    multiCommand<UIelement> reverter;

    reverter.push(revertCol);
    reverter.push(revertFont);
    InputBox thebox("Easy Comer");
    thebox.setFont(revFont);

    thebox.onFocus((&changeColor));

    thebox.onClick((&changeFont));

    thebox.onRevert((&reverter));
    thebox.setPos(win.getw()/8, win.getw()/8);
    /*
    
    //changeFont.setref(thebox);
    
    */
    TextInputHandler input;

    
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    
    //texture = texturei[0];
    TextBox boxied("Boxied");
    boxied.setfont(newFont);
    boxied.setboxpos(0, 0);
    while(!input.shouldQuit()){
        win.clr();
        input.update();
        boxied.settext(input.getText() == "" ? std::to_string(thebox.getBox()->w) + " x " + std::to_string(thebox.getBox()->h) : input.getText());
        boxied.draw(win.getren(), texture);
        thebox.update(input);
        thebox.render(win.getren());
        win.pst();
        SDL_Delay(33);
    }
    return 0;
}