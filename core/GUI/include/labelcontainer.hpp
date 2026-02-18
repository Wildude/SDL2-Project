#pragma once
#include <uilabel.hpp>
// 1.0 implementation
// each label has a texture and FONT pointer
// inefficient but functional
enum UIlabelContainerType {
    UILC_FIXED,
    UILC_VERTICAL,
    UILC_HORIZONTAL
};
class UIlabelcontainer : public UIelement {
    protected:
    std::vector<UIlabel*> labels;
    UIlabelContainerType contype;
    public:
    UIlabelcontainer(UIlabelContainerType type = UILC_FIXED);
    void setW(int w);
    void setH(int h);
    void setWH(int w, int h);
    void setType(UIlabelContainerType type);
    UIlabelContainerType getType() const;
    void push(UIlabel* label);
    void pop(UIlabel* label);
    virtual void setPos(int x, int y) override;
    virtual FONT* getFont() override;
    virtual void update(InputManager& input) override;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override;
    UIlabel* getAt(int index);
    size_t getSize() const;
};
class UIClabel : public UIelement {
    protected:
    std::vector<std::string> labels;
    UIlabelContainerType contype;
    FONT* font;
    SDL_Texture* atlas;
    // std::vector<SDL_Rect> labelboxes;
    void setAtlas();
    public:
    void setType(UIlabelContainerType type);
    UIlabelContainerType getType() const;
    void push(const std::string& label);
    void pop(const std::string& label);
    virtual void setPos(int x, int y) override;
    virtual FONT* getFont() override;
    virtual void update(InputManager& input) override;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override;
    std::string getAt(int index);
    size_t getSize() const;
};