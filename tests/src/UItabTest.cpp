// UIpanel + UIcontainer test
#include <GUI.hpp>
#include <TextBox.hpp>
#include <window.hpp>
#include <InputManager.hpp>
WINDOW win("UItab Test");
SDL_Texture* texture;
int main(int argn, char** argc){
    std::ofstream uilog("../../Files/Data/GUI.log");
    // std::cout << " revfont\n";
    FONT revFont("../Fonts/ROCKB.ttf", 25);
    // std::cout << " newfont\n";
    FONT newFont("../Fonts/ROCKBI.ttf", 25);

    SDL_Color rfg = {0, 0, 0, 255}, rbg = {200, 200, 255, 255};
    SDL_Color nfg = {255, 0, 0, 255}, nbg = {0, 0, 255, 255};
    //
    uilog << " Change colors|\n";
    UIColor changeColor(nbg, nfg);
    // std::cout << " change font\n";
    UIFont changeFont(newFont);
    UIColor revertCol(rfg, rbg);
    // std::cout << " revert font\n";
    UIFont revertFont(revFont);
    // std::cout << " full reverter\n";
    std::vector<Label> menu, diff;
    // std::cout <<" adding play\n";
    menu.push_back(Label("Play"));
    menu.push_back(Label("Options"));
    menu.push_back(Label("About"));
    menu.push_back(Label("Exit"));
    //
    diff.push_back(Label("Easy"));
    diff.push_back(Label("Medium"));
    diff.push_back(Label("Hard"));
    //
    UIContainer menucont, diffcont;
    ImageViewer theImage("../Images/Samples/AAU.png");
    for(Label& lb : menu)menucont.push(lb);
    for(Label& lb : diff)diffcont.push(lb);
    UIPanel fullpanel;
    uilog << " pushing both\n";
    fullpanel.push(diffcont);
    fullpanel.push(theImage);
    uilog << " setting font\n";
    //
    // multicommands
    multiCommand<UIelement> reverter;

    reverter.push(revertCol);
    reverter.push(revertFont);
    UITab theTab;
    UIContainer emptycon;
    theTab.push(menucont);
    theTab.push(fullpanel);
    theTab.push(emptycon);
    theTab.push(emptycon);
    theTab.push(emptycon);
    theTab.push(emptycon);
    theTab.setFont(revFont);
    theTab.setCol1(rfg);
    theTab.setCol2(rbg);
    theTab.onFocus(&changeColor);
    theTab.onClick(&changeFont);
    theTab.onRevert(&reverter);
    theTab.setPos(win.getw()/8, win.geth()/8);
    /*
    
    */
    TextInputHandler input;
    win.crtB();
    SDL_Color clearcol = {255, 255, 255, 255};
    //texture = texturei[0];
    TextBox boxied("Boxied");
    boxied.setfont(newFont);
    boxied.setboxpos(0, 0);
    while(!input.shouldQuit()){
        win.clr(clearcol);
        input.update();
        boxied.settext(input.getText() == "" ? std::to_string(theTab.getBox()->w) + " x " + std::to_string(theTab.getBox()->h) : input.getText());
        boxied.draw(win.getren(), texture);
        theTab.update(input);
        theTab.render(win.getren());
        win.pst();
        SDL_Delay(33);
    }
    return 0;
}