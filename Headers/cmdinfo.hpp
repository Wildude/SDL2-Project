// command interface
/* Basic UI Command Effects
✅ On Hover (mouse over)
Effect	Purpose
Text color change	Highlights interactiveness
Underline or bold	Indicates it's clickable
Cursor change (e.g., hand)	Visual feedback (OS-level support)
Background highlight	Emphasizes UI component
Tooltip display	Shows extra info or hint
Shadow or glow effect	Adds depth or focus

✅ On Click (mouse press or release)
Effect	Purpose
Text color flash	Immediate visual feedback
Sound effect	Auditory feedback
Trigger an action	Perform a command/callback
Slight shrink/push-down	Feels like a "button" press
Remove focus from others	UI state change
Disable or change state	E.g. toggling an option

✅ On Focus (keyboard/tab or programmatic)
Effect	Purpose
Dashed or glowing border	Shows it’s ready to interact
Keyboard input enabled	Accept text or commands
Highlighted background	Matches other UI focus behaviors
ARIA/accessibility cue	Important for screen readers
*/
/* Additional UI Command Effects
Drag (start, move, end)

Key press / key release

Mouse wheel scroll

Double click

Resize

Touch / multi-touch gestures

Blur / Unfocus

Mouse enter / leave
*/
ChangeStringCommand<T> changestr;
    SDL_Scancode quitCase;
    TextInputHandler* inputHandler;
    InputStringCommand(TextInputHandler* input = NULL, T* ref = NULL, 
        string* textN = NULL, SDL_Scancode quiter = SDL_SCANCODE_ESCAPE) : 
        command<T>(ref), inputHandler(input), quitCase(quiter), changestr(ref, textN){

    }
    void setquitCase(SDL_Scancode quiter = SDL_SCANCODE_ESCAPE){
        quitCase = quiter;
    }
    void setInputer(TextInputHandler& inputH){
        inputHandler = &inputH;
    }
    void setInputer(TextInputHandler* inputH = NULL){
        inputHandler = inputH;
    }
    TextInputHandler* getInputer() const{
        return inputHandler;
    }
    inline bool iswriting() {
        return (inputHandler && inputHandler->getTextState());
    }
    inline bool iswritingON(){
        return inputHandler && inputHandler->getInputref() == &changestr.getNewStrRef();
    }
    void checktext(){
        if(!iswriting())
            // cout << " quitcase\n";
            setwriting(false);
        }
        else if(iswritingON()){
            changestr.execute();
        }
    }
    void setwriting(bool write){
        // cout << " setting writing to false/true\n";
        if(!write){
            // cout << " quit textmode\n";
            if(iswritingON()){
                inputHandler->setTextUse(false);
                inputHandler->setInput(NULL);
            }
        }
    }
    inline void setStrRef(string* textto = NULL){
        changestr.setStrRef(textto);
    }
    inline void setStrRef(string& textto){
        changestr.setStrRef(textto);
    }
    string& getNewStrRef(){
        return changestr.getNewStrRef();
    }
    void execute() override {
        // cout << " exec inbox\n";
        if(!inputHandler){
            //cout << " cmd error no inputer\n";
            return;
        }
        if(!command<T>::ref){
            //cout << " no ref\n";
            return;
        }
        //else cout << " there's reference\n";
        //cout << " cmd writing\n";
        if(!iswriting() || !iswritingON()){
            // cout << " rewriting\n";
            inputHandler->clearText();
        }
        //else cout << " just writing\n";
        inputHandler->setInput(&changestr.getNewStrRef());
        if(!inputHandler->checkText())inputHandler->setTextUse(true);
        changestr.execute();
    }