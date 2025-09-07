#pragma once
#include <SDL2/SDL.h>
#include <array>
class InputManager {
    public:
    InputManager();

    void update();

    bool shouldQuit() const ;

    // Keyboard input
    bool isKeyDown(SDL_Scancode key) const ;
    //bool isKeyJustPressed(SDL_Scancode key) const { return keyPressed[key]; }
    bool isKeyReleased(SDL_Scancode key) const ;

    // Delayed action support
    bool isKeyReady(SDL_Scancode key, int delayFrames = 10);
    bool isMouseReady(Uint8 button, int delayFrames = 30);
    // Mouse input
    bool isMouseDown(Uint8 button) const ;
    //bool isMouseJustPressed(Uint8 button) const { return mousePressed[button]; }
    bool isMouseReleased(Uint8 button) const ;

    int getMouseX() const ;
    int getMouseY() const ;
    const SDL_Point& getMouseP() const ;
    int getMouseWheelY() const ;
    const std::array<int, SDL_NUM_SCANCODES>& getDelayCounters();
    std::array<bool, SDL_NUM_SCANCODES>& getKeyDowns();
    protected:
    void updateDelays();
    bool quit = false;
    std::array<bool, SDL_NUM_SCANCODES> keyDown;
    // std::array<bool, SDL_NUM_SCANCODES> keyPressed;
    std::array<bool, SDL_NUM_SCANCODES> keyReleased;
    std::array<int, SDL_NUM_SCANCODES> keyDelayCounters;
    std::array<int, 8> mouseDelayCounters{}; // SDL_BUTTON_LEFT...SDL_BUTTON_X2
    std::array<bool, 8> mouseDown{};      // SDL_BUTTON_LEFT...SDL_BUTTON_X2
    //std::array<bool, 8> mousePressed{};
    std::array<bool, 8> mouseReleased{};
    SDL_Point mouseXY = {0, 0};
    int mouseWheelY = 0;
    protected: SDL_Event e;
};