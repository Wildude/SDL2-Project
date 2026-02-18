#pragma once
#include <uielement.hpp>
class UIpanel : public UIelement {
    protected:
    std::vector<UIelement*> elements;
    public:
    void setW(int w);
    void setH(int h);
    void setWH(int w, int h);
    virtual void push(UIelement* element);
    virtual void pop(UIelement* element);
    virtual UIelement* getAt(int index);
    virtual size_t getSize() const;
    virtual void setPos(int x, int y) override;
    virtual FONT* getFont() override;
    virtual void update(InputManager& input) override;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override;
};