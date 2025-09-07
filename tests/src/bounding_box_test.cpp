// bounding box test
#include <InputManager.hpp>
#include <TextBox.hpp>
#include <Texture.hpp>
#include <window.hpp>
#include <Box.hpp>
int main(int argn, char** args){
    WINDOW win("Bounding Box Test");
    win.crtB();
    
    // Create a bounding box

    Box bbox;
    std::string text = "Content";
    // fits near 150
    TextBox thetext;
    thetext.settext(text);
    bbox.setSize(thetext.getBox().w, thetext.getBox().h);
    thetext.setboxpos(win.getw()/2 - thetext.getBox().w/2, win.geth()/2 - thetext.getBox().h/2);
    bbox.setpos(thetext.getBox().x, thetext.getBox().y);
    bbox.setpadding(15);
    bbox.setborder(10);
    bbox.setmargin(5);
    // Set the color for the bounding box
    SDL_Texture* texture = NULL;
    InputManager input;
    while(!input.shouldQuit()){
        input.update();
        win.set_rencol(255, 255, 255, 255);
        win.clr();
        thetext.draw(win.getren(), texture);
        win.set_rencol(255, 0, 0, 255); // contentrect is red
        SDL_Rect 
        fullbox = bbox.fullRect(),
        borderbox = bbox.borderBox(),
        paddingbox = bbox.paddingBox(),
        marginBox = bbox.marginBox();
        // Render the bounding box
        SDL_RenderDrawRect(win.getren(), &bbox.getcontent());
        win.set_rencol(0, 0, 255, 255); // padding rect is blue
        TEXTURE::drawRect(paddingbox, win.getren(), (int)bbox.padavg());
        win.set_rencol(0, 255, 0, 255); // border rect is green
        TEXTURE::drawRect(borderbox, win.getren(), (int)bbox.borderavg());
        win.set_rencol(0, 0, 0, 255); // margin rect is black
        TEXTURE::drawRect(marginBox, win.getren(), (int)bbox.marginavg());
        // Wait for a while to see the result
        win.pst();
        SDL_Delay(16);
    }
    return 0;
}