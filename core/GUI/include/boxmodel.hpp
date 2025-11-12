#pragma once
#include <SDL2/SDL.h>
class SimpleBox {
    protected:
    SDL_Rect content;
    SDL_Color bordercol, bgcol;
    int border, padding, margin;
    public:
    void setContentBox(const SDL_Rect& box);
    SDL_Rect& getContentBox();
    const SDL_Rect& getContentBox() const;
    void setBorderColor(const SDL_Color& col);
    SDL_Color& getBorderColor();
    const SDL_Color& getBorderColor() const;
    void setBackgroundColor(const SDL_Color& col);
    SDL_Color& getBackgroundColor();
    const SDL_Color& getBackgroundColor() const;
    void setBorderWidth(int width);
    int getBorderWidth();
    void setPadding(int pad);
    int getPadding();
    void setMargin(int marg);
    int getMargin();
    SDL_Rect getBox() const;
};
class DynamicBox {
    protected:
    // rect implementation for such logic:
    // x - left position
    // y - top position
    // w - right position
    // h - bottom position
    SDL_Rect marginBox, borderBox, paddingBox, contentBox;
    SDL_Color bordercol, bgcol;
    public:
    void setContentBox(const SDL_Rect& box);
    SDL_Rect& getContentBox();
    const SDL_Rect& getContentBox() const;
    void setBorderColor(const SDL_Color& col);
    SDL_Color& getBorderColor();
    const SDL_Color& getBorderColor() const;
    void setBackgroundColor(const SDL_Color& col);
    SDL_Color& getBackgroundColor();
    const SDL_Color& getBackgroundColor() const;
    void setBorder(int x, int y = -1, int w = -1, int h = -1);
    SDL_Rect& getBorder();
    const SDL_Rect& getBorder() const;
    void setPadding(int x, int y = -1, int w = -1, int h = -1);
    SDL_Rect& getPadding();
    const SDL_Rect& getPadding() const;
    void setMargin(int x, int y = -1, int w = -1, int h = -1);
    SDL_Rect& getMargin();
    const SDL_Rect& getMargin() const;
    SDL_Rect getBox() const;
};