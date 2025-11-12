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
    keyPressed.fill(false);
    keyReleased.fill(false);
    mousePressed.fill(false);
    mouseReleased.fill(false);
    mouseWheelY = 0;
    // Poll all events
    // Clear all events in this mode
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_TEXTINPUT:
                if(!useText){
                    textTo = NULL;
                    break;
                }
                inputText += e.text.text; 
                break;
            case SDL_KEYDOWN:
                if (!e.key.repeat) {
                    SDL_Scancode sc = e.key.keysym.scancode;
                    keyDown[sc] = true;
                    keyPressed[sc] = true;
                    if (e.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty() && useText)
                        inputText.pop_back();
                    else if (
                        e.key.keysym.sym == SDL_GetKeyFromScancode(quitCase) || 
                        e.key.keysym.sym == SDLK_ESCAPE
                    ) {
                        useText = false;
                        SDL_StopTextInput();  // stop when exiting
                        textTo = NULL;
                    }
                }
                break;
            case SDL_KEYUP:
                keyDown[e.key.keysym.scancode] = false;
                keyReleased[e.key.keysym.scancode] = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseDown[e.button.button] = true;
                mousePressed[e.button.button] = true;
                break;
            case SDL_MOUSEBUTTONUP:
                mouseDown[e.button.button] = false;
                mouseReleased[e.button.button] = true;
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