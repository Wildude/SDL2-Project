#include "../include/inputManager.hpp"
InputManager::InputManager() {
    keyDown.fill(false);
    //keyPressed.fill(false);
    keyReleased.fill(false);
    keyDelayCounters.fill(0);
    mouseDelayCounters.fill(0);
}

void InputManager::update() {
    // Reset transitional states
    //keyPressed.fill(false);
    keyReleased.fill(false);
    //mousePressed.fill(false);
    mouseReleased.fill(false);

    // Poll all events
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }

        if (e.type == SDL_KEYDOWN && !e.key.repeat) {
            SDL_Scancode sc = e.key.keysym.scancode;
            keyDown[sc] = true;
            //keyPressed[sc] = true;
        } else if (e.type == SDL_KEYUP) {
            SDL_Scancode sc = e.key.keysym.scancode;
            keyDown[sc] = false;
            keyReleased[sc] = true;
            keyDelayCounters[sc] = 0;
        }

        if (e.type == SDL_MOUSEBUTTONDOWN) {
            mouseDown[e.button.button] = true;
            //mouseDelayCounters[e.button.button]++;
            //mousePressed[e.button.button] = true;
        } else if (e.type == SDL_MOUSEBUTTONUP) {
            mouseDown[e.button.button] = false;
            mouseReleased[e.button.button] = true;
            mouseDelayCounters[e.button.button] = 0;
        }

        if (e.type == SDL_MOUSEMOTION) {
            mouseXY.x = e.motion.x;
            mouseXY.y = e.motion.y;
        }

        if (e.type == SDL_MOUSEWHEEL) {
            mouseWheelY = e.wheel.y;
        }
    }

    // Update key repeat delay counters
    updateDelays();

    mouseWheelY = 0; // Reset wheel each frame
}

bool InputManager::shouldQuit() const { return quit; }

// Keyboard input
bool InputManager::isKeyDown(SDL_Scancode key) const {
    //cout << " checking key: " << keyDown[key] <<endl; 
    return keyDown[key]; 
}
//bool InputManager::isKeyJustPressed(SDL_Scancode key) const { return keyPressed[key]; }
bool InputManager::isKeyReleased(SDL_Scancode key) const { return keyReleased[key]; }

// Delayed action support
bool InputManager::isKeyReady(SDL_Scancode key, int delayFrames ){
    if(keyDown[key]){
        if(keyDelayCounters[key] && keyDelayCounters[key] < delayFrames){
            return false;
        }
        else{
            if(key == SDL_SCANCODE_INSERT){
                // cout << " evaluated\n";
            }
            keyDelayCounters[key] = 0;
            return true;
        }
    }
    else return false;
}
bool InputManager::isMouseReady(Uint8 button, int delayFrames ){
    if(mouseDown[button]){
        if(mouseDelayCounters[button] > 1 && mouseDelayCounters[button] < delayFrames){
            //cout << " mouse not ready: " << mouseDelayCounters[button] << endl;
            mouseDelayCounters[button]++;
            return false;
        }
        else{
            //cout << " mouse ready: " << endl;
            mouseDelayCounters[button] = 0;
            mouseDelayCounters[button] = 2; // Reset to 1 to avoid immediate re-triggering
            return true;
        }
    }
    else return false;
}
// Mouse input
bool InputManager::isMouseDown(Uint8 button) const { return mouseDown[button]; }
//bool InputManager::isMouseJustPressed(Uint8 button) const { return mousePressed[button]; }
bool InputManager::isMouseReleased(Uint8 button) const { return mouseReleased[button]; }

int InputManager::getMouseX() const { return mouseXY.x; }
int InputManager::getMouseY() const { return mouseXY.y; }
const SDL_Point& InputManager::getMouseP() const { return mouseXY; }
int InputManager::getMouseWheelY() const { return mouseWheelY; }
const std::array<int, SDL_NUM_SCANCODES>& InputManager::getDelayCounters(){
    return keyDelayCounters;
}
std::array<bool, SDL_NUM_SCANCODES>& InputManager::getKeyDowns(){
    return keyDown;
}
void InputManager::updateDelays() {
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
        if (keyDown[i]) {
            keyDelayCounters[i]++;
        } else {
            keyDelayCounters[i] = 0;
        }
    }
}