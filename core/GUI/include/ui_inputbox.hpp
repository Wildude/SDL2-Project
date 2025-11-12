#include <uilabel.hpp>
#include <textInputHandler.hpp>
class UIinputbox : public UIelement {
    protected:
    std::string text;
    FONT* font;
    SDL_Texture* board;
    TextInputHandler inputhandler;
    public:
    UIinputbox(const std::string& txt, FONT* fnt);
    void setText(const std::string& txt);
    std::string getText() const;
    virtual void setPos(int x, int y) override;
    virtual FONT* getFont() override;
    virtual void update(InputManager& input) override;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override;
    void setFont(FONT* fnt);
    ~UIinputbox();
};