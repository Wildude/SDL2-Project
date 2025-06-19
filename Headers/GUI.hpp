// GUI of game
/* Types of UI elements
🔹 1. Text-Based Components
Component	Purpose
Label	Display static text
Textbox / InputField	Accept typed input (text, numbers, etc.)
Textarea	Multi-line input field
Password Field	Like textbox, but hides characters

🔹 2. Buttons & Interaction
Component	Purpose
Button	Triggers an action on click
Toggle Button	On/off switch (like a checkbox visually)
Radio Button	One of several mutually exclusive choices
Checkbox	Independent boolean toggle
Hyperlink	Clickable text that acts like a link

🔹 3. Selection & Lists
Component	Purpose
Dropdown / ComboBox	Shows a list of options when clicked
ListBox	Static list of selectable items
Multi-select List	Allows selecting multiple items
Autocomplete Box	Shows suggestions as user types

🔹 4. Containers & Layouts
Component	Purpose
Panel	Groups other widgets
Scroll View	Enables scrolling within a region
Tabs	Switch between views
Grid/Column Layouts	Organize widgets in structured layouts

🔹 5. Sliders & Selectors
Component	Purpose
Slider	Drag a knob to choose a value
SpinBox	Input number with +/− buttons
Color Picker	Choose color interactively
Date Picker	Pick a date from a calendar

🔹 6. Feedback & Display
Component	Purpose
Progress Bar	Visual progress indicator
Loading Spinner	Show busy/loading state
Tooltip	Small popup text on hover
Notification / Toast	Temporary popup message

🔹 7. Canvas & Graphics
Component	Purpose
Canvas / Viewport	Custom-drawn area for rendering
Image Viewer	Show and scale images
Mini-map / Nav	Like a 2D preview or interactive overlay

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
class UIelement
{
public:
    UIelement(): commands(NULL){}
    UIelement(const UIelement& ui){
        *this = ui;
    }
    UIelement& operator=(const UIelement& ui) {
        // Assignment operator implementation
        if (this != &ui) {
            commands = ui.commands;
            // Copy the data members from ui to this object
        }
        return *this;
    }
    ~UIelement() {
        // Destructor implementation
        // Clean up any resources if needed
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
    command<UIelement>** commands;
};
typedef command<UIelement> UICommand;
typedef multiCommand<UICommand> UIMulticommand;
struct UIColor : public UICommand{
    ChangeColorCommand<int> cmd;
    UIColor(): UICommand() , cmd(){}
    UIColor(UIelement& uref) : UICommand(uref), cmd(*ref->getCol1(), *ref->getCol2()){}
    UIColor(const SDL_Color& nbg, const SDL_Color& nfg): UICommand(), cmd(nbg, nfg){}
    void setNew(const SDL_Color& bnew, const SDL_Color& fnew){
        cout << " setting UI color news\n";
        cmd.setNew(bnew, fnew);
    }
    void setref(UIelement& tref) override {
        cout << " setting UI color references\n";
        ref = &tref;
        cmd.setRef(*ref->getCol1(), *ref->getCol2());
    }
    void execute(){
        cout << " executing UI color\n";
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
        cout << " setting UI Font news\n";
        cmd.newFont = font;
    }
    void setref(UIelement& tref){
        cout << " setting UI Font references\n";
        ref = &tref;
        cmd.setRef(*ref->getFont());
    }
    void execute(){
        cout << " executing UI font\n";
        cmd.execute();
    }
};

/*
🔹 1. Text-Based Components
Component	Purpose
Label	Display static text
Textbox / InputField	Accept typed input (text, numbers, etc.)
Textarea	Multi-line input field
Password Field	Like textbox, but hides characters
*/
FONT GUIFONT;
multiCommand<UIelement> GUIMultiCommand;
class Label : public UIelement {
    public:
    SDL_Point* mousepos;
    bool click;
    Label(): mousepos(NULL), click(false){
        commands = new UICommand*[4];
        commands[0] = NULL;
        commands[1] = NULL;
        commands[2] = NULL;
        commands[3] = NULL;
    }
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
        : labelText(text, x, y, w, h, font, col1, col2){
        mousepos = NULL;
        click = false;
        commands = new command<UIelement>*[4];
        commands[0] = NULL;
        commands[1] = NULL;
        commands[2] = NULL;
        commands[3] = NULL;
        // Initialize the label text with the provided parameters
    }
    void setPos(int x, int y){
        labelText.setboxpos(x, y);
    }
    void setFont(const FONT& font){
        labelText.setfont(font);
    }
    void setCol1(const SDL_Color& col){
        labelText.setcol1(col.r, col.g, col.b, col.a);
    }
    void setCol2(const SDL_Color& col){
        labelText.setcol2(col.r, col.g, col.b, col.a);
    }
    void render(SDL_Renderer* renderer, SDL_Texture*& board, int drawtype = 2) override {
        goto just_draw;
        if(!commands[0]){
            cout << " empty command 0\n";
            commands[0] = new UIColor(*getCol1(), *getCol2());
        }
        cout << " quit commandeer 0\n";
        if(onHover(*commands[0])){
            if(!commands[1]){
                cout << " empty command 1\n";
                GUIFONT = *getFont();
                GUIFONT.setStyle(TTF_STYLE_BOLD);
                commands[1] = new UIFont(GUIFONT);
            }
            onClick(*commands[1]);
        }
        just_draw:
        cout << " drawing\n";
        labelText.draw(renderer, board, drawtype);
        // Render the label text using the provided renderer
    }
    bool isHovered(const SDL_Point& point) const {
        // Check if the point is within the label's bounding box
        const SDL_Rect& box = labelText.getBoxc();
        return SDL_PointInRect(&point, &box);
    }
    bool isHovered(){
        return isHovered(*mousepos);
    }
    bool isCurrent(){
        return false;
    }
    bool isFocus(){
        return isHovered() || isCurrent();
    }
    bool isClicked(){
        // Check if the label is clicked based on the mouse position
        return isHovered() && click;
    }
    void revert(UICommand& cmd){
        if(cmd.getref() != this)cmd.setref(*this);
        cmd.execute();
    }
    int onHover(UICommand& cmd){
        if(isHovered()){
            cout << " is hovered\n";
            if(cmd.getref() != this)cmd.setref(*this);
            cmd.execute();
            return true;
        }
        else{
            cout << " not hovered\n";
            return false;
        }
    }
    void onClick(UICommand& cmd){
        if(isClicked()){
            if(cmd.getref() != this)cmd.setref(*this);
            cmd.execute();
        }
    }
    void onFocus(UICommand& cmd){
        if(isFocus()){
            if(cmd.getref() != this)cmd.setref(*this);
            cmd.execute();
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
class InputText : public UIelement {
};
class Textarea : public UIelement{
};
class PasswordField : public UIelement{
};
class UIContainer : public UIelement{
    vector<UIelement*> UIlist;
    public:
    UIContainer(){}
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
    UIContainer(vector<UIelement*>& UIs){
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
        for (UIelement* ui : UIlist) {
            ui->render(renderer, board, drawtype);
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
        return (UIlist.size() ? UIlist[0]->getBox() : NULL);
    }
    void apply(){
        applyFont();
        applyCol1();
        applyCol2();
        applycommands();
    }
    void applycommands(UICommand** cmds = NULL){
        int size = UIlist.size();
        if(!size)return;
        if(cmds)UIlist[0]->commands = cmds;
        for(int i = 1; i < size - 1; i++){
            UIlist[i]->commands = UIlist[0]->commands;
        }
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
        int size = UIlist.size();
        if(!size)return;
        for(int i = 0; i < size - 1; i++){
            UIlist[i]->setFont(font);
        }
    }
    void setCol1(const SDL_Color& col){
        int size = UIlist.size();
        if(!size)return;
        for(int i = 0; i < size - 1; i++){
            UIlist[i]->setCol1(col);
        }
    }
    void setCol2(const SDL_Color& col){
        int size = UIlist.size();
        if(!size)return;
        for(int i = 0; i < size - 1; i++){
            UIlist[i]->setCol2(col);
        }
    }
    void setPos(int x, int y){
        int size = UIlist.size();
        if(!size)return;
        UIlist[0]->setPos(x, y);
        for(int i = 1; i < size - 1; i++){
            UIlist[i]->setPos(UIlist[0]->getBox()->x, UIlist[i - 1]->getBox()->y + UIlist[i - 1]->getBox()->h);
        }
    }
    void setCommands(UICommand** cmds){
        int size = UIlist.size();
        if(!size)return;
        for(int i = 0; i < 2; i++)
        UIlist[0]->commands[i] = cmds[i];
        applycommands();
    }
};