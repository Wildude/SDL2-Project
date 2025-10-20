// testing states and transitions between states:
#include <GUI.hpp>
#include <TextBox.hpp>
#include <window.hpp>
#include <InputManager.hpp>
WINDOW win("RadioButton Test");
SDL_Texture* texture;
int main(int argn, char** argc){
    FONT newFont("../Fonts/nyala.ttf", 15);
    SDL_Color rfg = {0, 0, 255, 255}, rbg = {100, 155, 90, 255};
    SDL_Color nfg = {255, 0, 0, 255}, nbg = {128, 128, 128, 128};
    //
    UIColor changeColor(nfg, nbg);
    // std::cout << " change font\n";
    UIColor revertCol(rfg, rbg);
    // std::cout << " revert font\n";
    // std::cout << " full reverter\n";
    // multicommand
    CheckBox cbox;
    cbox.setPos(400, 20);
    cbox.onFocus(&changeColor);
    cbox.onRevert(&revertCol);

    RadioButton theRadiobutton;
    //
    theRadiobutton.push();
    theRadiobutton.push();
    theRadiobutton.push();
    theRadiobutton.push();
    //
    theRadiobutton.setCol1(rfg);
    theRadiobutton.setCol2(rbg);

    theRadiobutton.onFocus((&changeColor));
    theRadiobutton.onRevert((&revertCol));

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
        boxied.setboxpos(boxied.getBox().x, boxied.getBox().y + boxied.getBox().h);
        boxied.settext(input.getText() == "" ? "Fcurrent: " + std::to_string(theRadiobutton.getFCurrent()): input.getText());
        boxied.draw(win.getren(), texture);
        boxied.setboxpos(boxied.getBox().x, boxied.getBox().y - boxied.getBox().h);
        theRadiobutton.update(input);
        theRadiobutton.render(win.getren(), 10);
        cbox.update(input);
        cbox.render(win.getren(), 10);
        //theCheckbox.update(input);
        //theCheckbox.render(win.getren(), 10);
        win.pst();
        win.clr();
        SDL_Delay(33);
    }
    return 0;
}