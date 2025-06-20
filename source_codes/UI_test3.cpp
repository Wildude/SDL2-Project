#include "../Headers/inclusions.hpp"
int main(int argn, char** args){
    // cout << " revfont\n";
    script GUI("../Files/scripts/UI_test.lua");
    GUI.getglobalA("MainFont"); // get mainfont
    GUI.getfield("path"); // get path
    string pathes = GUI.tostr(); // take path value
    GUI.pop(); // pop path
    Uint8 r, g, b, a;
    GUI.getfield("size"); // get size
    FONT revFont(pathes.c_str(), GUI.tonum()); // take size value
    GUI.pop(); // pop size
    GUI.pop(); // pop mainfont
    // cout << " newfont\n";
    GUI.getglobalA("ChangeFont"); // get changefont
    GUI.getfield("path"); // get path
    pathes = GUI.tostr(); // take path value
    GUI.pop(); // pop path
    GUI.getfield("size"); // get size
    FONT newFont(pathes.c_str(), GUI.tonum()); // get size value
    GUI.pop(); // pop size
    GUI.pop(); // pop changefont
    UIContainer Mcon;
    GUI.getglobalA("MainColor"); // get maincolor
    GUI.getfield("fcolor"); // get fcolor
    GUI.getfield("r"); // get r
    r = (Uint8)GUI.tonum(); // take r
    GUI.pop(); // pop r
    GUI.getfield("g"); // get g
    g = (Uint8)GUI.tonum(); // take g
    GUI.pop(); // pop g
    GUI.getfield("b"); // get b
    b = (Uint8)GUI.tonum(); // take b
    GUI.pop(); // pop b
    GUI.getfield("a"); // get a 
    a = (Uint8)GUI.tonum(); // take a
    GUI.pop(); // pop a
    GUI.pop(); // pop fcolor
    SDL_Color rfg = {r, g, b, a}; 
    GUI.getfield("bcolor"); // get bcolor
    GUI.getfield("r"); // get r
    r = (Uint8)GUI.tonum(); // take r
    GUI.pop(); // pop r
    GUI.getfield("g"); // get g
    g = (Uint8)GUI.tonum(); // take g
    GUI.pop(); // pop g
    GUI.getfield("b"); // get b
    b = (Uint8)GUI.tonum(); // take b
    GUI.pop(); // pop b
    GUI.getfield("a"); // get a
    a = (Uint8)GUI.tonum(); // take a
    GUI.pop(); // pop a
    GUI.pop(); // pop bcolor
    GUI.pop(); // pop maincolor
    SDL_Color rbg = {r, g, b, a};
    GUI.getglobalA("ChangeColor"); // get changecolor
    GUI.getfield("fcolor"); // get fcolor
    GUI.getfield("r"); // get r
    r = (Uint8)GUI.tonum(); // take r
    GUI.pop(); // pop r
    GUI.getfield("g"); // get g
    g = (Uint8)GUI.tonum(); // take g
    GUI.pop(); // pop g
    GUI.getfield("b"); // get b
    b = (Uint8)GUI.tonum(); // take b
    GUI.pop(); // pop b
    GUI.getfield("a"); // get a 
    a = (Uint8)GUI.tonum(); // take a
    GUI.pop(); // pop a
    GUI.pop(); // pop fcolor
    SDL_Color nfg = {r, g, b, a};
    GUI.getfield("bcolor"); // get bcolor
    GUI.getfield("r"); // get r
    r = (Uint8)GUI.tonum(); // take r
    GUI.pop(); // pop r
    GUI.getfield("g"); // get g
    g = (Uint8)GUI.tonum(); // take g
    GUI.pop(); // pop g
    GUI.getfield("b"); // get b
    b = (Uint8)GUI.tonum(); // take b
    GUI.pop(); // pop b
    GUI.getfield("a"); // get a
    a = (Uint8)GUI.tonum(); // take a
    GUI.pop(); // pop a
    GUI.pop(); // pop bcolor
    GUI.pop(); // pop changecolor
    SDL_Color nbg = {r, g, b, a};
    vector<Label> menu;
    // cout <<" adding play\n";
    GUI.getglobalA("MenuItems"); // get menuitems
    GUI.getEi(1); // get 1th item
    menu.push_back(Label(GUI.tostr())); // take 1th item
    GUI.pop(); // pop 1th item
    GUI.getEi(2); // get 2th item
    menu.push_back(Label(GUI.tostr())); // take 2th item
    GUI.pop(); // pop 2th item
    GUI.getEi(3); // get 3th item
    menu.push_back(Label(GUI.tostr())); // take 3th item
    GUI.pop(); // pop 3th item
    GUI.getEi(4); // get 4th item
    menu.push_back(Label(GUI.tostr())); // take 4th item
    GUI.pop(); // pop 4th item
    GUI.pop(); // pop menuitems
    UIColor changeColor(nfg, nbg);
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
    WINDOW win("GUI Test", 0, 0, 640, 480, SDL_WINDOW_FULLSCREEN);
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
