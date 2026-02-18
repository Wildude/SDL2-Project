#pragma once
#include <uielement.hpp>
struct UIcommand{
    virtual UIcommand* clone() const = 0;
    virtual void execute(UIelement* ref) = 0;
};
struct UIMultiCommand: UIcommand{
    std::vector<UIcommand*> commands;
    UIMultiCommand(std::vector<UIcommand*>& cmds);
    void push(UIcommand& cmd);
    void push(UIcommand* cmd);
    UIcommand*& getcmd(int index = 0);
    UIMultiCommand* clone() const override;
    ~UIMultiCommand();
    void execute(UIelement* ref) override ;
};
struct UIColor : public UIcommand{
    SDL_Color newbg, newfg;
    UIColor();
    UIColor(const SDL_Color& nfg, const SDL_Color& nbg);
    void setNew(const SDL_Color& bnew, const SDL_Color& fnew);
    UIColor* clone() const override;
    void execute(UIelement* ref) override;
    ~UIColor();
};
struct UIFont : public UIcommand{
    FONT newfont;
    UIFont();
    UIFont(const FONT& font);
    void setNew(const FONT& font);
    UIFont* clone() const override;
    void execute(UIelement* ref);
};