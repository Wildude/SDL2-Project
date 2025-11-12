#include <boxmodel.hpp>
#include <inputManager.hpp>
#include <font.hpp>
class UIelement // : public GameObject
{
    protected:
    bool ishover, isfocus, isclick, isrevert, statechanged;
    SDL_Color fg, bg;
    SimpleBox box;
    //
    public:
    virtual void setPos(int x, int y) = 0;
    virtual void setfg(const SDL_Color& col);
    virtual void setbg(const SDL_Color& col);
    virtual SDL_Color* getfg();
    virtual SDL_Color* getbg();
    virtual FONT* getFont() = 0;
    virtual SimpleBox* getBox();
    virtual void update(InputManager& input) = 0;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) = 0;
};