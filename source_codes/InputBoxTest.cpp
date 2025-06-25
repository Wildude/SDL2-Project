// testing states and transitions between states:
#include "../Headers/inclusions.hpp"
WINDOW win("Menu State Test");
SDL_Texture* texture;
int currentState = 0;
string stater = "menu";
void changeState(){
    if(stater == "menu"){
        stater = "difficulty";
    }
    else stater = "menu";
}
int main(int argn, char** argc){
    // cout << " revfont\n";
    FONT revFont("../Fonts/ROCKB.ttf", 15);
    // cout << " newfont\n";
    FONT newFont("../Fonts/ROCKBI.ttf", 15);

    SDL_Color rfg = {0, 0, 0, 255}, rbg = {255, 255, 255, 255};
    SDL_Color nfg = {255, 0, 0, 255}, nbg = {0, 0, 255, 255};
    //
    UIColor changeColor(nbg, nfg);
    // cout << " change font\n";
    UIFont changeFont(newFont);
    UIColor revertCol(rfg, rbg);
    // cout << " revert font\n";
    UIFont revertFont(revFont);
    // cout << " full reverter\n";
    multiCommand<UIelement> reverter;

    reverter.push(revertCol);
    reverter.push(revertFont);

    InputBox thebox("Easy Comer");
    //changeFont.setref(thebox);
    thebox.setFont(revFont);

    thebox.onFocus((&changeColor));

    thebox.onClick((&changeFont));

    thebox.onRevert((&reverter));

    TextInputHandler input;

    WINDOW win("GUI Test");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    thebox.setPos(win.getw()/8, win.getw()/8);
    //texture = texturei[0];
    TextBox boxied("Boxied");
    boxied.setfont(newFont);
    boxied.setboxpos(0, 0);
    while(!input.shouldQuit()){
        win.clr();
        input.update();
        //UIcons[currentState].render(win.getren(), texture);
        boxied.settext(input.getText() == "" ? to_string(thebox.getBox()->w) + " x " + to_string(thebox.getBox()->h) : input.getText());
        boxied.draw(win.getren(), texture);
        thebox.update(input);
        thebox.render(win.getren(), texture);
        win.pst();
        SDL_Delay(33);
    }
    return 0;
}