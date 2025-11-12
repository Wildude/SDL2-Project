// This code is to test input processing functionality in the InputManager class.
#include <inputManager.hpp>
#include <window.hpp>
#include <iostream>
#include <GUI.hpp>
#include <textbox.hpp>
int main(int argn, char** args){
    FONT newFont("../Fonts/nyala.ttf", 15);
    WINDOW win("InputTest");
    win.crtB();
    InputManager inputMgr;
    TextBox delayerBox(" Press any buttons and look at the input queue", newFont);
    delayerBox.setboxpos(50, 50);
    SDL_Texture* board = NULL;
    SDL_Rect gaugeOutline = {150, 100, 200, 30};
    SDL_Rect gaugeFill = {152, 102, 0, 26};
    std::vector<std::string> inputLog;
    while(!inputMgr.shouldQuit()){
        SDL_SetRenderDrawColor(win.getren(), 255, 255, 255, 255);
        win.clr();
        delayerBox.setboxpos(50, 50);
        delayerBox.settext(" Press any buttons and look at the input queue");
        delayerBox.draw(win.getren(), board);
        delayerBox.setboxpos(50, 80);
        delayerBox.settext(" Hold space to fill the gauge");
        delayerBox.draw(win.getren(), board);
        SDL_SetRenderDrawColor(win.getren(), 0, 0, 0, 0);
        SDL_RenderDrawRect(win.getren(), &gaugeOutline);
        inputMgr.update();
        // Log key presses
        if(inputMgr.getKeyQueue().size() > inputLog.size()){
            for(size_t i = inputLog.size(); i < inputMgr.getKeyQueue().size(); ++i){
                SDL_Scancode sc = inputMgr.getKeyQueue()[i];
                inputLog.push_back(SDL_GetScancodeName(sc));
            }
        }
        delayerBox.setboxpos(50, 100);
        delayerBox.settext(" Input Queue:");
        delayerBox.draw(win.getren(), board);
        for(int i = 0; i < inputLog.size(); i++){
            delayerBox.settext(inputLog[i].c_str());
            delayerBox.setboxpos(50, 120 + i * 20);
            delayerBox.draw(win.getren(), board);
        }
        float fillRatio = inputMgr.getHoldCounters()[SDL_SCANCODE_SPACE] / 2000.0f;
        if(fillRatio > 1.0f) fillRatio = 1.0f;
        gaugeFill.w = 196 * fillRatio;
        SDL_SetRenderDrawColor(win.getren(), 255, 0, 0, 0);
        SDL_RenderFillRect(win.getren(), &gaugeFill);
        win.pst();
    }
    return 0;
}
/*
for(int sc = SDL_SCANCODE_A; sc <= SDL_SCANCODE_Z; ++sc){
            if(inputMgr.isKeyPressed(static_cast<SDL_Scancode>(sc))){
                std::cout << "Key Pressed: " << SDL_GetScancodeName(static_cast<SDL_Scancode>(sc)) << std::endl;
            }
            if(inputMgr.isKeyReleased(static_cast<SDL_Scancode>(sc))){
                std::cout << "Key Released: " << SDL_GetScancodeName(static_cast<SDL_Scancode>(sc)) << std::endl;
            }
        }
        for(Uint8 i = 0; i < 8; i++){
            if(inputMgr.isMousePressed(i)){
                std::cout << "MB pressed: " << i << std::endl;
            }
            if(inputMgr.isMouseReleased(i)){
                std::cout << "MB released: " << i << std::endl;
            }
        }
*/