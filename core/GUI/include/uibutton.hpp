#include <uielement.hpp>
enum UIButtonType {
    UIBT_DEFAULT,
    UIBT_INCREMENT,
    UIBT_DECREMENT
};
class UIbutton : public UIelement {
    protected:
    UIButtonType buttontype;
    public:
    UIbutton(UIButtonType type = UIBT_DEFAULT);
    virtual void setPos(int x, int y) override;
    virtual FONT* getFont() override;
    virtual void update(InputManager& input) override;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override;
    ~UIbutton();
};