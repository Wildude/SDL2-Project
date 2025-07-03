// testing states and transitions between states:
#include "../Headers/inclusions.hpp"
WINDOW win("RadioButton Test");
SDL_Texture* texture;
int main(int argn, char** argc){
    // cout << " revfont\n";
    FONT revFont("../Fonts/ROCKB.ttf", 15);
    // cout << " newfont\n";
    FONT newFont("../Fonts/ROCKBI.ttf", 15);

    SDL_Color rfg = {0, 0, 255, 255}, rbg = {100, 155, 90, 255};
    SDL_Color nfg = {255, 0, 0, 255}, nbg = {128, 128, 128, 128};
    //
    UIColor changeColor(nfg, rbg);
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
    RadioButton theRadiobutton;
    //
    theRadiobutton.push(CheckBox());
    theRadiobutton.push(CheckBox());
    theRadiobutton.push(CheckBox());
    theRadiobutton.push(CheckBox());
    //
    theRadiobutton.setCol1(rfg);
    theRadiobutton.setCol2(rbg);
    theRadiobutton.setFont(revFont);

    theRadiobutton.onFocus((&changeColor));

    theRadiobutton.onClick((&clicker));

    theRadiobutton.onRevert((&reverter));

    clicker.push(changeFont);
    CheckBox theCheckbox;
    theCheckbox.setCol1(rfg);
    theCheckbox.setCol2(rbg);
    theCheckbox.setFont(revFont);

    theCheckbox.onFocus((&changeColor));

    theCheckbox.onClick((&clicker));

    theCheckbox.onRevert((&reverter));

    theCheckbox.setPos(win.getw() - 100, win.geth() - 300);

    TextInputHandler input;

    win.crtB();
    SDL_Color clearcol = {255, 255, 255, 255};
    theRadiobutton.setPos(win.getw()/8, win.getw()/8);
    //texture = texturei[0];
    TextBox boxied("Boxied");
    boxied.setfont(newFont);
    boxied.setboxpos(0, 0);
    while(!input.shouldQuit()){
        win.clr(clearcol);
        input.update();
        SDL_Point mpos;
        SDL_GetMouseState(&mpos.x, &mpos.y);
        if(input.isMouseDown(SDL_BUTTON_RIGHT))theRadiobutton.setPos(mpos.x, mpos.y);
        boxied.settext(input.getText() == "" ? to_string(theRadiobutton.getBox()->w) + " x " + to_string(theRadiobutton.getBox()->h) + "(" + to_string(theRadiobutton.getCurrent())+ ")" : input.getText());
        boxied.draw(win.getren(), texture);

        theRadiobutton.update(input);
        theRadiobutton.render(win.getren(), 10);
        //theCheckbox.update(input);
        //theCheckbox.render(win.getren(), 10);
        win.pst();
        SDL_Delay(33);
    }
    return 0;
}