#pragma once
#include "../../SDL/include/font.hpp"
#include "../../SDL/include/textInputHandler.hpp"
#include <iostream>
#include <vector>
template <class T>
struct command{
    T* ref;
    command(): ref(NULL){}
    command(T& uref): ref(&uref){}
    command(T* uref): ref(uref){}
    virtual void setref(T& uref){
        //std::cout << " setting reference\n";
        ref = &uref;
    }
    virtual void setref(T* uref = NULL){
        ref = uref;
    }
    virtual const T* getref() const {
        //std::cout << " getting reference\n";
        return ref;
    }
    virtual T* getref(){
        //std::cout << " getting reference\n";
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
    ChangeFontCommand(const FONT& nFont): newFont(nFont), fontRef(NULL){}
    void setRef(FONT& font){
        //std::cout << " setting font references\n";
        fontRef = &font;
    }
    void setNew(const FONT& font){
        //std::cout << " setting new font\n";
        newFont = font;
    }
    void execute() override {
        if(!fontRef){
            // std::cout << " no font execution\n";
            return;
        }
        // std::cout << " executing font change\n";
        *fontRef = newFont; // Change the font to the new value
    } 
    const T* getref() const override {
        //std::cout << " Font command ref get called\n";
        return command<T>::getref();
    }
};
template <class T>
struct ChangeColorCommand : public command<T>{
    SDL_Color* bg, *fg;
    SDL_Color nb, nf;
    ChangeColorCommand() : bg(NULL), fg(NULL), command<T>(){}
    ChangeColorCommand(SDL_Color& bref, SDL_Color& fref) : bg(&bref), fg(&fref){}
    ChangeColorCommand(const SDL_Color& nbg, const SDL_Color& nfg): nb(nbg), nf(nfg), bg(NULL), fg(NULL){}
    void setRef(SDL_Color& bref, SDL_Color& fref){
        //std::cout << " setting color references\n";
        bg = &bref;
        fg = &fref;
    }
    void setNew(const SDL_Color& bnew, const SDL_Color& fnew){
        //std::cout << " setting new colors\n";
        nb = bnew;
        nf = fnew;
    }
    void execute() override {
        if(!bg || !fg){
            // std::cout << " no color execution\n";
            return;
        }
        // std::cout << " executing color change\n";
        *bg = nb;
        *fg = nf;
    }
};
template <class T>
struct ChangeStringCommand : public command<T>{
    std::string* stringref;
    std::string newstring;
    ChangeStringCommand(): command<T>(), stringref(NULL), newstring("") {}
    ChangeStringCommand(T& ref, std::string* strref = NULL): command<T>(ref), stringref(strref), newstring("") {}
    ChangeStringCommand(T* ref, std::string* strref = NULL): command<T>(ref), stringref(strref), newstring("") {}
    ChangeStringCommand(const char* str): command<T>(), stringref(NULL), newstring(str){}
    inline void setStrRef(std::string* strref){
        stringref = strref;
    }
    inline void setStrRef(std::string& strref){
        stringref = &strref;
    }
    inline void setNewString(const std::string& newstr){
        newstring = newstr;
    }
    inline void setNewString(const char* newstr = ""){
        newstring = newstr;
    }
    inline std::string* getStrRef(){
        return stringref;
    }
    inline std::string& getNewStrRef(){
        return newstring;
    }
    void execute(){
        // std::cout << " executing string change command\n";
        if(!command<T>::ref){
           // std::cout << " no ref\n";
            return;
        }
        if(!stringref){
            // std::cout << " no string ref\n";
            return;
        }
        // std::cout << "before: " << *stringref << ", after: " << newstring << endl;
        *stringref = newstring;
    }
};
template <class T>
struct InputStringCommand : public command<T> {
    ChangeStringCommand<T> changestr;
    SDL_Scancode quitCase;
    TextInputHandler* inputHandler;
    InputStringCommand(TextInputHandler* input = NULL, T* ref = NULL, 
        std::string* textN = NULL, SDL_Scancode quiter = SDL_SCANCODE_ESCAPE) : 
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
    inline TextInputHandler* getInputer() const{
        return inputHandler;
    }
    inline bool iswriting() {
        return (inputHandler && inputHandler->getTextState());
    }
    inline bool iswritingON(){
        return inputHandler && inputHandler->getInputref() == &changestr.getNewStrRef();
    }
    void checktext(){
        if(!iswriting()){
            // std::cout << " quitcase\n";
            setwriting(false);
        }
        else if(iswritingON()){
            changestr.execute();
        }
    }
    inline void stopwriting(){
        inputHandler->setTextUse(false);
        inputHandler->setInput(NULL);
    }
    void setwriting(bool write){
        // std::cout << " setting writing to false/true\n";
        if(!write){
            // std::cout << " quit textmode\n";
            if(iswritingON()){
                stopwriting();
            }
        }
        else if(inputHandler){
            inputHandler->setTextUse(true);
        }
    }
    inline std::string* getStrRef() {
        return changestr.getStrRef();
    }
    inline void setStrRef(std::string* textto = NULL){
        changestr.setStrRef(textto);
    }
    inline void setStrRef(std::string& textto){
        changestr.setStrRef(textto);
    }
    inline void setInput(){
        if(!inputHandler)return;
        inputHandler->setInput(changestr.getNewStrRef());
    }
    std::string& getNewStrRef(){
        return changestr.getNewStrRef();
    }
    void execute() override {
        // std::cout << " exec inbox\n";
        if(!inputHandler){
            //std::cout << " cmd error no inputer\n";
            return;
        }
        if(!command<T>::ref){
            //std::cout << " no ref\n";
            return;
        }
        //else std::cout << " there's reference\n";
        //std::cout << " cmd writing\n";
        if(!iswritingON()){
            setInput();
            inputHandler->clearText();
        }
        setwriting(true);
        //else std::cout << " just writing\n";
        changestr.execute();
    }
};
template <class T>
struct multiCommand : public command<T>{
    std::vector<command<T>*> commands;
    multiCommand(T* ref = NULL) : command<T>(ref){}
    multiCommand(std::vector<command<T>*>& cmds): multiCommand(){
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
        //std::cout << " pushing command\n";
        commands.push_back(cmd);
    }
    command<T>*& getcmd(int index = 0){
        return commands[index];
    }
    void execute() override {
        // std::cout << " executing multicommand\n";
        if(!command<T>::ref){
             // std::cout << " no reference\n";
            return;
        }
        int size = commands.size();
        if(!size){
             // std::cout << " no executions\n";
            return;
        }
        for(int i = 0; i < size; i++){
            // std::cout << " executing cmd " << i << endl;
            commands[i]->setref(*command<T>::ref);
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
