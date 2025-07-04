// testing states and transitions between states:
#include "../Headers/inclusions.hpp"
WINDOW win("DropDown Test");
SDL_Texture* texture;
int main(int argn, char** argc){
    // cout << " revfont\n";
    FONT revFont("../Fonts/ROCKB.ttf", 15);
    // cout << " newfont\n";
    FONT newFont("../Fonts/ROCKBI.ttf", 25);

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
    Dropdown theDropdown;
    //
    theDropdown.push("640 x 480");
    theDropdown.push("1024 x 768");
    theDropdown.push("1152 x 960");
    theDropdown.push("1378 x 850");
    //
    theDropdown.setCol1(rfg);
    theDropdown.setCol2(rbg);
    theDropdown.setFont(revFont);

    theDropdown.onFocus((&changeColor));

    theDropdown.onClick((&clicker));

    theDropdown.onRevert((&reverter));

    clicker.push(changeFont);
    TextInputHandler input;

    win.crtB();
    SDL_Color clearcol = {255, 255, 255, 255};
    theDropdown.setPos(win.getw()/8, win.getw()/8);
    //texture = texturei[0];
    TextBox boxied("Boxied");
    boxied.setfont(newFont);
    boxied.setboxpos(0, 0);
    while(!input.shouldQuit()){
        win.clr(clearcol);
        input.update();
        SDL_Point mpos;
        SDL_GetMouseState(&mpos.x, &mpos.y);
        if(input.isMouseDown(SDL_BUTTON_RIGHT))theDropdown.setPos(mpos.x, mpos.y);
        boxied.settext(input.getText() == "" ? to_string(theDropdown.getBox()->w) + " x " + to_string(theDropdown.getBox()->h) : input.getText());
        boxied.draw(win.getren(), texture);
        theDropdown.update(input);
        theDropdown.render(win.getren(), 10);
        win.pst();
        SDL_Delay(33);
    }
    return 0;
}