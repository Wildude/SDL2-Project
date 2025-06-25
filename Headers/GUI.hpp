ofstream uilog("../Files/Data/GUI.log");
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
    } UIcmds;
    public:
    UIelement(const UIcmdset& cmd = UIcmdset{NULL, NULL, NULL}, 
        bool focus = false, bool hover = false, bool click = false, bool revert = true) 
        : UIcmds(cmd), isfocus(focus), ishover(hover), isclick(click), isrevert(revert){
        checkfile();
        uilog << " created UIelement\n";
    }
    UIelement(const UIelement& ui): UIelement(){
        *this = ui;
    }
    UIelement& operator=(const UIelement& ui) {
        // Assignment operator implementation
        if (this != &ui) {
            UIcmds = ui.UIcmds;
            isfocus = ui.isfocus;
            isrevert = ui.isrevert;
            isclick = ui.isclick;
            ishover = ui.ishover;
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
    virtual void update(InputManager& input){
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
            // cout << " clicking\n";
            if(UIcmds.click->getref() != this){
                //cout << " was not ref\n";
                UIcmds.click->setref(*this);
            }
            //else cout << " was refed\n";
            //cout << " executing\n";
            UIcmds.click->execute();
            //cout << " executed\n";
            /*
            if(UIcmds.click){
                cout << " clicked\n";
                if(UIcmds.click->getref() != this)UIcmds.click->setref(*this);
                cout << " executing\n";
                UIcmds.click->execute();
            }
            */
        }
        else if(UIcmds.focus){
            isrevert = false;
            if(UIcmds.focus->getref() != this)UIcmds.focus->setref(*this);
            UIcmds.focus->execute();
        }
    };
    virtual void onFocus(UICommand* focus = NULL){
        UIcmds.focus = focus;
    }
    virtual void onClick(UICommand* click = NULL){
        UIcmds.click = click;
    }
    virtual void onRevert(UICommand* revert = NULL){
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
    virtual void settext(const string& text){}
    virtual string& getText() {}
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

    UICommand* getFocusCmd() const {
        return UIcmds.focus;
    }
    UICommand* getClickCmd() const {
        return UIcmds.click;
    }
    UICommand* getRevertCmd() const{
        return UIcmds.revert;
    }
    //
    virtual bool isHovered(const InputManager& input){
        const SDL_Point& mpos = input.getMouseP();
        const SDL_Rect& mbox = *getBox();
        ishover = SDL_PointInRect(&mpos, &mbox);
        return ishover;
    }
    virtual bool isClicked(InputManager&) = 0;
    virtual bool isFocused(const InputManager&) = 0;
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
    void execute() override{
        //cout << " executing UI color\n";
        if(!ref){
            //cout << " no UI reference\n";
            return;
        }
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
        if(!ref){
            //cout << " no UI reference\n";
            return;
        }
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
    bool isClicked(InputManager& input){
        isclick = isFocused(input) && input.isMouseReady(SDL_BUTTON_LEFT);
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
    void update(InputManager& input) override {
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
    
    void onClick(UICommand* cmd = NULL){
        UIelement::onClick(cmd);
        int size = UIlist.size();
        if(!size)return;
        for(int i = 0; i < size; i++)
        if(!UIlist[i]->getClickCmd())UIlist[i]->onClick(cmd);
    }
    void onFocus(UICommand* cmd = NULL){
        UIelement::onFocus(cmd);
        int size = UIlist.size();
        if(!size)return;
        for(int i = 0; i < size; i++)
        if(!UIlist[i]->getFocusCmd())UIlist[i]->onFocus(cmd);
    }
    void onRevert(UICommand* cmd = NULL){
        UIelement::onRevert(cmd);
        int size = UIlist.size();
        if(!size)return;
        for(int i = 0; i < size; i++)
        if(!UIlist[i]->getRevertCmd())UIlist[i]->onRevert(cmd);
    }
};
/*
🔹 1. Text-Based Components
*/
template <class T>
struct ChangeStringCmd : public command<T>{
    string* textTo;
    SDL_Scancode quitCase;
    bool iswriting;
    TextInputHandler* inputHandler;
    ChangeStringCmd(TextInputHandler* input = NULL, T* ref = NULL, string* textp = NULL) : command<T>(ref), inputHandler(input), textTo(textp), iswriting(false), quitCase(SDL_SCANCODE_RETURN){
        
    }
    void setInputer(TextInputHandler& inputH){
        inputHandler = &inputH;
    }
    void setInputer(TextInputHandler* inputH = NULL){
        inputHandler = inputH;
    }
    void setTextP(string* textp = NULL){
        textTo = textp;
    }
    void setwriting(bool write){
        iswriting = write;
        if(!iswriting)inputHandler->setInput();
    }
    virtual void execute(){
        if(!textTo){
            // cout << " cmd error no textTo\n";
            return;
        }
        if(!inputHandler){
            // cout << " cmd error no inputer\n";
            return;
        }
        //if(!command<T>::ref)cout << " no ref though\n";
        //else cout << " there's reference\n";
        //cout << " cmd writing\n";
        //if(textTo)cout << " text before: " << *textTo << endl;
        if(!iswriting){
            //cout << " rewriting\n";
            inputHandler->clearText();
        }
        //cout << " writing\n";
        inputHandler->setInput(textTo);
        inputHandler->setQuitCase(quitCase);
        //cout << " text pointer set\n";
        if(!inputHandler->checkText())inputHandler->setTextUse(true);
        //cout << " textuse checked\n";
        iswriting = true;
    }
};
struct ChangeStringUIcmd : public UICommand {
    string* textTo;
    SDL_Scancode quitCase;
    bool iswriting;
    TextInputHandler* inputHandler;
    ChangeStringUIcmd(TextInputHandler* input = NULL, UIelement* ref = NULL, string* textN = NULL) : command<UIelement>(ref), inputHandler(input), iswriting(false), quitCase(SDL_SCANCODE_RETURN), textTo(textN){

    }
    void setInputer(TextInputHandler& inputH){
        inputHandler = &inputH;
    }
    void setInputer(TextInputHandler* inputH = NULL){
        inputHandler = inputH;
    }
    void checktext(){
        if(!inputHandler->getTextState()){
            // cout << " quitcase\n";
            setwriting(false);
        }
    }
    void setwriting(bool write){
        // cout << " setting writing to false/true\n";
        iswriting = write;
        if(!iswriting){
            // cout << " quit textmode\n";
            inputHandler->setTextUse(false);
            setTextTo();
        }
    }
    void setTextTo(string* textto = NULL){
        textTo = (textto ? textto : ref ? &ref->getText() : NULL);
    }
    void execute() override{
        // cout << " exec inbox\n";
        if(!inputHandler){
            //cout << " cmd error no inputer\n";
            return;
        }
        if(!command<UIelement>::ref){
            //cout << " no ref\n";
            return;
        }
        //else cout << " there's reference\n";
        //cout << " cmd writing\n";
        if(!iswriting){
            // cout << " rewriting\n";
            inputHandler->clearText();
        }
        else cout << " just writing\n";
        inputHandler->setInput(textTo);
        if(!inputHandler->checkText())inputHandler->setTextUse(true);
        iswriting = true;
    }
};
class Label : public UIelement {
    public:
    Label(const UIcmdset& cmd = UIcmdset{NULL, NULL, NULL}, 
        bool focus = false, bool hover = false, bool click = false, bool revert = true)
        : UIelement(cmd, focus, hover, click, revert), labelText(){}
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
    void settext(const string& str) override {
        labelText.settext(str);
    }
    void render(SDL_Renderer* renderer, SDL_Texture*& board, int drawtype = 2) override {
        checkfile();
        uilog << " Rendering label: \n";
        labelText.draw(renderer, board, drawtype);
        // Render the label text using the provided renderer
    }
    bool isCurrent() const{
        return false;
    }
    bool isFocused(const InputManager& input){
        isfocus = isHovered(input) || isCurrent();
        return isfocus;
    }
    bool isClicked(InputManager& input){
        // Check if the label is clicked based on the mouse position
        isclick = isFocused(input) && input.isMouseReady(SDL_BUTTON_LEFT);
        return isclick;
    }
    string& getText(){
        return labelText.getTextRef();
    }
    const char* gettext(){
        return labelText.getText();
    }
    string& gettextRef(){
        return labelText.getTextRef();
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
    protected:
    TextBox labelText; // Text to display
};

class InputBox : public Label{
    multiCommand<UIelement>& multref;
    SDL_Color boxColor;
public:
    InputBox() : Label(UIcmdset({NULL, new multiCommand<UIelement>(this), NULL})), 
    multref(*static_cast<multiCommand<UIelement>*>(UIcmds.click)), boxColor(SDL_Color({0, 0, 0, 0})){
        //cout << " input boxing\n";
        //if(UIcmds.click == NULL)cout << " click not okay\n";
        multref.push((new ChangeStringUIcmd(NULL, this)));
        //ChangeStringCmd<UIelement>* temp = new ChangeStringCmd<UIelement>(NULL, this, &labelText.getTextRef());
        //multcom.push(static_cast<UICommand*>(temp));
    }
    InputBox(const char* str) : InputBox() {
        settext(str);
    }
    InputBox(int x, int y) : InputBox() {
        setPos(x, y);
    }
    InputBox(const FONT& font) : InputBox() {
        setFont(font);
    }
    InputBox(const string& text, int x, int y, int w, int h, const FONT& font, SDL_Color* col1 = NULL, SDL_Color* col2 = NULL)
        : Label(text, x, y, w, h, font, col1, col2), multref(*(multiCommand<UIelement>*)UIcmds.click), boxColor(SDL_Color({0, 0, 0, 0})){
        // Initialize the input text with the provided parameters
    }
    bool isCurrent() const{
        return false;
    }
    void onClick(UICommand* cmd = NULL) override {
        multref.push(cmd);
        //multcom.push(cmd);
    }
    void update(InputManager& input) override {
        TextInputHandler& inputT = *static_cast<TextInputHandler*>(&input);
        static ChangeStringUIcmd& inputSetter = *static_cast<ChangeStringUIcmd*>(multref.getcmd(0));
        //static ChangeStringCmd<UIelement>* inputSetter = reinterpret_cast<ChangeStringCmd<UIelement>*>(multcom.getcmd(0));
        inputSetter.setInputer(inputT);
        //cout << " checking click\n";
        //if(UIcmds.click == NULL)cout << " click okay\n";;
        Label::update(input);
        inputSetter.checktext();
        settext(inputSetter.textTo ? *inputSetter.textTo : labelText.getText());
        if(!isfocus && input.isMouseReady(SDL_BUTTON_LEFT, 60) || input.isMouseReady(SDL_BUTTON_RIGHT, 60))inputSetter.setwriting(false);
    }
    void render(SDL_Renderer* rend, SDL_Texture*& board, int drawtype = 2) override {
        const SDL_Color& bk = boxColor;
        SDL2::setRenCol(rend, bk);
        TEXTURE::drawRect(*getBox(), rend);
        Label::render(rend, board, drawtype);
    }
    void setBoxCol(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
        boxColor = {r, g, b, a};
    }
    void setBoxCol(const SDL_Color& col){
        boxColor = col;
    }
    const SDL_Color& getBoxCol(){
        return boxColor;
    }
    ~InputBox(){
        delete multref.getcmd(0);
    }
};
class LabelArea : public Label{

};
class InputArea : public LabelArea{

};
class PasswordBox : InputBox{

};
/*
🔹 2. Buttons & Interaction
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
    ChangeLevelUIcmd(InputManager* input = NULL, UIelement* ref = NULL, SDL_Scancode quiter = SDL_SCANCODE_ESCAPE): UICommand(ref), inputHandler(input), quitCase(quiter), increaseCase(SDL_SCANCODE_UP), decreaseCase(SDL_SCANCODE_DOWN){}
    void setRef(InputManager* input = NULL){
        inputHandler = input;
    }
    inline void quitit(){
        increase = NULL;
        decrease = NULL;
    }
    cond checkcond(){
        // cout << " checking condition\n";
        cond ret = NTN;
        if(!increase || !decrease)return EXT;
        if(!inputHandler)return EXT;
        //cout << " checking quitcase:\n";
        if(inputHandler->isKeyDown(quitCase)){
            ret = EXT;
        }
        else{
            if(*increase)ret = INC;
            else if(*decrease)ret = DEC;
        }
        return ret;
    }
    void setIncrease(SDL_Scancode inced = SDL_SCANCODE_UP){
        increaseCase = inced;
    }
    void setDecrease(SDL_Scancode deced = SDL_SCANCODE_DOWN){
        decreaseCase = deced;
    }
    void setQuit(SDL_Scancode quitC){
        quitCase = quitC;
    }
    void execute(){
        //cout << " executionist\n";
        if(!inputHandler){
             //cout << " input handler problem\n";
            return;
        }
        //else cout << " doing it\n";
        array<bool, SDL_NUM_SCANCODES>& keyDowns = inputHandler->getKeyDowns();
        increase = &keyDowns[increaseCase];
        decrease = &keyDowns[decreaseCase];
        //cout << " done\n";
    }
};
/*
🔹 5. Sliders & Selectors
*/
class Slider : public UIelement{
    private:
    multiCommand<UIelement>& multref;
    SDL_Rect box;
    SDL_Color fg, bg;
    short portion;
    enum orient{VERT, HORI}type;
    public:
    Slider(bool focus = false, bool hover = false, bool click = false, bool revert = true)
        : UIelement(UIcmdset({NULL, new multiCommand<UIelement>(this)}), focus, hover, click, revert), 
        multref(*static_cast<multiCommand<UIelement>*>(UIcmds.click)), portion(50){
            //UIcmds.click->setref(*this);
            multref.push(new ChangeLevelUIcmd(NULL, this));
        }
    Slider(orient slideType): UIelement(UIcmdset({NULL, new multiCommand<UIelement>(this)})), 
    type(slideType), multref(*static_cast<multiCommand<UIelement>*>(UIcmds.click)), portion(50){
        multref.push(new ChangeLevelUIcmd(NULL, this));
    }
    Slider(const SDL_Rect& slidebox): UIelement(UIcmdset({NULL, new multiCommand<UIelement>(this)})), 
    box(slidebox), multref(*static_cast<multiCommand<UIelement>*>(UIcmds.click)), portion(50){
        multref.push(new ChangeLevelUIcmd(NULL, this));
        checkbox();
    }
    void setType(orient slideType){
        type = slideType;
    }
    void setportion(short port){
        portion = port;
        checkportion();
    }
    void checkbox(){
        if(box.w > box.h)type = HORI;
        else type = VERT;
    }
    void setPos(int x, int y) override {
        box.x = x;
        box.y = y;
    }
    void setBox(int w, int h){
        box.w = w;
        box.h = h;
        checkbox();
    }
    SDL_Color* getCol1() override {
        return &fg;
    }
    SDL_Color* getCol2() override {
        return &bg;
    }
    FONT* getFont() override {
        return NULL;
    }
    SDL_Rect* getBox() override {
        return &box;
    }
    void update(InputManager& input) override {
        static ChangeLevelUIcmd& refcheck = *static_cast<ChangeLevelUIcmd*>(multref.getcmd(0));
        refcheck.setRef(&input);
        UIelement::update(input);
        cond curr = refcheck.checkcond();
        setascond(curr);
        if(curr == EXT){
            // cout << " slider exit\n";
            refcheck.quitit();
            return;
        }
        else{
            int size = multref.commands.size();
            for(int i = 1; i < size; i++){
                multref.getcmd(i)->execute();
            }
            isrevert = false;
        }
    }
    inline void checkportion(){
        if(portion > 100)portion = 100;
        if(portion < 0)portion = 0;
    }
    inline short getportion() const {
        return portion;
    }
    inline void setascond(cond curr){
        switch (curr){
            case INC:
            portion += 1;
            break;
            case DEC:
            portion -= 1;
            break;            
            default:
            break;
        }
        checkportion();
    }
    void render(SDL_Renderer* rend, SDL_Texture*& tex, int drawt = 2) override {
        float percent = portion * 0.01;
        int width = type == HORI ? (int)((float)box.w * percent) - 1 : box.w - 1;
        int height = type == VERT ? (int)((float)box.h * percent) - 1 : box.h - 1;
        if(width < 0)width = 0;
        if(height < 0)height = 0;
        SDL_Rect boxportion = {box.x + 1, type == HORI ? box.y + 1 : box.y + 1 + (int)((float)box.h * (1.0f - percent)), width, height};
        SDL2::setRenCol(rend, bg);
        SDL_RenderFillRect(rend, &boxportion);
        SDL2::setRenCol(rend, fg);
        int drawtype = drawt <= 2 ? type == HORI ? box.h/2 : box.w/2 : drawt;
        TEXTURE::drawRect(box, rend, drawtype);
    }
    void setCol1(const SDL_Color& col) override {
        fg = col;
    }
    void setCol2(const SDL_Color& col) override {
        bg = col;
    }
    void setFont(const FONT& font) override {
        return;
    }
    bool isCurrent(){
        return false;
    }
    bool isFocused(const InputManager& input){
        isfocus = isHovered(input) || isCurrent();
        return isfocus;
    }
    bool isClicked(InputManager& input){
        isclick = isFocused(input) && input.isMouseReady(SDL_BUTTON_LEFT);
        return isclick;
    }
    void onClick(UICommand* cmd = NULL) override {
        multref.push(cmd);
    }
    ~Slider(){
        delete multref.getcmd(0);
    }
};
class SpinBox : public UIelement{

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
    SDL_Rect Box;
    SDL_Texture* texture;
    string imgname;
    char* path;
    public:
    ImageViewer(): UIelement(){}
};
class MiniMap : public UIelement{

};
/*
🔹 8. Windows and Dialogs
*/
/*
🔹 9. Advanced (for scriptable apps/editors)
*/