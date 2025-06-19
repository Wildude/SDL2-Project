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
    UIelement() {}
    UIelement(const UIelement& ui) {
        // Copy constructor implementation
    }
    UIelement& operator=(const UIelement& ui) {
        // Assignment operator implementation
        if (this != &ui) {
            // Copy the data members from ui to this object
        }
        return *this;
    }
    ~UIelement() {
        // Destructor implementation
        // Clean up any resources if needed
    }
    virtual FONT& getFont() = 0;
    virtual SDL_Color& getCol1() = 0;
    virtual SDL_Color& getCol2() = 0;
    virtual void render(SDL_Renderer*, SDL_Texture*&, int) = 0; // Pure virtual function for rendering the UI element
};
/*
🔹 1. Text-Based Components
Component	Purpose
Label	Display static text
Textbox / InputField	Accept typed input (text, numbers, etc.)
Textarea	Multi-line input field
Password Field	Like textbox, but hides characters
*/
class Label : public UIelement {
    public:
    Label(const char* str){
        labelText.settext(str);
    }
    Label(int x, int y){
        labelText.setboxpos(x, y);
    }
    Label(const FONT& font){
        labelText.setfont(font);
    }
    Label(const string& text, int x, int y, int w, int h, const FONT& font, SDL_Color* col1 = NULL, SDL_Color* col2 = NULL) 
        : labelText(text, x, y, w, h, font, col1, col2) {
        // Initialize the label text with the provided parameters
    }
    void render(SDL_Renderer* renderer, SDL_Texture*& board, int drawtype = 2) override {
        labelText.draw(renderer, board, drawtype);
        // Render the label text using the provided renderer
    }
    bool isHovered(const SDL_Point& point) const {
        // Check if the point is within the label's bounding box
        const SDL_Rect& box = labelText.getBoxc();
        return SDL_PointInRect(&point, &box);
    }
    bool isHovered(){}
    bool isCurrent(){}
    bool isFocus(){
        return isHovered() || isCurrent();
    }
    bool isClicked(){
        // Check if the label is clicked based on the mouse position
        return isFocus();
    }
    void onHover(UICommand& cmd){
        if(isHovered()){
            if(cmd.getref() != this)cmd.setref(*this);
            cmd.execute();
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
    FONT& getFont() {
        return labelText.getFont();
    }
    SDL_Color& getCol1() {
        return labelText.getCol1();
    }
    SDL_Color& getCol2() {
        return labelText.getCol2();
    }
    private:
    TextBox labelText; // Text to display
};
class InputText : public UIelement {
    public:
    //
    private:
    //
};
class Textarea : public UIelement{
};
class PasswordField : public UIelement{
};
class UIContainer : public UIelement{
    vector<UIelement&> UIlist;
    public:
    UIContainer(){}
    const UIContainer& operator=(const vector<UIelement&>& UIC){
        if(&this->UIlist != &UIC){
            UIlist = UIC;
        }
        return *this;
    }
    const UIContainer& operator=(const UIContainer& UIC){
        *this = UIC;
    }
    UIContainer(vector<UIelement>& UIs){
        for (UIelement& UI : UIs){
            UIlist.push_back(UI);
        }
    }
    void render(SDL_Renderer* renderer, SDL_Texture*& board, int drawtype = 2) override {
        for (UIelement& ui : UIlist) {
            ui.render(renderer, board, drawtype);
        }
    }
};