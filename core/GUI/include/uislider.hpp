#pragma once
#include <uielement.hpp>
enum UIsliderType {
    UISL_DEFAULT,
    UISL_VERTICAL,
    UISL_ARC,
    UISL_GAUGE
};
class UIslider : public UIelement {
    protected:
    short portion;
    UIsliderType type;
    //bool isdragging;
    public:
    UIslider(short portion = 0);
    void setType(UIsliderType t);
    UIsliderType getType() const;
    void setValue(int val);
    int getValue() const;
    virtual void setPos(int x, int y) override;
    virtual FONT* getFont() override;
    virtual void update(InputManager& input) override;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override;
    ~UIslider();
};