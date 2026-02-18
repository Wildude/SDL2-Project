#pragma once
#include <boxmodel.hpp>
#include <inputManager.hpp>
#include <font.hpp>
#include <SDL2_gfx/SDL2_gfxPrimitives.h>
inline std::ostream& operator<<(std::ostream& os, const SDL_Color& col){
    os << "(" << (int)col.r << ", " << (int)col.g << ", " << (int)col.b << ", " << (int)col.a << ")";
    return os;
}
class UIelement // : public GameObject
{
    protected:
    bool ishover, isfocus, isclick, isrevert, statechanged, iscurrent;
    SDL_Color fg, bg;
    SimpleBox box;
    //
    public:
    UIelement(): 
    ishover(false), isfocus(false), isclick(false), 
    isrevert(false), statechanged(false), iscurrent(false),
    fg({0, 0, 0, 0}), bg({255, 255, 255, 255}), box() {}
    bool isclicked(InputManager& input);
    bool ishovered(InputManager& input);
    bool isfocused(InputManager& input);
    bool isreverted(InputManager& input);
    // discrete testers
    bool getclick() const;
    bool gethover() const;
    bool getfocus() const;
    bool getrevert() const;
    bool getcurrent() const;
    bool getstate() const;
    //
    bool& getclick();
    bool& gethover();
    bool& getfocus();
    bool& getrevert();
    bool& getcurrent();
    bool& getstate();
    //
    virtual void setPos(int x, int y) = 0;
    virtual void setfg(const SDL_Color& col);
    virtual void setbg(const SDL_Color& col);
    //
    virtual SDL_Color* getfg();
    virtual SDL_Color* getbg();
    // returns a pointer to the font (pure virtual, must be implemented by derived classes)
    virtual FONT* getFont() = 0;
    virtual SimpleBox* getBox();
    virtual void update(InputManager& input);
    virtual void render(SDL_Renderer* rend, int drawtype = 2);
};