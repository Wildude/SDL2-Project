#include <uicontainer.hpp>
class UItab : public UIelement {
    protected:
    //UIlabelpanel tablabels;
    std::vector<UIcontainer*> tabpages;
    int currenttab;
    //std::vector<std::string> tabnames;
    //std::vector<SDL_Rect> tabboxes;
    public:
    UItab();
    void push(UIelement* page);
    void pop(UIelement* page);
    void setCurrent(int index);
    int getCurrent() const;
    UIelement* getCurrentTab();
    virtual void setPos(int x, int y) override;
    virtual FONT* getFont() override;
    virtual void update(InputManager& input) override;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override;
};