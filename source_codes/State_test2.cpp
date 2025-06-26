// testing states and transitions between states:
#include "../Headers/inclusions.hpp"
WINDOW win("Menu + Difficuly State Test");
SDL_Texture* texture;
int main(int argn, char** argc){
    // cout << " revfont\n";
    FONT revFont("../Fonts/ROCKB.ttf", 15);
    // cout << " newfont\n";
    FONT newFont("../Fonts/ROCKBI.ttf", 15);
    MenuState menust("Main Menu"), diffst("Difficulty Menu");
    StateManager StMan;
    StMan.pushState(&diffst);
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
    UIContainer optionscont;
    ImageViewer theImage;
    for(Label& lb : diff)optionscont.push(lb);
    UIPanel fullpanel;
    fullpanel.push(optionscont);
    fullpanel.push(theImage);
    fullpanel.setFont(revFont);
    /*
    
    
    */
    //
    //
    UIColor changeColor(nbg, nfg);
    //
    fullpanel.getList()[1]->onFocus(&changeColor);
    // cout << " change font\n";
    UIFont changeFont(newFont);
    UIColor revertCol(rfg, rbg);
    // cout << " revert font\n";
    UIFont revertFont(revFont);
    // cout << " full reverter\n";
    ChangeStateCommand<UIelement> state_change(StMan, &diffst);
    multiCommand<UIelement> reverter, state_changer, imageChanger1, imageChanger2, imageChanger3;
    reverter.push(revertCol);
    reverter.push(revertFont);
    state_changer.push(changeFont);
    state_changer.push(state_change);
    imageChanger1.push(changeColor);
    imageChanger2.push(changeColor);
    imageChanger3.push(changeColor);
    /*
    
    */
    //
    // image changing code //
    /***********************************/
    string pathholder = "../Images/Samples/AAU.png";
    ChangeStringUICmd 
    //
    changepath1(NULL, &pathholder), 
    //
    changepath2(NULL, &pathholder),
    //
    changepath3(NULL, &pathholder);
    //
    //imageChanger1.push(changepath1);
    imageChanger2.push(changepath2);
    imageChanger3.push(changepath3);
    ///
    diff[0].onFocus(&imageChanger1);
    diff[1].onFocus(&imageChanger2);
    diff[2].onFocus(&imageChanger3);
    ///
    changepath1.setNewStr("../Images/Samples/Easy.png");
    changepath2.setNewStr("../Images/Samples/Medium.png");
    changepath3.setNewStr("../Images/Samples/Hard.png");
    //************************/

    for(UIelement& ui : menu){
        menust.getUICs()[0].push(ui);
    }
    diffst.getUICs()[0].push(fullpanel);   
    // cout << " setting font\n";
    menust.getUICs()[0].setFont(revFont);
    diffst.getUICs()[0].setFont(revFont);

    menust.getUICs()[0].onFocus((&changeColor));

    menust.getUICs()[0].onClick((&changeFont));
    diffst.getUICs()[0].onClick((&changeFont));

    menust.getUICs()[0].onRevert((&reverter));
    diffst.getUICs()[0].onRevert((&reverter));

    TextInputHandler input;
    menust.getUICs()[0].setPos(win.getw()/8, win.geth()/8);
    diffst.getUICs()[0].setPos(win.getw()/8, win.geth()/8);
    win.crtB();
    SDL_Color clearcol = {255, 255, 255, 255};
    menust.getUICs()[0].getList()[0]->onClick((&state_changer));
    TextBox boxied("Boxied");
    boxied.setfont(revFont);
    while(!input.shouldQuit()){
        win.clr(clearcol);
        if(StMan.getCurrent() == &diffst )
        {
            if(input.isKeyDown(SDL_SCANCODE_ESCAPE))StMan.popState();
            else theImage.givepath(pathholder);
        }
        input.update();
        boxied.settext(string(theImage.getpath()) + " "  + to_string(theImage.getBox()->w) + ", " + to_string(theImage.getBox()->h));
        boxied.draw(win.getren(), texture);
        StMan.update(input);
        StMan.render(win.getren());
        win.pst();
        SDL_Delay(33);
    }
    return 0;
}