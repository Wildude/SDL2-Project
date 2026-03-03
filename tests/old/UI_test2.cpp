#include <GUI.hpp>
#include <TextBox.hpp>
#include <window.hpp>
#include <InputManager.hpp>
template <class T>
int simpleSearch(const std::vector<T>& vec, const T& target){
    int size = vec.size();
    for(int i = 0; i < size; i++){
        if(vec[i] == target){
            return i;
        }
    }
    return -1;
}
int main(int argn, char** args){
    // std::cout << " revfont\n";
    FONT revFont("../Fonts/ROCKB.ttf", 50);
    // std::cout << " newfont\n";
    FONT newFont("../Fonts/ROCKBI.ttf", 50);
    UIContainer Mcon;
    SDL_Color rfg = {255, 0, 0, 255}, rbg = {0, 255, 255, 255};
    SDL_Color nfg = {0, 255, 0, 255}, nbg = {255, 0, 0, 255};
    std::vector<Label> menu;
    // std::cout <<" adding play\n";
    menu.push_back(Label("Play"));
    menu.push_back(Label("Options"));
    menu.push_back(Label("About"));
    menu.push_back(Label("Exit"));
    UIColor changeColor(nbg, nfg);
    // std::cout << " change font\n";
    UIFont changeFont(newFont);
    UIColor revertCol(rbg, rfg);
    // std::cout << " revert font\n";
    UIFont revertFont(revFont);
    // std::cout << " full reverter\n";
    multiCommand<UIelement> reverter;
    reverter.push(revertCol);
    reverter.push(revertFont);
    for(UIelement& ui : menu){
        Mcon.push(&ui);
    }
    // std::cout << " setting font\n";
    Mcon.setCol1(rfg);
    Mcon.setCol2(rbg);
    Mcon.setFont(revFont);
    Mcon.onFocus(&changeFont);
    Mcon.onClick(&changeColor);
    Mcon.onRevert(&reverter);
    InputManager input;
    bool oldclick = false;
    int size = Mcon.getsize();
    WINDOW win("UIContainer Test");
    Mcon.setPos(win.getw()/2, win.geth()/2);
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    std::vector<UIelement*> UIlist = Mcon.getList();
    std::vector<uintptr_t> ptrlist;
    for(UIelement* ui : UIlist){
        ptrlist.push_back((uintptr_t)ui);
    }
    TextBox tbox("list: ", FONT("../Fonts/ROCKB.ttf", 20));
    SDL_Texture* board = NULL;
    while(!input.shouldQuit()){
        input.update();
        SDL_Point point;
        SDL_GetMouseState(&point.x, &point.y);
        if(input.isMouseDown(SDL_BUTTON_RIGHT)){
            Mcon.setPos(point.x, point.y);
        }
        tbox.setboxpos(10, 10);
        tbox.settext("list of pointers: ");
        tbox.draw(win.getren(), board, 2);
        for(int i = 0; i < size; i++){
            tbox.setboxpos(10, 10 + tbox.getBox().h * (i + 1));
            std::string ptrstr = "Pointer " + std::to_string(i) + ": " + std::to_string(ptrlist[i]);
            tbox.settext(ptrstr);
            tbox.draw(win.getren(), board, 2);
        }
        int w = 50 + tbox.getBox().w;
        tbox.setboxpos(w, 10);
        tbox.settext("ChangeFont points at " + std::to_string(simpleSearch(ptrlist, (uintptr_t)changeFont.getref())));
        tbox.draw(win.getren(), board, 2);
        tbox.setboxpos(w, 10 + tbox.getBox().h);
        tbox.settext("ChangeColor points at " + std::to_string(simpleSearch(ptrlist, (uintptr_t)changeColor.getref())));
        tbox.draw(win.getren(), board, 2);
        tbox.setboxpos(w, 10 + tbox.getBox().h * 2);
        tbox.settext("Reverter points at " + std::to_string(simpleSearch(ptrlist, (uintptr_t)reverter.getref())));
        tbox.draw(win.getren(), board, 2);
        //
        Mcon.update(input);
        Mcon.render(win.getren());
        //Mcon.render(win.getren(), texture);
        win.pst();
        win.clr();
        SDL_Delay(33);
    }
    return 0;
}
