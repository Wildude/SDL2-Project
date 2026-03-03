// testing states and transitions between states:
#include <GUI.hpp>
#include <TextBox.hpp>
#include <window.hpp>
#include <InputManager.hpp>
WINDOW win("LabelArea Test");
SDL_Texture* texture;
int main(int argn, char** argc){
    // std::cout << " revfont\n";
    FONT revFont("../Fonts/ROCK.ttf", 15);
    // std::cout << " newfont\n";
    FONT newFont("../Fonts/ROCKB.ttf", 15);

    SDL_Color rfg = {0, 0, 0, 255}, rbg = {255, 255, 255, 255};
    SDL_Color nfg = {0, 255, 0, 255}, nbg = {0, 0, 255, 255};
    //
    UIColor changeColor(nfg, nbg);
    // std::cout << " change font\n";
    UIFont changeFont(newFont);
    UIColor revertCol(rfg, rbg);
    // std::cout << " revert font\n";
    UIFont revertFont(revFont);
    // std::cout << " full reverter\n";
    // multicommands
    
    multiCommand<UIelement> reverter, clicker;

    reverter.push(revertCol);
    reverter.push(revertFont);

    clicker.push(changeFont);
    LabelArea theLabelArea;
    //
    theLabelArea.setCol1(rfg);
    theLabelArea.setCol2(rbg);
    theLabelArea.setFont(revFont);
    //
    theLabelArea.push("LabelArea (Paragraph UI) v1.0");
    theLabelArea.push("This is the Paragraph UI element");
    theLabelArea.push("Every line is drawn using the same Texture of a LabelUI element.");
    theLabelArea.push("Thus Texture deletion and recreation happens for every line of text every frame.");
    theLabelArea.push("This is not very efficient and so improvements (like Texture atlas) are required.");
    //
    theLabelArea.onFocus((&changeFont));

    theLabelArea.onClick((&changeColor));

    theLabelArea.onRevert((&reverter));

    TextInputHandler input;

    win.crtB();
    SDL_Color clearcol = {255, 255, 255, 255};
    theLabelArea.setPos(win.getw()/8, win.getw()/8);
    //texture = texturei[0];
    TextBox boxied("Boxied");
    boxied.setfont(newFont);
    boxied.setboxpos(0, 0);
    while(!input.shouldQuit()){
        win.clr(clearcol);
        input.update();
        SDL_Point mpos;
        SDL_GetMouseState(&mpos.x, &mpos.y);
        if(input.isMouseDown(SDL_BUTTON_RIGHT))theLabelArea.setPos(mpos.x, mpos.y);
        boxied.settext(input.getText() == "" ? std::to_string(theLabelArea.getBox()->w) + " x " + std::to_string(theLabelArea.getBox()->h) : input.getText());
        boxied.draw(win.getren(), texture);
        theLabelArea.update(input);
        theLabelArea.render(win.getren(), 2);
        win.pst();
        SDL_Delay(33);
    }
    return 0;
}