// UIpanel + UIcontainer test
#include "../Headers/inclusions.hpp"
WINDOW win("UIPanel + Container Test");
SDL_Texture* texture;
int main(int argn, char** argc){
    // cout << " revfont\n";
    FONT revFont("../Fonts/ROCKB.ttf", 15);
    // cout << " newfont\n";
    FONT newFont("../Fonts/ROCKBI.ttf", 15);

    SDL_Color rfg = {0, 0, 0, 255}, rbg = {255, 255, 255, 255};
    SDL_Color nfg = {255, 0, 0, 255}, nbg = {0, 0, 255, 255};
    //
    uilog << " Change colors|\n";
    UIColor changeColor(nbg, nfg);
    // cout << " change font\n";
    UIFont changeFont(newFont);
    UIColor revertCol(rfg, rbg);
    // cout << " revert font\n";
    UIFont revertFont(revFont);
    // cout << " full reverter\n";
    vector<Label> menu;
    // cout <<" adding play\n";
    menu.push_back(Label("Play"));
    menu.push_back(Label("Options"));
    menu.push_back(Label("About"));
    menu.push_back(Label("Exit"));
    UIContainer menucont;
    ImageViewer theImage("../Images/Samples/AAU.png");
    for(Label& lb : menu)menucont.push(lb);
    UIPanel fullpanel;
    uilog << " pushing both\n";
    fullpanel.push(menucont);
    fullpanel.push(theImage);
    uilog << " setting font\n";
    fullpanel.setFont(revFont);
    //
    // multicommands
    multiCommand<UIelement> reverter, clicker;

    reverter.push(revertCol);
    reverter.push(revertFont);

    clicker.push(changeFont);
    
    theImage.setCol1(rfg);
    theImage.setCol2(rbg);
    theImage.setFont(revFont);

    theImage.onFocus((&changeColor));
    menucont.onFocus((&changeColor));

    theImage.onClick((&clicker));
    menucont.onClick((&changeFont));

    theImage.onRevert((&reverter));
    menucont.onRevert((&reverter));

    TextInputHandler input;

    WINDOW win("GUI Test");
    win.crtB();
    SDL_Color clearcol = {255, 255, 255, 255};
    fullpanel.setPos(win.getw()/8, win.getw()/8);
    //texture = texturei[0];
    TextBox boxied("Boxied");
    boxied.setfont(newFont);
    boxied.setboxpos(0, 0);
    while(!input.shouldQuit()){
        win.clr(clearcol);
        input.update();
        boxied.settext(input.getText() == "" ? to_string(fullpanel.getBox()->w) + " x " + to_string(fullpanel.getBox()->h) : input.getText());
        boxied.draw(win.getren(), texture);
        fullpanel.update(input);
        fullpanel.render(win.getren());
        win.pst();
        SDL_Delay(33);
    }
    return 0;
}