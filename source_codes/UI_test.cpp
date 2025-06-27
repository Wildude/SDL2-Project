#include "../Headers/inclusions.hpp"
int main(int argn, char** args){
    WINDOW win("GUI Test");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    cout << " creating play:\n";
    Label play("play");
    play.setPos(100, 100);
    SDL_Color rfg = {0, 0, 0, 255}, rbg = {255, 255, 255, 255};
    cout << " Creating new Font:\n";
    FONT newFont("../Fonts/ROCKB.ttf", 70);
    cout << " Creating rev Font:\n";
    FONT revFont("../Fonts/nyala.ttf", 70);
    cout << " setting play font:\n";
    play.setFont(revFont);
    play.setCol1(rfg);
    play.setCol2(rbg);
    SDL_Color nfg = {255, 0, 0, 255}, nbg = {0, 0, 255, 255};
    //
    UIColor changeColor(nbg, nfg);
    UIFont changeFont(newFont);
    UIColor revertCol(rfg, rbg);
    UIFont revertFont(revFont);
    revertCol.setref(play);
    revertFont.setref(play);
    UIMulticommand reverter;
    reverter.push(revertCol);
    reverter.push(revertFont);
    reverter.setref(play);
    play.onFocus(&changeColor);
    play.onClick(&changeFont);
    play.onRevert(&reverter);
    /*
    vector<Label> menu;
    menu.push_back(Label("Play"));
    menu.push_back(Label("Options"));
    menu.push_back(Label("About"));
    menu.push_back(Label("Exit"));
    
    UICommand* cmds [2]; // hover and revert
    cmds[0] = &changeColor;
    cmds[1] = &revert;
    */
    InputManager input;
    SDL_Texture* texture = NULL;
    bool oldclick = false;
    while(!input.shouldQuit()){
        input.update();
        SDL_Point point;
        bool click = false;
        bool revert = true;
        SDL_GetMouseState(&point.x, &point.y);
        play.update(input);
        play.render(win.getren());
        //Mcon.render(win.getren(), texture);
        win.pst();
        win.clr();
        SDL_Delay(33);
    }
}
