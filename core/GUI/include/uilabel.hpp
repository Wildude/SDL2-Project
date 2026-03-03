#pragma once
#include <uielement.hpp>
enum UILabelQuality {
    UILABEL_QUALITY_SOLID,
    UILABEL_QUALITY_BLENDED,
    UILABEL_QUALITY_SHADED,
    UILABEL_QUALITY_LCD
};
class UIlabel : public UIelement {
    protected:
    std::string text;
    FONT* font;
    SDL_Texture* board;
    UILabelQuality qual;
    public:
    UIlabel(const std::string& txt, FONT* fnt);
    void setQual(UILabelQuality quality);
    UILabelQuality getQual();
    void setText(const std::string& txt);
    std::string getText() const;
    virtual void setPos(int x, int y) override;
    virtual FONT* getFont() override;
    virtual void update(InputManager& input) override;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override;
    void setFont(FONT* fnt);
    ~UIlabel();
};