#include "../include/textInputHandler.hpp"
TextInputHandler::TextInputHandler(bool use , std::string* whichtext ) : 
useText(use), textTo(whichtext), quitCase(SDL_SCANCODE_RETURN), InputManager(){
    if(useText)startText();
}
void TextInputHandler::setTextUse(bool use){
    useText = use;
}
// checks if the input handler is on text input mode
bool TextInputHandler::checkText(){
    if(!useText)SDL_StopTextInput();
    else SDL_StartTextInput();
    return useText;
}
bool TextInputHandler::getTextState() const{
    return useText;
}
TextInputHandler::~TextInputHandler() {
    SDL_StopTextInput(); // Stop listening for text input when done
}
void TextInputHandler::update() {
    if (useText){
        if (!SDL_IsTextInputActive()) SDL_StartTextInput();
    }
    // Only start text input once when entering text mode
    else if(SDL_IsTextInputActive()) SDL_StopTextInput();

    // Reset transitional states
    //keyPressed.fill(false);
    keyReleased.fill(false);
    //mousePressed.fill(false);
    mouseReleased.fill(false);

    // Poll all events
    // Clear all events in this mode
    while (SDL_PollEvent(&e)) {
        //cout << " still on text: "<< useText << endl;
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            //cout << " mouse button down\n";
            //cout << " mouse: " << (int)e.button.button << endl;
            mouseDown[e.button.button] = true;
            mouseDelayCounters[e.button.button]++;
            //mousePressed[e.button.button] = true;
        } 
        else if (e.type == SDL_MOUSEBUTTONUP) {
            //cout << " mouse button up\n";
            //cout << " mouse: " << (int)e.button.button << endl;
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
        if (e.type == SDL_KEYUP) {
            SDL_Scancode sc = e.key.keysym.scancode;
            keyDown[sc] = false;
            keyReleased[sc] = true;
            keyDelayCounters[sc] = 0;
        }
        if(!useText){
            textTo = NULL;
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
        }   
        else{
            if (e.type == SDL_TEXTINPUT) {
                inputText += e.text.text;
            } 
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
                    inputText.pop_back();
                } else if (
                    e.key.keysym.sym == SDL_GetKeyFromScancode(quitCase) || 
                    e.key.keysym.sym == SDLK_ESCAPE
                ) {
                    useText = false;
                    SDL_StopTextInput();  // stop when exiting
                    textTo = NULL;
                }
            }
            if(textTo)*textTo = inputText; // Update the textTo content to the current inputText
        }
    }
    // Update key repeat delay counters
    updateDelays();
    mouseWheelY = 0; // Reset wheel each frame
}
const std::string& TextInputHandler::getText() const {
    return inputText;
}

void TextInputHandler::clearText() {
    inputText.clear();
}
void TextInputHandler::setInput(std::string& the_str){
    textTo = &the_str;
}
void TextInputHandler::setInput(std::string* the_str ){
    textTo = the_str;
}
void TextInputHandler::setQuitCase(SDL_Scancode quiter ){
    quitCase = quiter;
}
std::string* TextInputHandler::getInputref() const {
    return textTo;
}
void TextInputHandler::startText(){
    SDL_StartTextInput(); // Start listening for text input
    inputText.clear();    // Initialize empty text buffer
}
bool useText;
std::string inputText; // Stores the text input
std::string* textTo;
SDL_Scancode quitCase;