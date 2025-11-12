#include <uibutton.hpp>
enum UICheckboxType {
    UICB_DEFAULT,
    UICB_TICK,
    UICB_FLIP
};
class UIcheckbox : public UIelement {
    protected:
    UICheckboxType checkboxType;
    bool checked;
    public:
    UIcheckbox(UICheckboxType type = UICB_DEFAULT);
    void setChecked(bool state);
    bool isChecked() const;
    virtual void setPos(int x, int y) override;
    virtual FONT* getFont() override;
    virtual void update(InputManager& input) override;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override;
    ~UIcheckbox();
};