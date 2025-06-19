// command interface
/*
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
template <class T>
struct command{
    T* ref;
    command(): ref(NULL){}
    command(T& uref){
        ref = &uref;
    }
    virtual void setref(T& uref){
        cout << " setting reference\n";
        ref = &uref;
    }
    virtual const T* getref() const {
        cout << " getting reference\n";
        return ref;
    }
    virtual void execute() = 0; // Pure virtual function for executing the command
    virtual ~command() = default; // Virtual destructor for proper cleanup
};
template <class T>
struct ChangeFontCommand : public command<T>{
    FONT* fontRef;
    FONT newFont;
    ChangeFontCommand() : fontRef(NULL) {}
    ChangeFontCommand(FONT& font) : fontRef(&font) {}
    ChangeFontCommand(const FONT& nFont): newFont(nFont){}
    void setRef(FONT& font){
        cout << " setting font references\n";
        fontRef = &font;
    }
    void setNew(const FONT& font){
        cout << " setting new font\n";
        newFont = font;
    }
    void execute() override {
        cout << " executing font change\n";
        *fontRef = newFont; // Change the font to the new value
    } 
};
template <class T>
struct ChangeColorCommand : public command<T>{
    SDL_Color* bg, *fg;
    SDL_Color nb, nf;
    ChangeColorCommand() : bg(NULL), fg(NULL){}
    ChangeColorCommand(SDL_Color& bref, SDL_Color& fref) : bg(&bref), fg(&fref){}
    ChangeColorCommand(const SDL_Color& nbg, const SDL_Color& nfg): nb(nbg), nf(nfg){}
    void setRef(SDL_Color& bref, SDL_Color& fref){
        cout << " setting color references\n";
        bg = &bref;
        fg = &fref;
    }
    void setNew(const SDL_Color& bnew, const SDL_Color& fnew){
        cout << " setting new colors\n";
        nb = bnew;
        nf = fnew;
    }
    void execute() override {
        cout << " executing color change\n";
        *bg = nb;
        *fg = nf;
    }
};
template <class T>
struct multiCommand : public command<T>{
    vector<command<T>*> commands;
    mutliCommand(){}
    mutliCommand(vector<command<T>*>& cmds){
        commands = cmds;
    }
    void push(command<T>& cmd){
        push(&cmd);
    }
    void push(command<T>* cmd){
        cout << " pushing command\n";
        commands.push_back(cmd);
    }
    void execute(){
        cout << " executing multicommand\n";
        for(command<T>* cmd : commands)
        cmd->execute();
    }
};
// for simple commands
template <class T>
struct doCommand : public command<T>{
    T (*cmd)();
    doCommand(){}
    doCommand(T (*cmd_)()) : cmd(cmd_) {}
    const doCommand& operator=(T (*cmd_)()){
        if(this->cmd != cmd_){
            cmd = cmd_;
        }
        return *this;
    }
    void execute() override {
        cmd();
    }
};
