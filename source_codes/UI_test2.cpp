#include "../Headers/inclusions.hpp"
int main(int argn, char** args){
    // cout << " revfont\n";
    FONT revFont("../Fonts/ROCKB.ttf", 15);
    // cout << " newfont\n";
    FONT newFont("../Fonts/ROCKBI.ttf", 15);
    UIContainer Mcon;
    SDL_Color rfg = {0, 0, 0, 255}, rbg = {255, 255, 255, 255};
    SDL_Color nfg = {255, 0, 0, 255}, nbg = {0, 0, 255, 255};
    vector<Label> menu;
    // cout <<" adding play\n";
    menu.push_back(Label("Play"));
    menu.push_back(Label("Options"));
    menu.push_back(Label("About"));
    menu.push_back(Label("Exit"));
    UIColor changeColor(nbg, nfg);
    // cout << " change font\n";
    UIFont changeFont(newFont);
    UIColor revertCol(rfg, rbg);
    // cout << " revert font\n";
    UIFont revertFont(revFont);
    // cout << " full reverter\n";
    multiCommand<UIelement> reverter;
    reverter.push(revertCol);
    reverter.push(revertFont);
    for(UIelement& ui : menu){
        Mcon.push(ui);
    }
    // cout << " setting font\n";
    Mcon.setFont(revFont);
    InputManager input;
    SDL_Texture* texture;
    bool oldclick = false;
    int size = Mcon.getsize();
    WINDOW win("GUI Test");
    Mcon.setPos(win.getw()/2, win.geth()/2);
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    vector<UIelement*>& UIlist = Mcon.getList();
    while(!input.shouldQuit()){
        input.update();
        SDL_Point point;
        bool click = false;
        bool revert = true;
        SDL_GetMouseState(&point.x, &point.y);
        if(input.isMouseDown(SDL_BUTTON_LEFT)){
            click = true;
        }
        for(int i = 0; i < size; i++){
            // cout << " event " << i << endl;
            if(UIlist[i]->onHover(point, changeFont)){
                // cout << " hovered\n";
                if(!oldclick){
                    // cout << " clicked\n";
                    revert = false;
                }
                oldclick = UIlist[i]->onClick(point, click, changeColor);
                //if(!oldclick)// cout << " not clicked\n";
            }
            else{
                // cout << " not hovered\n";
                revert = true;
            } 
            if(revert){
                // cout << " reverting\n";
                reverter.setref(*UIlist[i]);
                // cout << " ref set\n";
                reverter.execute();
                // cout << " executed\n";
            }
        }
        Mcon.render(win.getren(), texture, 3);
        //Mcon.render(win.getren(), texture);
        win.pst();
        win.clr();
        SDL_Delay(33);
    }
    return 0;
}
