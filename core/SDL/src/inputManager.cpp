#include <inputManager.hpp>
InputManager::InputManager() {
    keyDown.fill(false);
    keyPressed.fill(false);
    keyReleased.fill(false);
    keyDelayCounters.fill(0);
    mouseDelayCounters.fill(0);
    keyHoldCounters.fill(0);
    mouseHoldCounters.fill(0);
}

void InputManager::update() {
    // Reset transitional states
    keyPressed.fill(false);
    keyReleased.fill(false);
    mousePressed.fill(false);
    mouseReleased.fill(false);
    mouseWheelY = 0; // Reset wheel each frame

    // Poll all events
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                if (!e.key.repeat) {
                    SDL_Scancode sc = e.key.keysym.scancode;
                    keyDown[sc] = true;
                    keyPressed[sc] = true;
                    keyPressedQueue.push_back(sc);
                }
                break;
            case SDL_KEYUP:
                keyDown[e.key.keysym.scancode] = false;
                keyReleased[e.key.keysym.scancode] = true;
                keyReleasedQueue.push_back(e.key.keysym.scancode);
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseDown[e.button.button] = true;
                mousePressed[e.button.button] = true;
                mousePressedQueue.push_back(e.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                mouseDown[e.button.button] = false;
                mouseReleased[e.button.button] = true;
                mouseReleasedQueue.push_back(e.button.button);
                break;
            case SDL_MOUSEMOTION:
                mouseXY.x = e.motion.x;
                mouseXY.y = e.motion.y;
                break;
            case SDL_MOUSEWHEEL:
                mouseWheelY = e.wheel.y;
                break;
        }
    }
    updateDelays();
}

bool InputManager::shouldQuit() const { return quit; }

// Keyboard input
bool InputManager::isKeyDown(SDL_Scancode key) const {
    //cout << " checking key: " << keyDown[key] <<endl; 
    return keyDown[key]; 
}
bool InputManager::isKeyPressed(SDL_Scancode key) const { return keyPressed[key]; }
bool InputManager::isKeyReleased(SDL_Scancode key) const { return keyReleased[key]; }

// Delayed action support
bool InputManager::isKeyReady(SDL_Scancode key, int delayFrames ){
    if(keyDown[key]){
        int diff = SDL_GetTicks() - keyDelayCounters[key];
        keyDelayCounters[key] = SDL_GetTicks();
        if(diff < delayFrames) return false;
        else return true;
    }
    else return false;
}
bool InputManager::isMouseReady(Uint8 button, int delayFrames ){
    if(mouseDown[button]){        
        int diff = SDL_GetTicks() - mouseDelayCounters[button];
        mouseDelayCounters[button] = SDL_GetTicks();
        if(diff < delayFrames) return false;
        else return true;
    }
    else return false;
}
// Mouse input
bool InputManager::isMouseDown(Uint8 button) const { return mouseDown[button]; }
bool InputManager::isMousePressed(Uint8 button) const { return mousePressed[button]; }
bool InputManager::isMouseReleased(Uint8 button) const { return mouseReleased[button]; }

int InputManager::getMouseX() const { return mouseXY.x; }
int InputManager::getMouseY() const { return mouseXY.y; }
const SDL_Point& InputManager::getMouseP() const { return mouseXY; }
int InputManager::getMouseWheelY() const { return mouseWheelY; }
const std::array<Uint32, SDL_NUM_SCANCODES>& InputManager::getDelayCounters(){
    return keyDelayCounters;
}
const std::array<Uint32, 8>& InputManager::getMouseDelayCounters(){
    return mouseDelayCounters;
}
const std::array<Uint32, SDL_NUM_SCANCODES>& InputManager::getHoldCounters(){
    return keyHoldCounters;
}
const std::array<Uint32, 8>& InputManager::getMouseHoldCounters(){
    return mouseHoldCounters;
}
std::array<bool, SDL_NUM_SCANCODES>& InputManager::getKeyDowns(){
    return keyDown;
}
const std::vector<SDL_Scancode>& InputManager::getKeyQueue(){
    return keyPressedQueue;
}
const std::vector<Uint8>& InputManager::getMouseQueue(){
    return mousePressedQueue;
}
const std::vector<SDL_Scancode>& InputManager::getReleaseQueue(){
    return keyReleasedQueue;
}
const std::vector<Uint8>& InputManager::getMouseReleaseQueue(){
    return mouseReleasedQueue;
}
void InputManager::updateDelays() {
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
        if (keyPressed[i]) {
            keyDelayCounters[i] = SDL_GetTicks();
        } else if(keyReleased[i]) {
            keyHoldCounters[i] = 0;
        }
        else if (keyDown[i]) {
            keyHoldCounters[i] = SDL_GetTicks() - keyDelayCounters[i];
        }
    }
    for(int i = 0; i < 8; ++i){
        if(mousePressed[i]){
            mouseDelayCounters[i] = SDL_GetTicks();
        }
        else if(mouseReleased[i]){
            mouseHoldCounters[i] = 0;
        }
        else if(mouseDown[i]){
            mouseHoldCounters[i] = SDL_GetTicks() - mouseDelayCounters[i];
        }
    }
}