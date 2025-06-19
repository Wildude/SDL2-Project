#include "../Headers/inclusions.hpp"
int main(int argn, char** args){
    WINDOW win("GUI Test");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    vector<Label> menu;
    menu.push_back(Label("Play"));
    menu.push_back(Label("Options"));
    menu.push_back(Label("About"));
    menu.push_back(Label("Exit"));
    UIContainer Mcon;
    SDL_Color rfg = {0, 0, 0, 255}, rbg = {255, 255, 255, 255};
    SDL_Color nfg = {255, 0, 0, 255}, nbg = {0, 0, 255, 255};
    FONT newFont("../Fonts/ROCKBI.ttf", 15);
    FONT revFont = newFont;
    newFont.setStyle(TTF_STYLE_BOLD);
    UIColor changeColor(nbg, nfg);
    UIFont changeFont(newFont);
    UIColor revertCol(rfg, rbg);
    UIFont revertFont(revFont);
    for(UIelement& ui : menu){
        Mcon.push(ui);
    }
    Mcon.setFont(revFont);
    Mcon.setPos(win.getw()/2, win.geth()/2);
    multiCommand<UIelement> revert;
    revert.push(revertCol);
    revert.push(revertFont);
    UICommand* cmds [2]; // hover and revert
    cmds[0] = &changeColor;
    cmds[1] = &revert;
    Mcon.setCommands(cmds);
    InputManager input;
    SDL_Texture* texture;
    while(!input.shouldQuit()){
        input.update();
        SDL_Point point;
        bool click = false;
        SDL_GetMouseState(&point.x, &point.y);
        if(input.isMouseDown(SDL_BUTTON_LEFT)){
            click = true;
        }
        for(int i = 0; i < 4; i++){
            menu[i].mousepos = &point;
            menu[i].click = click;
            menu[i].render(win.getren(), texture);
        }
        //Mcon.render(win.getren(), texture);
        win.pst();
        win.clr();
        SDL_Delay(33);
    }
}
