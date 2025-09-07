// testing states and transitions between states:
#include <GUI.hpp>
#include <TextBox.hpp>
#include <window.hpp>
#include <InputManager.hpp>
WINDOW win("ImageUI Test");
SDL_Texture* texture;
int main(int argn, char** argc){
    // std::cout << " revfont\n";
    FONT revFont("../Fonts/ROCKB.ttf", 15);
    // std::cout << " newfont\n";
    FONT newFont("../Fonts/ROCKBI.ttf", 15);

    SDL_Color rfg = {0, 0, 0, 255}, rbg = {100, 155, 90, 255};
    SDL_Color nfg = {255, 0, 0, 255}, nbg = {128, 128, 128, 128};
    //
    UIColor changeColor(nfg, rbg);
    // std::cout << " change font\n";
    UIFont changeFont(newFont);
    UIColor revertCol(rfg, rbg);
    // std::cout << " revert font\n";
    UIFont revertFont(revFont);
    // std::cout << " full reverter\n";
    // multicommands
    multiCommand<UIelement> reverter, clicker;

    reverter.push(revertCol);
    reverter.push(revertFont);

    clicker.push(changeFont);
    CheckBox theCheckbox;
    theCheckbox.settype(TICKBOX);
    theCheckbox.setCol1(rfg);
    theCheckbox.setCol2(rbg);
    theCheckbox.setFont(revFont);

    theCheckbox.onFocus((&changeColor));

    theCheckbox.onClick((&clicker));

    theCheckbox.onRevert((&reverter));

    TextInputHandler input;

    WINDOW win("GUI Test");
    win.crtB();
    SDL_Color clearcol = {255, 255, 255, 255};
    theCheckbox.setPos(win.getw()/8, win.getw()/8);
    //texture = texturei[0];
    TextBox boxied("Boxied");
    boxied.setfont(newFont);
    boxied.setboxpos(0, 0);
    while(!input.shouldQuit()){
        win.clr(clearcol);
        input.update();
        boxied.settext(input.getText() == "" ? std::to_string(theCheckbox.getBox()->w) + " x " + std::to_string(theCheckbox.getBox()->h) : input.getText());
        boxied.draw(win.getren(), texture);
        theCheckbox.update(input);
        theCheckbox.render(win.getren(), 4);
        win.pst();
        SDL_Delay(33);
    }
    return 0;
}