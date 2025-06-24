struct ICommand {
    virtual void execute() = 0;
    virtual void setref(void* ref) = 0; // generic ref if needed
    virtual void* getref() const {}
    virtual ~ICommand() {}
};
template <class T>
struct command{
    T* ref;
    command(): ref(NULL){}
    command(T& uref){
        ref = &uref;
    }
    command(T* uref): ref(uref){}
    virtual void setref(T& uref){
        //cout << " setting reference\n";
        ref = &uref;
    }
    virtual const T* getref() const {
        //cout << " getting reference\n";
        return ref;
    }
    virtual void execute() = 0; // Pure virtual function for executing the command
    virtual ~command() = default; // Virtual destructor for proper cleanup
};
template <class T>
struct ChangeFontCommand : public command<T>{
    FONT* fontRef;
    FONT newFont;
    ChangeFontCommand() : command<T>(), fontRef(NULL) {}
    ChangeFontCommand(FONT& font) : command<T>(), fontRef(&font) {}
    ChangeFontCommand(const FONT& nFont): newFont(nFont){}
    void setRef(FONT& font){
        //cout << " setting font references\n";
        fontRef = &font;
    }
    void setNew(const FONT& font){
        //cout << " setting new font\n";
        newFont = font;
    }
    void execute() override {
        if(!fontRef){
            // cout << " no execution\n";
            return;
        }
        //cout << " executing font change\n";
        *fontRef = newFont; // Change the font to the new value
    } 
};
template <class T>
struct ChangeColorCommand : public command<T>{
    SDL_Color* bg, *fg;
    SDL_Color nb, nf;
    ChangeColorCommand() : bg(NULL), fg(NULL), command<T>(){}
    ChangeColorCommand(SDL_Color& bref, SDL_Color& fref) : bg(&bref), fg(&fref){}
    ChangeColorCommand(const SDL_Color& nbg, const SDL_Color& nfg): nb(nbg), nf(nfg){}
    void setRef(SDL_Color& bref, SDL_Color& fref){
        //cout << " setting color references\n";
        bg = &bref;
        fg = &fref;
    }
    void setNew(const SDL_Color& bnew, const SDL_Color& fnew){
        //cout << " setting new colors\n";
        nb = bnew;
        nf = fnew;
    }
    void execute() override {
        if(!bg || !fg){
            // cout << " no execution\n";
            return;
        }
        //cout << " executing color change\n";
        *bg = nb;
        *fg = nf;
    }
};
template <class T>
struct multiCommand : public command<T>{
    vector<command<T>*> commands;
    multiCommand(T* ref = NULL) : command<T>(ref){}
    multiCommand(vector<command<T>*>& cmds): multiCommand(){
        commands = cmds;
    }
    void setref(T& ref) override {
        command<T>::setref(ref);
        int size = commands.size();
        for(int i = 0; i < size; i++){
            commands[i]->setref(ref);
        }
    }
    void push(command<T>& cmd){
        push(&cmd);
    }
    void push(command<T>* cmd){
        //cout << " pushing command\n";
        commands.push_back(cmd);
    }
    command<T>*& getcmd(int index = 0){
        return commands[index];
    }
    void execute(){
        // cout << " executing multicommand\n";
        if(!command<T>::ref){
            // cout << " no reference\n";
            return;
        }
        int size = commands.size();
        if(!size){
            // cout << " no executions\n";
            return;
        }
        for(int i = 0; i < size; i++){
            // cout << " executing cmd " << i << endl;
            commands[i]->execute();
        }
    }
};
// for simple commands
template <class T>
struct doCommand : public command<T>{
    void (*cmd)();
    doCommand(){}
    doCommand(void (*cmd_)()) : cmd(cmd_) {}
    const doCommand& operator=(void (*cmd_)()){
        if(this->cmd != cmd_){
            cmd = cmd_;
        }
        return *this;
    }
    void execute() override {
        cmd();
    }
};
