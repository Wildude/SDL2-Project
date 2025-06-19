#include "../Headers/inclusions.hpp"
int main(int argn, char** args){
    WINDOW win("GUI Test");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    Label play("play");
    play.setPos(100, 100);
    SDL_Color rfg = {0, 0, 0, 255}, rbg = {255, 255, 255, 255};
    FONT newFont("../Fonts/ROCKBI.ttf", 70);
    FONT revFont = newFont;
    newFont.setStyle(TTF_STYLE_BOLD);
    play.setFont(newFont);
    play.setCol1(rfg);
    play.setCol2(rbg);
    SDL_Color nfg = {255, 0, 0, 255}, nbg = {0, 0, 255, 255};
    UIColor changeColor(nbg, nfg);
    UIFont changeFont(newFont);
    UIColor revertCol(rfg, rbg);
    UIFont revertFont(revFont);
    revertCol.setref(play);
    revertFont.setref(play);
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
    while(!input.shouldQuit()){
        cout << " running\n";
        input.update();
        SDL_Point point;
        bool click = false;
        SDL_GetMouseState(&point.x, &point.y);
        if(input.isMouseDown(SDL_BUTTON_LEFT)){
            click = true;
        }
        //goto just_render;
        play.mousepos = &point;
        play.click = click;
        if(play.onHover(changeFont)){
            //goto just_render;
            play.onClick(changeColor);
        }
        else {
            //goto just_render;
            revertFont.execute();
            revertCol.execute();
        }
        just_render:
        play.render(win.getren(), texture, 3);
        //Mcon.render(win.getren(), texture);
        win.pst();
        win.clr();
        SDL_Delay(33);
    }
}
