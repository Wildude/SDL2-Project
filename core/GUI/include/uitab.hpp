#pragma once
#include <uicontainer.hpp>
#include <labelcontainer.hpp>
class UItab : public UIelement {
    protected:
    UIlabelcontainer tablabels;
    std::vector<UIcontainer*> tabpages;
    int currenttab;
    FONT* font;
    //std::vector<std::string> tabnames;
    //std::vector<SDL_Rect> tabboxes;
    public:
    UItab();
    void push(UIcontainer* page);
    void pop(UIcontainer* page);
    void setCurrent(int index);
    int getCurrent() const;
    UIelement* getCurrentTab();
    virtual void setPos(int x, int y) override;
    virtual FONT* getFont() override;
    virtual void update(InputManager& input) override;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override;
};