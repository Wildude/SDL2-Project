// testing states and transitions between states:
#include <GUI.hpp>
#include <TextBox.hpp>
#include <window.hpp>
#include <InputManager.hpp>
WINDOW win("SliderUI Test");
SDL_Texture* texture;
int currentState = 0;
int main(int argn, char** argc){
    FONT newFont("../Fonts/ROCKBI.ttf", 15);
    SDL_Color rfg = {0, 0, 255, 255}, rbg = {255, 0, 0, 255};
    SDL_Color nfg1 = {0, 150, 50, 255}, nbg1 = {0, 255, 255, 255};
    SDL_Color nfg2 = {0, 0, 255, 255}, nbg2 = {150, 25, 25, 255};
    //
    UIColor changeColor1(nbg1, nfg1), changeColor2(nbg2, nfg2);
    // std::cout << " change font\n";
    UIColor revertCol(rfg, rbg);
    // std::cout << " revert font\n";
    // std::cout << " full reverter\n";
    multiCommand<UIelement> reverter;
    reverter.push(revertCol);
    Slider theSlider;
    theSlider.setCol1(rfg);
    theSlider.setCol2(rbg);
    theSlider.setBox(90, 30);
    theSlider.onFocus((&changeColor1));

    theSlider.onClick((&changeColor2));

    theSlider.onRevert((&reverter));

    TextInputHandler input;

    WINDOW win("GUI Test");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    theSlider.setPos(win.getw()/8, win.getw()/8);
    //texture = texturei[0];
    TextBox boxied("");
    boxied.setfont(newFont);
    boxied.setboxpos(0, 0);
    while(!input.shouldQuit()){
        win.clr();
        input.update();
        //UIcons[currentState].render(win.getren(), texture);
        boxied.settext(std::to_string(theSlider.getportion()) + " : " + std::to_string(theSlider.getBox()->w) + " x " + std::to_string(theSlider.getBox()->h));
        boxied.draw(win.getren(), texture);
        theSlider.update(input);
        theSlider.render(win.getren());
        win.pst();
        SDL_Delay(33);
    }
    return 0;
}