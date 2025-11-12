#include <uibutton.hpp>
class UItextswitch : public UIelement {
    protected:
    std::vector<std::string> options;
    int currentindex;
    FONT* font;
    SDL_Texture* atlas;
    void setAtlas();
    UIbutton inc, dec;
    public:
    UItextswitch(FONT* fnt);
    void push(const std::string& option);
    void pop(const std::string& option);
    void setCurrent(int index);
    int getCurrent() const;
    std::string getCurrentOption() const;
    virtual void setPos(int x, int y) override;
    virtual FONT* getFont() override;
    virtual void update(InputManager& input) override;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override;
    size_t getSize() const;
    ~UItextswitch();
};