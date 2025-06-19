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
struct command{
    command(){}
    virtual void execute() = 0; // Pure virtual function for executing the command
    virtual ~command() = default; // Virtual destructor for proper cleanup
};
struct UICommand : public command{
    UIelement* ref;
    UICommand(): ref(NULL){}
    UICommand(UIelement& uref){
        ref = &uref;
    }
    virtual void setref(UIelement& uref){
        ref = &uref;
    }
    virtual const UIelement* getref() const {
        return ref;
    }
    virtual void execute() = 0;
    virtual ~UICommand() = default;
};
struct ChangeFontCommand : public command{
    FONT* fontRef;
    FONT newFont;
    ChangeFontCommand() : fontRef(NULL) {}
    ChangeFontCommand(FONT& font) : fontRef(&font) {}
    void setRef(FONT& font){
        fontRef = &font;
    }
    void setNew(const FONT& font){
        newFont = font;
    }
    void execute() override {
        *fontRef = newFont; // Change the font to the new value
    } 
};
struct ChangeColorCommand : public command{
    SDL_Color* bg, *fg;
    SDL_Color nb, nf;
    ChangeColorCommand() : bg(NULL), fg(NULL){}
    ChangeColorCommand(SDL_Color& bref, SDL_Color& fref) : bg(&bref), fg(&fref){}
    void setRef(SDL_Color& bref, SDL_Color& fref){
        bg = &bref;
        fg = &fref;
    }
    void setNew(const SDL_Color& bnew, const SDL_Color& fnew){
        nb = bnew;
        nf = fnew;
    }
    void execute() override {
        *bg = nb;
        *fg = nf;
    }
};
// for simple commands
template <class T>
struct doCommand : public command{
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
struct UIColor : public UICommand{
    ChangeColorCommand cmd;
    UIColor(): UICommand() , cmd(){}
    UIColor(UIelement& uref) : UICommand(uref), cmd(ref->getCol1(), ref->getCol2()){}
    void setNew(const SDL_Color& bnew, const SDL_Color& fnew){
        cmd.nb = bnew;
        cmd.nf = fnew;
    }
    void setref(UIelement& tref) override {
        ref = &tref;
        cmd.setRef(ref->getCol1(), ref->getCol2());
    }
    ~UIColor(){}
};
struct UIFont : public UICommand{
    ChangeFontCommand cmd;
    UIFont(): UICommand(), cmd(){}
    UIFont(UIelement& uref) : UICommand(uref), cmd(ref->getFont()){}
    void setNew(const FONT& font){
        cmd.newFont = font;
    }
    void setref(UIelement& tref){
        ref = &tref;
        cmd.setRef(ref->getFont());
    }
};
