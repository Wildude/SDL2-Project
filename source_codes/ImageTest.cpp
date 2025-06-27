// testing states and transitions between states:
#include "../Headers/inclusions.hpp"
WINDOW win("ImageUI Test");
SDL_Texture* texture;
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
    // multicommands
    multiCommand<UIelement> reverter, clicker;

    reverter.push(revertCol);
    reverter.push(revertFont);

    clicker.push(changeFont);
    ImageViewer theImage("../Images/Samples/AAU.png");
    theImage.settext("AAU");
    theImage.setCol1(rfg);
    theImage.setCol2(rbg);
    theImage.setFont(revFont);

    theImage.onFocus((&changeColor));

    theImage.onClick((&clicker));

    theImage.onRevert((&reverter));

    TextInputHandler input;

    WINDOW win("GUI Test");
    win.crtB();
    SDL_Color clearcol = {255, 255, 255, 255};
    theImage.setPos(win.getw()/8, win.getw()/8);
    //texture = texturei[0];
    TextBox boxied("Boxied");
    boxied.setfont(newFont);
    boxied.setboxpos(0, 0);
    while(!input.shouldQuit()){
        win.clr(clearcol);
        input.update();
        boxied.settext(input.getText() == "" ? to_string(theImage.getBox()->w) + " x " + to_string(theImage.getBox()->h) : input.getText());
        boxied.draw(win.getren(), texture);
        theImage.update(input);
        theImage.render(win.getren());
        win.pst();
        SDL_Delay(33);
    }
    return 0;
}