#include <SDL2/SDL.h>
class SimpleBox {
    protected:
    SDL_Rect content;
    SDL_Color bordercol, bgcol;
    int border, padding, margin;
    public:
    void setContentBox(const SDL_Rect& box);
    SDL_Rect& getContentBox();
    void setBorderColor(const SDL_Color& col);
    SDL_Color& getBorderColor();
    void setBackgroundColor(const SDL_Color& col);
    SDL_Color& getBackgroundColor();
    void setBorderWidth(int width);
    int getBorderWidth();
    void setPadding(int pad);
    int getPadding();
    void setMargin(int marg);
    int getMargin();
    SDL_Rect getBox();
};
class DynamicBox {
    protected:
    SDL_Rect marginBox, borderBox, paddingBox, contentBox;
    SDL_Color bordercol, bgcol;
    public:
    void setContentBox(const SDL_Rect& box);
    SDL_Rect& getContentBox();
    void setBorderColor(const SDL_Color& col);
    SDL_Color& getBorderColor();
    void setBackgroundColor(const SDL_Color& col);
    SDL_Color& getBackgroundColor();
    void setBorder(int x, int y = -1, int w = -1, int h = -1);
    SDL_Rect getBorder();
    void setPadding(int x, int y = -1, int w = -1, int h = -1);
    SDL_Rect getPadding();
    void setMargin(int x, int y = -1, int w = -1, int h = -1);
    SDL_Rect getMargin();
    SDL_Rect getBox();
};