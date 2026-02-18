#pragma once
#include <uielement.hpp>
enum UIContainerType {
    UIC_FIXED,
    UIC_VERTICAL,
    UIC_HORIZONTAL
};
class UIcontainer : public UIelement {
    protected:
    std::vector<UIelement*> elements;
    UIContainerType contype;
    public:
    UIcontainer(): contype(UIC_VERTICAL) {
        box.content.x = 0;
        box.content.y = 0;
    };
    void setType(UIContainerType type);
    UIContainerType getType() const;
    void setW(int w);
    void setH(int h);
    void setWH(int w, int h);
    virtual void push(UIelement* element);
    virtual void pop(UIelement* element);
    inline void pop() {
        elements.pop_back();
    }
    virtual UIelement* getAt(int index);
    virtual size_t getSize() const;
    virtual void setPos(int x, int y) override;
    virtual FONT* getFont() override;
    virtual void update(InputManager& input) override;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override;
};