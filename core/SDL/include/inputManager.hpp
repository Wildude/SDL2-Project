#pragma once
#include <SDL2/SDL.h>
#include <array>
#include <vector>
inline const char* GetMouseButtonName(Uint8 button) {
    switch (button) {
        case SDL_BUTTON_LEFT:   return "LMB";
        case SDL_BUTTON_MIDDLE: return "MMB";
        case SDL_BUTTON_RIGHT:  return "RMB";
        case SDL_BUTTON_X1:     return "MB4";
        case SDL_BUTTON_X2:     return "MB5";
        default:                return "UMB";
    }
}
class InputManager {
    public:
    InputManager();

    void update();

    bool shouldQuit() const ;

    // Keyboard input
    bool isKeyDown(SDL_Scancode key) const ;
    bool isKeyPressed(SDL_Scancode key) const;
    bool isKeyReleased(SDL_Scancode key) const ;

    // Delayed action support
    bool isKeyReady(SDL_Scancode key, int delayFrames = 100);
    bool isMouseReady(Uint8 button, int delayFrames = 100);
    // Mouse input
    bool isMouseDown(Uint8 button) const ;
    bool isMousePressed(Uint8 button) const ;
    bool isMouseReleased(Uint8 button) const ;

    int getMouseX() const ;
    int getMouseY() const ;
    const SDL_Point& getMouseP() const ;
    int getMouseWheelY() const ;
    const std::array<Uint32, SDL_NUM_SCANCODES>& getDelayCounters();
    const std::array<Uint32, 8>& getMouseDelayCounters();
    const std::array<Uint32, SDL_NUM_SCANCODES>& getHoldCounters();
    const std::array<Uint32, 8>& getMouseHoldCounters();
    const std::vector<SDL_Scancode>& getKeyQueue();
    const std::vector<Uint8>& getMouseQueue();
    const std::vector<SDL_Scancode>& getReleaseQueue();
    const std::vector<Uint8>& getMouseReleaseQueue();
    std::array<bool, SDL_NUM_SCANCODES>& getKeyDowns();
    protected:
    void updateDelays();
    bool quit = false;

    // Keyboard states
    std::array<bool, SDL_NUM_SCANCODES> keyDown;
    std::array<bool, SDL_NUM_SCANCODES> keyPressed;
    std::array<bool, SDL_NUM_SCANCODES> keyReleased;
    // Mouse states
    std::array<bool, 8> mouseDown{};
    std::array<bool, 8> mousePressed{};
    std::array<bool, 8> mouseReleased{};
    // Mouse Position
    SDL_Point mouseXY = {0, 0};
    // Mouse wheel
    int mouseWheelY = 0;
    // Delay counters
    std::array<Uint32, SDL_NUM_SCANCODES> keyDelayCounters;
    std::array<Uint32, 8> mouseDelayCounters{}; 
    // Hold counters
    std::array<Uint32, SDL_NUM_SCANCODES> keyHoldCounters;
    std::array<Uint32, 8> mouseHoldCounters{};
    // input queues for processing
    std::vector<SDL_Scancode> keyPressedQueue, keyReleasedQueue;
    std::vector<Uint8> mousePressedQueue, mouseReleasedQueue;

    protected: SDL_Event e;
};
// Important functions
// SDL_GetScancodeFromKey(SDL_Keycode key)
// SDL_GetKeyFromScancode(SDL_Scancode scancode)
// SDL_GetScancodeName(SDL_Scancode scancode)
// SDL_GetKeyName(SDL_Keycode key)