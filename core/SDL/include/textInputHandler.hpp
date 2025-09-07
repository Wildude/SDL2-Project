#pragma once
#include "inputManager.hpp"
class TextInputHandler : public InputManager {
    public:
    TextInputHandler(bool use = false, std::string* whichtext = NULL);
    void setTextUse(bool use);
    // checks if the input handler is on text input mode
    bool checkText();
    bool getTextState() const;
    ~TextInputHandler();
    void update();
    const std::string& getText() const ;
    void clearText();
    /* inline */ void setInput(std::string& the_str);
    /* inline */ void setInput(std::string* the_str = NULL);
    void setQuitCase(SDL_Scancode quiter = SDL_SCANCODE_RETURN);
    std::string* getInputref() const ;
    private:
    void startText();
    bool useText;
    std::string inputText; // Stores the text input
    std::string* textTo;
    SDL_Scancode quitCase;
};