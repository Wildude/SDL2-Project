ofstream uilog("../Files/Data/GUI.log");
typedef command<GameObject> GameCommand;
struct UIcmdset{
    GameCommand* focus;
    GameCommand* click;
    GameCommand* revert;
};
class UIelement : public GameObject
{
public:
    UIelement() : UIcmds(UIcmdset{NULL, NULL, NULL}), isfocus(false), ishover(false), isclick(false), isrevert(true){
        checkfile();
        uilog << " created UIelement\n";
    }
    UIelement(const UIelement& ui): UIelement(){
        *this = ui;
    }
    UIelement& operator=(const UIelement& ui) {
        // Assignment operator implementation
        if (this != &ui) {
            // Copy the data members from ui to this object
        }
        return *this;
    }
    inline void checkfile(){
        if(!uilog.is_open()){
            uilog.open("../Files/Data/GUI.log", ios::app);
        }
    }
    ~UIelement() {
        uilog << " destroying UIelement\n";
        uilog.close();
        // Destructor implementation
        // Clean up any resources if needed
    }
    virtual void update(InputManager&) = 0;
    virtual void onFocus(GameCommand* focus = NULL){
        UIcmds.focus = focus;
    }
    virtual void onClick(GameCommand* click = NULL){
        UIcmds.click = click;
    }
    virtual void onRevert(GameCommand* revert = NULL){
        UIcmds.revert = revert;
    }
    virtual void setPos(int, int) = 0;
    virtual void setCol1(const SDL_Color&) = 0;
    virtual void setCol2(const SDL_Color&) = 0;
    virtual void setFont(const FONT&) = 0;
    virtual SDL_Rect* getBox() = 0;
    virtual FONT* getFont() = 0;
    virtual SDL_Color* getCol1() = 0;
    virtual SDL_Color* getCol2() = 0;
    virtual void render(SDL_Renderer*, SDL_Texture*&, int) = 0; // Pure virtual function for rendering the UI element
    bool gethover() const {
        return ishover;
    }
    bool getfocus() const {
        return isfocus;
    }
    bool getclick() const {
        return isclick;
    }
    bool getrevert() const {
        return isrevert;
    }

    GameCommand* getFocusCmd() const {
        return UIcmds.focus;
    }
    GameCommand* getClickCmd() const {
        return UIcmds.click;
    }
    GameCommand* getRevertCmd() const{
        return UIcmds.revert;
    }
    //
    virtual bool isClicked(const InputManager&) = 0;
    virtual bool isFocused(const InputManager&) = 0;
    protected:
    bool ishover, isfocus, isclick, isrevert;
    UIcmdset UIcmds;
};
typedef command<UIelement> UICommand;
typedef multiCommand<UIelement> UIMulticommand;
struct UIColor : public UICommand{
    ChangeColorCommand<int> cmd;
    UIColor(): UICommand() , cmd(){}
    UIColor(UIelement& uref) : UICommand(uref), cmd(*ref->getCol2(), *ref->getCol1()){}
    UIColor(const SDL_Color& nbg, const SDL_Color& nfg): UICommand(), cmd(nbg, nfg){}
    void setNew(const SDL_Color& bnew, const SDL_Color& fnew){
        //cout << " setting UI color news\n";
        cmd.setNew(bnew, fnew);
    }
    void setref(UIelement& tref) override {
        //cout << " setting UI color references\n";
        ref = &tref;
        cmd.setRef(*ref->getCol1(), *ref->getCol2());
    }
    void execute(){
        //cout << " executing UI color\n";
        cmd.execute();
    }
    ~UIColor(){}
};
struct UIFont : public UICommand{
    ChangeFontCommand<int> cmd;
    UIFont(): UICommand(), cmd(){}
    UIFont(UIelement& uref) : UICommand(uref), cmd(*ref->getFont()){}
    UIFont(const FONT& font): UICommand(), cmd(font){}
    void setNew(const FONT& font){
        //cout << " setting UI Font news\n";
        cmd.newFont = font;
    }
    void setref(UIelement& tref){
        //cout << " setting UI Font references\n";
        ref = &tref;
        cmd.setRef(*ref->getFont());
    }
    void execute(){
        //cout << " executing UI font\n";
        cmd.execute();
    }
};
class UIPanel : public UIelement{

};
class UIContainer : public UIelement{
    vector<UIelement*> UIlist;
    SDL_Rect box;
    public:
    UIContainer(): box(SDL_Rect{0, 0, 0, 0}), UIelement(){}
    int getsize(){
        return UIlist.size();
    }
    bool isHovered(const InputManager& input) {
        const SDL_Point& mpos = input.getMouseP();
        // Check if the point is within the label's bounding box
        const SDL_Rect& box = *getBox();
        ishover = SDL_PointInRect(&mpos, &box);
        return ishover;
    }
    bool isCurrent(){
        return false;
    }
    bool isFocused(const InputManager& input){
        isfocus = isHovered(input) || isCurrent();
        return isfocus;
    }
    bool isClicked(const InputManager& input){
        isclick = isFocused(input) && input.isMouseDown(SDL_BUTTON_LEFT);
        return isclick;
    }
    vector<UIelement*>& getList(){
        return UIlist;
    }
    const UIContainer& operator=(const vector<UIelement*>& UIC){
        if(&this->UIlist != &UIC){
            UIlist = UIC;
        }
        return *this;
    }
    const UIContainer& operator=(const UIContainer& UIC){
        if(this != &UIC){
            UIlist = UIC.UIlist;
        }
        return *this;
    }
    void update(InputManager& input){
        for(UIelement* ui : UIlist)
        ui->update(input);
    }
    UIContainer(vector<UIelement*>& UIs): UIContainer(){
        for (UIelement* UI : UIs){
            UIlist.push_back(UI);
        }
    }
    void push(UIelement& ui){
        push(&ui);
    }
    void push(UIelement* ui){
        UIlist.push_back(ui);
    }
    void render(SDL_Renderer* renderer, SDL_Texture*& board, int drawtype = 2) override {
        checkfile();
        uilog << " Rending UIelements:\n";
        for (UIelement* ui : UIlist) {
            ui->render(renderer, board, drawtype);
        }
    }
    void setbox(){
        box.w = 0;
        box.h = 0;
        int size = UIlist.size();
        if(!size){
            return;
        }
        for(UIelement* ui : UIlist){
            SDL_Rect* rect = ui->getBox();
            if(rect->w > box.w) box.w = rect->w;
            box.h += rect->h;
        }
    }
    SDL_Color* getCol1(){
        return (UIlist.size() ? UIlist[0]->getCol1() : NULL);
    }
    SDL_Color* getCol2(){
        return (UIlist.size() ? UIlist[0]->getCol2() : NULL);
    }
    FONT* getFont(){
        return (UIlist.size() ? UIlist[0]->getFont() : NULL);
    }
    SDL_Rect* getBox(){
        setbox();
        return &box;
    }
    void apply(){
        applyFont();
        applyCol1();
        applyCol2();
    }
    void applyFont(){
        int size = UIlist.size();
        if(!size)return;
        for(int i = 1; i < size - 1; i++){
            UIlist[i]->setFont(*UIlist[0]->getFont());
        }
    }
    void applyCol1(){
        int size = UIlist.size();
        if(!size)return;
        for(int i = 1; i < size - 1; i++){
            UIlist[i]->setCol1(*UIlist[0]->getCol1());
        }
    }
    void applyCol2(){
        int size = UIlist.size();
        if(!size)return;
        for(int i = 1; i < size - 1; i++){
            UIlist[i]->setCol2(*UIlist[0]->getCol2());
        }
    }
    void setFont(const FONT& font){
        if(!UIlist.size())return;
        // cout << " setting all fonts\n";
        for(UIelement* ui : UIlist){
            ui->setFont(font);
        }
    }
    void setCol1(const SDL_Color& col){
        if(!UIlist.size())return;
        // cout << " setting all fcolors\n";
        for(UIelement* ui : UIlist){
            ui->setCol1(col);
        }
    }
    void setCol2(const SDL_Color& col){
        if(!UIlist.size())return;
        // cout << " setting all fcolors\n";
        for(UIelement* ui : UIlist){
            ui->setCol2(col);
        }
    }
    void setPos(int x, int y){
        int size = UIlist.size();
        if(!size)return;
        // cout << " setting all positions\n";
        vector<UIelement*>& List = UIlist;
        // cout << " p0\n";
        List[0]->setPos(x, y);
        for(int i = 1; i < size; i++){
            List[i]->setPos(x, List[i - 1]->getBox()->h + List[i - 1]->getBox()->y);
        }
    }
    
    void onClick(GameCommand* cmd = NULL){
        UIelement::onClick(cmd);
        int size = UIlist.size();
        if(!size)return;
        for(int i = 0; i < size; i++)
        if(!UIlist[i]->getClickCmd())UIlist[i]->onClick(cmd);
    }
    void onFocus(GameCommand* cmd = NULL){
        UIelement::onFocus(cmd);
        int size = UIlist.size();
        if(!size)return;
        for(int i = 0; i < size; i++)
        if(!UIlist[i]->getFocusCmd())UIlist[i]->onFocus(cmd);
    }
    void onRevert(GameCommand* cmd = NULL){
        UIelement::onRevert(cmd);
        int size = UIlist.size();
        if(!size)return;
        for(int i = 0; i < size; i++)
        if(!UIlist[i]->getRevertCmd())UIlist[i]->onRevert(cmd);
    }
};
/*
🔹 1. Text-Based Components
Component	Purpose
Label	Display static text (done)
Textbox / InputField	Accept typed input (text, numbers, etc.)
Textarea	Multi-line input field
Password Field	Like textbox, but hides characters
*/
class Label : public UIelement {
    public:
    Label(): UIelement(), labelText(){}
    Label(const char* str): Label(){
        labelText.settext(str);
    }
    Label(int x, int y): Label(){
        setPos(x, y);
    }
    Label(const FONT& font): Label(){
        setFont(font);
    }
    Label(const string& text, int x, int y, int w, int h, const FONT& font, SDL_Color* col1 = NULL, SDL_Color* col2 = NULL) 
        : UIelement(), labelText(text, x, y, w, h, font, col1, col2){
        // Initialize the label text with the provided parameters
    }
    void setPos(int x, int y){
        labelText.setboxpos(x, y);
    }
    void setFont(const FONT& font){
        // cout <<" setting label font\n";
        labelText.setfont(font);
    }
    void setCol1(const SDL_Color& col){
        labelText.setcol1(col.r, col.g, col.b, col.a);
    }
    void setCol2(const SDL_Color& col){
        labelText.setcol2(col.r, col.g, col.b, col.a);
    }
    void settext(const char* str){
        labelText.settext(str);
    }
    void settext(const string& str){
        labelText.settext(str);
    }
    void render(SDL_Renderer* renderer, SDL_Texture*& board, int drawtype = 2) override {
        checkfile();
        uilog << " Rendering label: \n";
        labelText.draw(renderer, board, drawtype);
        // Render the label text using the provided renderer
    }
    bool isHovered(const InputManager& input) {
        const SDL_Point& mpos = input.getMouseP();
        // Check if the point is within the label's bounding box
        const SDL_Rect& box = labelText.getBoxc();
        ishover = SDL_PointInRect(&mpos, &box);
        return ishover;
    }
    bool isCurrent() const{
        return false;
    }
    bool isFocused(const InputManager& input){
        isfocus = isHovered(input) || isCurrent();
        return isfocus;
    }
    bool isClicked(const InputManager& input){
        // Check if the label is clicked based on the mouse position
        isclick = isFocused(input) && input.isMouseDown(SDL_BUTTON_LEFT);
        return isclick;
    }
    void update(InputManager& input){
        static bool oldclick = false;
        bool click = isClicked(input);
        bool revert = true;
        if(isfocus){
            if(!oldclick){
                // cout << " clicked\n";
                revert = false;
            }
            oldclick = click;
        }
        else revert = true;
        if(revert){
            if(!isrevert){
                if(UIcmds.revert){
                    if(UIcmds.revert->getref() != this)UIcmds.revert->setref(*this);
                    UIcmds.revert->execute();
                }
            }
            isrevert = true;
        }
        else if(click)
        {
            isrevert = false;
            if(UIcmds.click){
                if(UIcmds.click->getref() != this)UIcmds.click->setref(*this);
                UIcmds.click->execute();
            }
        }
        else if(UIcmds.focus){
            isrevert = false;
            if(UIcmds.focus->getref() != this)UIcmds.focus->setref(*this);
            UIcmds.focus->execute();
        }
    }
    FONT* getFont() {
        return labelText.getFontP();
    }
    SDL_Color* getCol1() {
        return labelText.getCol1P();
    }
    SDL_Color* getCol2() {
        return labelText.getCol2P();
    }
    SDL_Rect* getBox(){
        return labelText.getBoxP();
    }
    private:
    TextBox labelText; // Text to display
};
class InputBox : public Label{

};
class LabelArea : public Label{

};
class InputArea : public LabelArea{

};
class PasswordBox : InputBox{

};
/*
🔹 2. Buttons & Interaction
Component	Purpose
Button	Triggers an action on click
Toggle Button	On/off switch (like a checkbox visually)
Radio Button	One of several mutually exclusive choices
Checkbox	Independent boolean toggle
Hyperlink	Clickable text that acts like a link
*/
class Button : public UIelement {
    // Button implementation
};
class ToggleButton : public Button {
    // Toggle button implementation
};
class RadioButton : public UIelement{

};
class CheckBox : public UIelement{

};

/*
🔹 3. Selection & Lists
Component	Purpose
Dropdown / ComboBox	Shows a list of options when clicked
ListBox	Static list of selectable items
Multi-select List	Allows selecting multiple items
Autocomplete Box	Shows suggestions as user types
*/
class Dropdown : public UIelement {
    // Dropdown implementation
};
class ListBox : public Dropdown{

};
class MultiSelect : public ListBox{

};
class AutoCompleteBox : public Dropdown{

};

/*
🔹 4. Containers & Layouts
Component	Purpose
Panel	Groups other widgets
Scroll View	Enables scrolling within a region
Tabs	Switch between views
Grid/Column Layouts	Organize widgets in structured layouts
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

/*
🔹 5. Sliders & Selectors
Component	Purpose
Slider	Drag a knob to choose a value
SpinBox	Input number with +/− buttons
Color Picker	Choose color interactively
Date Picker	Pick a date from a calendar
*/
class Slider : public UIelement{

};
class SpinBox : public UIelement{

};
class ColorPicker : public UIelement{

};
class DatePicker : public UIelement{

};
/*
🔹 6. Feedback & Display
Component	Purpose
Progress Bar	Visual progress indicator
Loading Spinner	Show busy/loading state
Tooltip	Small popup text on hover
Notification / Toast	Temporary popup message
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
Component	Purpose
Canvas / Viewport	Custom-drawn area for rendering
Image Viewer	Show and scale images
Mini-map / Nav	Like a 2D preview or interactive overlay
*/
class Canvas : public UIelement{

};
class ImageViewer : public UIelement{

};
class MiniMap : public UIelement{

};
/*
🔹 8. Windows and Dialogs
Component	Purpose
Window	A movable/closable container
Modal Dialog	Blocks interaction until resolved
Message Box	Shows alert/info messages
File Picker	Choose files or directories

🔹 9. Advanced (for scriptable apps/editors)
Component	Purpose
Property Inspector	Shows editable fields for selected object
Hierarchy Panel	Shows parent-child tree (like scenes)
Event Log Console	Text area for logging/debug messages
Docking System	Repositionable tool windows
*/