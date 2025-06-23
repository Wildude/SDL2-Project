// testing states and transitions between states:
#include "../Headers/inclusions.hpp"
WINDOW win("Menu State Test");
SDL_Texture* texture;
int currentState = 0;
string stater = "menu";
void changeState(){
    if(stater == "menu"){
        stater = "difficulty";
    }
    else stater = "menu";
}
int main(int argn, char** argc){
    // cout << " revfont\n";
    FONT revFont("../Fonts/ROCKB.ttf", 15);
    // cout << " newfont\n";
    FONT newFont("../Fonts/ROCKBI.ttf", 15);
    MenuState menust("Main Menu"), diffst("Difficulty Menu");
    StateManager StMan;
    StMan.pushState(&menust);
    menust.push(UIContainer());
    diffst.push(UIContainer());
    SDL_Color rfg = {0, 0, 0, 255}, rbg = {255, 255, 255, 255};
    SDL_Color nfg = {255, 0, 0, 255}, nbg = {0, 0, 255, 255};
    vector<Label> menu;
    vector<Label> diff;
    vector<Label> options;
    vector<Label> about;
    vector<Label> exit;
    // cout <<" adding play\n";
    menu.push_back(Label("Play"));
    menu.push_back(Label("Options"));
    menu.push_back(Label("About"));
    menu.push_back(Label("Exit"));
    // diffculty labels
    diff.push_back(Label("Easy"));
    diff.push_back(Label("Medium"));
    diff.push_back(Label("Hard"));
    //
    UIColor changeColor(nbg, nfg);
    // cout << " change font\n";
    UIFont changeFont(newFont);
    UIColor revertCol(rfg, rbg);
    // cout << " revert font\n";
    UIFont revertFont(revFont);
    // cout << " full reverter\n";
    ChangeStateCommand<UIelement> state_change(StMan, &diffst);
    multiCommand<UIelement> reverter, state_changer;
    reverter.push(revertCol);
    reverter.push(revertFont);
    state_changer.push(changeFont);
    state_changer.push(state_change);
    for(UIelement& ui : menu){
        menust.getUICs()[0].push(ui);
    }
    for(UIelement& ui : diff){
        diffst.getUICs()[0].push(ui);
    }   
    // cout << " setting font\n";
    menust.getUICs()[0].setFont(revFont);
    diffst.getUICs()[0].setFont(revFont);

    menust.getUICs()[0].onFocus((GameCommand*)&changeColor);
    diffst.getUICs()[0].onFocus((GameCommand*)&changeColor);

    menust.getUICs()[0].onClick((GameCommand*)&changeFont);
    diffst.getUICs()[0].onClick((GameCommand*)&changeFont);

    menust.getUICs()[0].onRevert((GameCommand*)&reverter);
    diffst.getUICs()[0].onRevert((GameCommand*)&reverter);

    InputManager input;
    bool oldclick = false;
    WINDOW win("GUI Test");
    menust.getUICs()[0].setPos(win.getw()/2, win.geth()/2);
    diffst.getUICs()[0].setPos(win.getw()/2, win.geth()/2);
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    //texture = texturei[0];
    doCommand<UIelement> dochange(changeState);
    multiCommand<UIelement> changestater;
    changestater.push(&changeColor);
    changestater.push(&dochange);
    menust.getUICs()[0].getList()[0]->onClick((GameCommand*)&state_changer);
    while(!input.shouldQuit()){
        if(StMan.getCurrent() == &diffst && input.isKeyDown(SDL_SCANCODE_ESCAPE))StMan.popState();
        input.update();
        //UIcons[currentState].render(win.getren(), texture);
        StMan.update(input);
        StMan.render(win.getren());
        win.pst();
        win.clr();
        SDL_Delay(33);
    }
    return 0;
}