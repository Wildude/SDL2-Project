#pragma once
#include <texture2D.hpp>
#include <font.hpp>
#include <textInputHandler.hpp>
#include <command.hpp>
#include <gameobject.hpp>
//#include <fstream>
#include <vector>
typedef command<GameObject> GameCommand;
class UIelement : public GameObject
{
    public:
    typedef command<UIelement> UICommand;
    protected:
    bool ishover, isfocus, isclick, isrevert;
    struct UIcmdset{
        UICommand* focus;
        UICommand* click;
        UICommand* revert;
        UIcmdset(UICommand*f = NULL, UICommand*c = NULL, UICommand*r = NULL):
        focus(f), click(c), revert(r){}
    } UIcmds;
    public:
    // abstract imps
    virtual void setPos(int, int) = 0;
    virtual void setCol1(const SDL_Color&) = 0;
    virtual void setCol2(const SDL_Color&) = 0;
    virtual void setFont(const FONT&) = 0;
    virtual SDL_Rect* getBox() = 0;
    virtual FONT* getFont() = 0;
    virtual SDL_Color* getCol1() = 0;
    virtual SDL_Color* getCol2() = 0;
    virtual void render(SDL_Renderer*, int) = 0; // Pure virtual function for rendering the UI element
    // repeated imps
    virtual bool isFocused(InputManager& input);
    virtual bool isClicked(InputManager& input);    
    virtual bool isCurrent(InputManager& input);
    virtual void update(InputManager& input);
    virtual void onFocus(UICommand* focus = NULL);
    virtual void onClick(UICommand* click = NULL);
    virtual void onRevert(UICommand* revert = NULL);
    void clearCMD();
    virtual bool isHovered(const InputManager& input);
    // meaningless imps
    virtual void settext(const std::string& text);
    virtual std::string& getText();
    // important imps
    bool gethover() const ;
    bool getfocus() const ;
    bool getclick() const ;
    bool getrevert() const ;
    UICommand* getFocusCmd() const ;
    UICommand* getClickCmd() const ;
    UICommand* getRevertCmd() const;
    // constructors and such
    UIelement(const UIcmdset& cmd = UIcmdset{NULL, NULL, NULL}, 
        bool focus = false, bool hover = false, bool click = false, bool revert = true);
    UIelement(const UIelement& ui);
    UIelement& operator=(const UIelement& ui);
    /* inline */ void checkfile();
    ~UIelement();
    
};
typedef command<UIelement> UICommand;
struct UIMultiCommand: UICommand{
    std::vector<UICommand*> commands;
    UIMultiCommand(UIelement* ref = NULL);
    UIMultiCommand(std::vector<UICommand*>& cmds);
    void setref(UIelement& ref) override ;
    void push(UICommand& cmd);
    void push(UICommand* cmd);
    UICommand*& getcmd(int index = 0);
    void execute() override ;
};
struct UIColor : public UICommand{
    ChangeColorCommand<int> cmd;
    UIColor();
    UIColor(UIelement& uref);
    UIColor(const SDL_Color& nbg, const SDL_Color& nfg);
    void setNew(const SDL_Color& bnew, const SDL_Color& fnew);
    void setref(UIelement& tref) override;
    void execute() override;
    ~UIColor();
};
struct UIFont : public UICommand{
    ChangeFontCommand<int> cmd;
    UIFont();
    UIFont(UIelement& uref);
    UIFont(const FONT& font);
    void setNew(const FONT& font);
    void setref(UIelement& tref);
    const UIelement* getref() const override ;
    void execute();
};
enum orient{VERT, HORI};
enum Alignment{LEFT, CENTER, RIGHT};
class UIContainer : public UIelement{
    protected:
    std::vector<UIelement*> UIlist;
    SDL_Rect box;
    SDL_Color fg, bg;
    public:
    UIContainer();
    int getsize();
    void setBoxW(int width);
    void setBoxH(int height);
    std::vector<UIelement*>& getList();
    const UIContainer& operator=(const std::vector<UIelement*>& UIC);
    const UIContainer& operator=(const UIContainer& UIC);
    void update(InputManager& input) override;
    UIContainer(std::vector<UIelement*>& UIs);
    void push(UIelement& ui);
    void push(UIelement* ui);
    void render(SDL_Renderer* renderer, int drawtype = 2) override ;
    SDL_Color* getCol1();
    SDL_Color* getCol2();
    FONT* getFont();
    SDL_Rect* getBox();
    void apply();
    void applyFont();
    void applyCol1();
    void applyCol2();
    void setFont(const FONT& font) override ;
    void setCol1(const SDL_Color& col) override ;
    void setCol2(const SDL_Color& col) override ;
    void onClick(UICommand* cmd = NULL) override ;
    void onFocus(UICommand* cmd = NULL) override ;
    void onRevert(UICommand* cmd = NULL) override ;
    //
    virtual void setPos(int x, int y) override ;
    virtual void setbox();
};
class UIPanel : public UIContainer{
    public:
    void setPos(int x, int y) override ;
    void setbox() override ;
};
/*
🔹 1. Text-Based Components
*/
struct ChangeStringUICmd : public UICommand{
    ChangeStringCommand<UIelement> cmd;
    ChangeStringUICmd(UIelement* ref = NULL, std::string* textp = NULL);
    void setref(UIelement& ref) override ;
    void setref(UIelement* ref) override ;
    void setTextP(std::string* textp = NULL);
    void setNewStr(const std::string& newstr);
    void setNewStr(const char* newstr = "");
    virtual void execute();
};
struct InputStringUIcmd : public UICommand {
    InputStringCommand<UIelement> cmd;
    InputStringUIcmd(TextInputHandler* input = NULL, UIelement* ref = NULL, std::string* textN = NULL, 
        SDL_Scancode quitCase = SDL_SCANCODE_ESCAPE);
    void setref(UIelement& ref);
    void setref(UIelement* ref = NULL);
    void setInputer(TextInputHandler& inputH);
    void setInputer(TextInputHandler* inputH = NULL);
    /* inline */ TextInputHandler* getInputer() const;
    /* inline */ bool iswriting();
    /* inline */ bool iswritingON();
    /* inline */ void stopwriting();
    void checktext();
    /* inline */ void setwriting(bool write);
    /* inline */ void setStrRef(std::string* textto = NULL);
    /* inline */ void setStrRef(std::string& textto);
    void execute() override;
};
class Label : public UIelement {
    public:
    const Label& operator=(const Label& label);
    Label(const UIcmdset& cmd = UIcmdset{NULL, NULL, NULL}, const SDL_Color& fcolor = SDL_Color({0, 0, 0, 255})
    , const SDL_Color& bcolor = SDL_Color({255, 255, 255, 255}), const std::string& ttext = ""
    , const SDL_Rect& rbox = SDL_Rect({0, 0, 0, 0}), const FONT& ffont = FONT(), SDL_Texture* tex = NULL);
    Label(const char* str);
    Label(int x, int y);
    Label(const FONT& font);
    /* inline */ void setPos(int x, int y);
    void setFont(const FONT& newfont);
    /* inline */ void setCol1(const SDL_Color& col);
    /* inline */ void setCol2(const SDL_Color& col);
    void setquery();
    /* inline */ void delTex();
    void settext(const char* str = NULL);
    void settext(const std::string& str) override ;
    virtual void render(SDL_Renderer* renderer, int drawtype = 2) override ;
    virtual /* inline */ std::string& getText();
    virtual /* inline */ const char* gettext();
    virtual /* inline */ std::string& gettextRef();
    virtual /* inline */ FONT* getFont();
    virtual /* inline */ SDL_Color* getCol1();
    virtual /* inline */ SDL_Color* getCol2();
    virtual /* inline */ SDL_Rect* getBox();
    protected:
    SDL_Rect box; // box model
    std::string text;
    FONT font;
    SDL_Color fg, bg;
    SDL_Texture* texture;
};
class LabelPanel : public UIelement {
    protected:
    std::vector<Label> labelList;
    SDL_Rect box;
    SDL_Color fg, bg;
    public:
    LabelPanel();
    int getsize();
    std::vector<Label>& getList();
    const LabelPanel& operator=(const std::vector<Label>& UIC);
    const LabelPanel& operator=(const LabelPanel& UIC);
    void update(InputManager& input) override ;
    LabelPanel(std::vector<Label>& UIs);
    void push(const Label& ui);
    void push(Label* ui);
    void render(SDL_Renderer* renderer, int drawtype = 2) override ;
    SDL_Color* getCol1();
    SDL_Color* getCol2();
    FONT* getFont();
    SDL_Rect* getBox();
    void apply();
    void applyFont();
    void applyCol1();
    void applyCol2();
    void setFont(const FONT& font) override ;
    void setCol1(const SDL_Color& col) override ;
    void setCol2(const SDL_Color& col) override ;
    void onClick(UICommand* cmd = NULL) override ;
    void onFocus(UICommand* cmd = NULL) override ;
    void onRevert(UICommand* cmd = NULL) override ;
    //
    virtual void setPos(int x, int y) override ;
    virtual void setbox();
};
class UITab : public UIelement{
    protected:
    void setbox();
    int calcWidthSum();
    void setLabels();
    void setallwidths();
    int getLargestLabelHeight();
    int getLargestUICwidth();
    int getLargestUICheight();
    LabelPanel labelList;
    std::vector<UIContainer*> tabs;
    std::vector<std::string> tabnames;
    std::vector<SDL_Rect> boxes;
    SDL_Rect Box;
    short currenttab;
    SDL_Color fg, bg;
    FONT font;
    public:
    UITab();
    //
    void update(InputManager& input) override ;
    void render(SDL_Renderer* rend, int drawtype = 2) override ;
    void setPos(int x, int y) override ;
    void setCol1(const SDL_Color& col) override ;
    void setCol2(const SDL_Color& col) override ;
    void setFont(const FONT& font_) override ;
    SDL_Rect* getBox() override ;
    FONT* getFont() override ;
    SDL_Color* getCol1() override ;
    SDL_Color* getCol2() override ;
    void onFocus(UICommand* cmd = NULL) override ;
    void onClick(UICommand* cmd = NULL) override ;
    void onRevert(UICommand* cmd = NULL) override ;
    //
    /* inline */ void push(UIContainer& tab, const char* name = NULL);
    /* inline */ void push(UIContainer* tab, const char* name = NULL);
    /* inline */ void settabname(int i, const char* name = NULL);
    /* inline */ void settabname(int i, const std::string& name);
    /* inline */ void setCurrentTab(int i);
    /* inline */ int getCurrentTab() const ;
    /* inline */ UIContainer* getCurrentTabContainer() const ;  
};
class InputBox : public Label{
    UIMultiCommand& multref;
    SDL_Point dims;
    bool iswrite;
public:
    InputBox();
    InputBox(const char* str);
    InputBox(int x, int y);
    InputBox(const FONT& font);
    /* inline */ void setdims(int x, int y);
    /* inline */ void onClick(UICommand* cmd = NULL) override ;
    void update(InputManager& input) override ;
    void render(SDL_Renderer* renderer, int drawtype = 2) override ;
    const SDL_Point& getDims() const ;
    bool isWritingON() const;
    ~InputBox();
};
class LabelArea : public Label{
    protected:
    void setBox();
    std::vector<std::string> lines;
    int linespacing;
    SDL_Rect Box;
    SDL_Color fg, bg;
    public:
    //
    void setPos(int x, int y) override ;
    void setCol1(const SDL_Color& col) override ;
    void setCol2(const SDL_Color& col) override ;
    void setFont(const FONT& font) override ;
    SDL_Rect* getBox();
    void render(SDL_Renderer* rend, int drawtype = 2) override ;
    //
    //
    LabelArea();
    void push(const std::string& str);
    void push(const char* str = "");
};
class InputArea : public LabelArea{
    // 
};
class PasswordBox : public InputBox {

};
/*
🔹 2. Buttons & Interaction
*/
class Button : public UIelement {
    protected:
    SDL_Rect Box;
    SDL_Color fg, bg;
    public:
    // overriden functions (abstract)
    /* inline */ virtual void setPos(int x, int y) override ;
    /* inline */ virtual void setCol1(const SDL_Color& col) override ;
    /* inline */ virtual void setCol2(const SDL_Color& col) override ;
    /* inline */ virtual void setFont(const FONT& font) override ;
    /* inline */ virtual SDL_Rect* getBox() override ;
    /* inline */ virtual FONT* getFont() ;
    /* inline */ virtual SDL_Color* getCol1() override ;
    /* inline */ virtual SDL_Color* getCol2() override ;
    //void update(InputManager& input) override ;
    virtual void render(SDL_Renderer*, int) = 0;
    // overriden functions (non-abstract)

    // Button implementation
    Button();
    void setBoxDim(int w, int h);
};
class ToggleButton : public Button {
    // Toggle button implementation
};
enum checkType{
    CLASSIC, 
    FLIPBOX,
    TICKBOX
};
class CheckBox : public Button{ // maybe should inherit from Button later.
    bool clickstate;
    checkType type;
    public:
    // abstract imps
    // virtual void setPos(int x , int y) override ;
    // virtual void setCol1(const SDL_Color& col);
    // virtual void setCol2(const SDL_Color& col);
    // virtual void setFont(const FONT& font);
    // virtual SDL_Rect* getBox();
    // virtual FONT* getFont();
    // virtual SDL_Color* getCol1();
    // virtual SDL_Color* getCol2();
    virtual void update(InputManager& input) override ;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override ;
    //
    CheckBox(checkType typei = CLASSIC);
    const CheckBox& operator=(const CheckBox& sbox);
    //
    void settype(checkType typei = CLASSIC);
    
    /* inline */ bool getState() const ;
    /* inline */ void setState();
    /* inline */ void clearState();
    /* inline */ void toogleState();
};
class RadioButton : public UIelement{
    std::vector<CheckBox> checkboxes;
    int current;
    SDL_Rect Box;
    SDL_Color fg, bg;
    public:
    // abstract imps
    virtual void setPos(int x , int y) override ;
    virtual void setCol1(const SDL_Color& col);
    virtual void setCol2(const SDL_Color& col);
    virtual void setFont(const FONT& font);
    virtual SDL_Rect* getBox();
    virtual FONT* getFont();
    virtual SDL_Color* getCol1();
    virtual SDL_Color* getCol2();
    virtual void update(InputManager& input) override ;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override ;
    //
    void onFocus(UICommand* cmd = NULL) override ;
    void onClick(UICommand* cmd = NULL) override ;
    void onRevert(UICommand* cmd = NULL) override ;
    RadioButton();
    /* inline */ void push(const CheckBox& cbox);
    /* inline */ void setbox() ;
    /* inline */ int getCurrent() const ;
    /* inline */ std::vector<CheckBox>& getList();
};
enum Orientation{INC_HORI, INC_VERT, DEC_HORI, DEC_VERT};
class IncDecButton : public Button {
    protected:
    Orientation type;
    // abstract imps
    public:
    virtual void render(SDL_Renderer* rend, int drawtype = 2);
    // imps
    IncDecButton(Orientation typei = INC_HORI);
    /* inline */ void setType(Orientation typei);
    /* inline */ Orientation getType() const ;
};
class IncDecCheckbox : public IncDecButton{
    protected:
    bool clickstate;
    orient type;
    public:
    //
    void update(InputManager& input) override ;
    void render(SDL_Renderer* rend, int drawtype = 2) override ;
    //
    IncDecCheckbox(orient typei = HORI);
    /* inline */ void setType(orient typei);
    /* inline */ bool getState() const ;
    /* inline */ void setState();
    /* inline */ void clearState();
    /* inline */ void toggleState();
};
class TextSwitch: public UIelement{
    protected:
    std::vector<std::string> texts;
    int current;
    Label theText;
    SDL_Color fg, bg;
    SDL_Rect Box;
    IncDecButton inc, dec;
    public:
    //
    void setPos(int x , int y) override ;
    void setCol1(const SDL_Color& col) override ;
    void setCol2(const SDL_Color& col) override ;
    void setFont(const FONT& font) override ;
    SDL_Rect* getBox() override ;
    FONT* getFont() override ;
    SDL_Color* getCol1() override ;
    SDL_Color* getCol2() override ;
    void update(InputManager& input) override ;
    void render(SDL_Renderer* rend, int drawtype = 2) override ;
    //
    void onFocus(UICommand* cmd = NULL);
    void onClick(UICommand* cmd = NULL);
    void onRevert(UICommand* cmd = NULL);
    //
    std::string& getText() override ;
    //
    TextSwitch();
    void setBox();
    void push(const std::string& txt);
    void push(const char* txt = "");
};
/*
🔹 3. Selection & Lists
*/
class Dropdown : public UIelement {
    protected:
    void setBox();
    int largestheight();
    int largestwidth();
    std::vector<Label> options;
    SDL_Rect Box;
    SDL_Color fg, bg;
    IncDecCheckbox updown;
    public:
    // abstract imps
    virtual void setPos(int x , int y) override ;
    virtual void setCol1(const SDL_Color& col);
    virtual void setCol2(const SDL_Color& col);
    virtual void setFont(const FONT& font);
    virtual SDL_Rect* getBox();
    virtual FONT* getFont();
    virtual SDL_Color* getCol1();
    virtual SDL_Color* getCol2();
    void update(InputManager& input) override ;
    void render(SDL_Renderer* rend, int drawtype = 2) override ;
    //
    // Dropdown implementation
    Dropdown();
    void push(const Label& opt);
    void push(const std::string& str);
    void push(const char* str = "");
};
class ListBox : public Dropdown{

};
class MultiSelect : public ListBox{

};
class AutoCompleteBox : public Dropdown{

};

/*
🔹 4. Containers & Layouts
*/
class Panel : public UIelement {
    // Panel implementation
};
class ScrollView : public Panel {
    // Scroll view implementation
};
class Tabs : public UIelement {
    // Tabs implementation
};
class GridLayout : public UIelement {
    // Grid layout implementation
};
enum cond{INC, DEC, EXT, NTN};
struct ChangeLevelUIcmd : UICommand{
    SDL_Scancode quitCase, increaseCase, decreaseCase;
    InputManager* inputHandler;
    bool *increase = NULL, *decrease = NULL;
    ChangeLevelUIcmd(InputManager* input = NULL, UIelement* ref = NULL, SDL_Scancode quiter = SDL_SCANCODE_ESCAPE);
    void setRef(InputManager* input = NULL);
    /* inline */ void quitit();
    cond checkcond();
    void setIncrease(SDL_Scancode inced = SDL_SCANCODE_UP);
    void setDecrease(SDL_Scancode deced = SDL_SCANCODE_DOWN);
    void setQuit(SDL_Scancode quitC);
    void execute();
};
/*
🔹 5. Sliders & Selectors
*/
class Slider : public UIelement{
    private:
    UIMultiCommand& multref;
    SDL_Rect box;
    SDL_Color fg, bg;
    short portion;
    orient type;
    public:
    Slider(bool focus = false, bool hover = false, bool click = false, bool revert = true);
    Slider(orient slideType);
    Slider(const SDL_Rect& slidebox);
    void setType(orient slideType);
    void setportion(short port);
    void checkbox();
    void setPos(int x, int y) override ;
    void setBox(int w, int h);
    SDL_Color* getCol1() override ;
    SDL_Color* getCol2() override ;
    FONT* getFont() override ;
    SDL_Rect* getBox() override ;
    void update(InputManager& input) override ;
    /* inline */ void checkportion();
    /* inline */ short getportion() const ;
    /* inline */ void setascond(cond curr);
    void render(SDL_Renderer* rend, int drawt = 2) override;
    void setCol1(const SDL_Color& col) override ;
    void setCol2(const SDL_Color& col) override ;
    void setFont(const FONT& font) override ;
    void onClick(UICommand* cmd = NULL) override ;
    ~Slider();
};
class SpinBox : public UIelement{
    protected:
    void setasType();
    void setBox();
    short num;
    InputBox thenum;
    IncDecButton inc, dec;
    orient type;
    SDL_Rect Box;
    SDL_Color fg, bg;
    public:
    //
    void setPos(int x, int y);
    void setCol1(const SDL_Color& col) override ;
    void setCol2(const SDL_Color& col) override ;
    void setFont(const FONT& font) override ;
    FONT* getFont() override ;
    SDL_Rect* getBox();
    SDL_Color* getCol1() override ;
    SDL_Color* getCol2() override ;
    void update(InputManager& input) override ;
    void render(SDL_Renderer* rend, int drawtype = 2) override ;
    //

    //
    SpinBox(orient typei = VERT);
    void setType(orient typei);
};
class ColorPicker : public UIelement{

};
class DatePicker : public UIelement{

};
/*
🔹 6. Feedback & Display
*/
class ProgressBar : public UIelement{

};
class Spinner : public UIelement{

};
class Tooltip : public Label{

};
class Notification : public LabelArea{

};
/*
🔹 7. Canvas & Graphics
*/
class Canvas : public UIelement{

};
class ImageViewer : public UIelement{
    protected:
    /*
    * sets path:
    * returns: -1 on clear, 0 on duplicate, 1 on success
    */ 
    virtual int setpath(const std::string& imgpath);
    /*
    * sets path:
    * returns: -1 on clear, 0 on duplicate, 1 on success
    */ 
    virtual int setpath(const char* imgpath = NULL);
    void resize();
    /* inline */ void delTex();
    SDL_Rect box;
    FONT font;
    SDL_Color fg, bg;
    std::string imgname;
    std::string path;
    SDL_Texture* texture;
    public:
    virtual void setPos(int x, int y) override ;
    virtual void setCol1(const SDL_Color& col) override ;
    virtual void setCol2(const SDL_Color& col) override ;
    virtual void setFont(const FONT& font_) override;
    virtual SDL_Rect* getBox() override;
    virtual FONT* getFont() override;
    virtual SDL_Color* getCol1() override ;
    virtual SDL_Color* getCol2() override ;
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override ;
    //
    void settext(const std::string& text) override ;
    std::string& getText() override ;
    // important imps
    int loadImg(SDL_Renderer* rend);
    int loadImgPath(SDL_Renderer* rend, const char* fpath = NULL);
    void setquery();
    /* inline */ const char* getpath() const ;
    /* inline */ const char* getname() const ;
    /* inline */ void setBox(const SDL_Rect& SBox);
    /* inline */ void setBoxDimP(const SDL_Point& point);
    /* inline */ void setBoxDim(int w, int h);
    //
    ImageViewer();
    ImageViewer(const char* fpath);
    ImageViewer(const SDL_Rect& tbox);
    //
    ~ImageViewer();
};
class ImageUI : public ImageViewer{
    protected:
    std::string pathholder;
    int setpath(const std::string& fpath) override;
    int setpath(const char* fpath) override ;
    public:
    void update(InputManager& input);
    ImageUI();
    ImageUI(const char* fpath);
    ImageUI(const SDL_Rect& tbox);
    std::string& getpathholder();
};
class MiniMap : public UIelement{

};
/*
🔹 8. Windows and Dialogs
*/
/*
🔹 9. Advanced (for scriptable apps/editors)
*/