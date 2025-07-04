// testing states and transitions between states:
#include "../Headers/inclusions.hpp"
WINDOW win("SpinBox Test");
SDL_Texture* texture;
int main(int argn, char** argc){
    // cout << " revfont\n";
    FONT revFont("../Fonts/ROCKB.ttf", 45);
    // cout << " newfont\n";
    FONT newFont("../Fonts/ROCKBI.ttf", 45);

    SDL_Color rfg = {0, 0, 0, 255}, rbg = {255, 255, 255, 255};
    SDL_Color nfg = {0, 255, 0, 255}, nbg = {0, 0, 255, 255};
    //
    UIColor changeColor(nfg, nbg);
    // cout << " change font\n";
    UIFont changeFont(newFont);
    UIColor revertCol(rfg, rbg);
    // cout << " revert font\n";
    UIFont revertFont(revFont);
    // cout << " full reverter\n";
    // multicommands
    multiCommand<UIelement> reverter, clicker;

    reverter.push(revertCol);
    reverter.push(revertFont);

    clicker.push(changeFont);
    SpinBox theSpinBox;
    //
    theSpinBox.setCol1(rfg);
    theSpinBox.setCol2(rbg);
    theSpinBox.setFont(revFont);
    //
    theSpinBox.onFocus((&changeColor));

    theSpinBox.onClick((&clicker));

    theSpinBox.onRevert((&reverter));

    TextInputHandler input;

    win.crtB();
    SDL_Color clearcol = {255, 255, 255, 255};
    theSpinBox.setPos(win.getw()/8, win.getw()/8);
    //texture = texturei[0];
    TextBox boxied("Boxied");
    boxied.setfont(newFont);
    boxied.setboxpos(0, 0);
    while(!input.shouldQuit()){
        win.clr(clearcol);
        input.update();
        SDL_Point mpos;
        SDL_GetMouseState(&mpos.x, &mpos.y);
        if(input.isMouseDown(SDL_BUTTON_RIGHT))theSpinBox.setPos(mpos.x, mpos.y);
        boxied.settext(input.getText() == "" ? to_string(theSpinBox.getBox()->w) + " x " + to_string(theSpinBox.getBox()->h) : input.getText());
        boxied.draw(win.getren(), texture);
        theSpinBox.update(input);
        theSpinBox.render(win.getren(), 10);
        win.pst();
        SDL_Delay(33);
    }
    return 0;
}