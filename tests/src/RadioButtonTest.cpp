// testing states and transitions between states:
#include <GUI.hpp>
#include <TextBox.hpp>
#include <window.hpp>
#include <InputManager.hpp>
WINDOW win("RadioButton Test");
SDL_Texture* texture;
int main(int argn, char** argc){
    // std::cout << " revfont\n";

    FONT revFont("../Fonts/ROCKB.ttf", 15);
    // std::cout << " newfont\n";
    FONT newFont("../Fonts/nyala.ttf", 15);

    SDL_Color rfg = {0, 0, 255, 255}, rbg = {100, 155, 90, 255};
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
    TextBox boxied("Boxied", newFont);
    boxied.setboxpos(0, 0);
    while(!input.shouldQuit()){
        win.clr(clearcol);
        input.update();
        SDL_Point mpos;
        SDL_GetMouseState(&mpos.x, &mpos.y);
        if(input.isMouseDown(SDL_BUTTON_RIGHT))theRadiobutton.setPos(mpos.x, mpos.y);
        boxied.settext(input.getText() == "" ? "Current: " + std::to_string(theRadiobutton.getCurrent()): input.getText());
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