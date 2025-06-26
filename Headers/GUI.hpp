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
    // abstract imps
    virtual void setPos(int, int) = 0;
    virtual void setCol1(const SDL_Color&) = 0;
    virtual void setCol2(const SDL_Color&) = 0;
    virtual void setFont(const FONT&) = 0;
    virtual SDL_Rect* getBox() = 0;
    virtual FONT* getFont() = 0;
    virtual SDL_Color* getCol1() = 0;
    virtual SDL_Color* getCol2() = 0;
    virtual void render(SDL_Renderer*, SDL_Texture*&, int) = 0; // Pure virtual function for rendering the UI element
    // repeated imps
    virtual bool isFocused(InputManager& input){
        isfocus = isHovered(input) || isCurrent(input);
        return isfocus;
    }
    virtual bool isClicked(InputManager& input){
        isclick = isFocused(input) && input.isMouseReady(SDL_BUTTON_LEFT);
        return isclick;
    }
    virtual bool isCurrent(InputManager& input) {
        return false;
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
            if(UIcmds.click){
                if(UIcmds.click->getref() != this){
                    UIcmds.click->setref(*this);
                }
                UIcmds.click->execute();
            }
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
    virtual bool isHovered(const InputManager& input){
        const SDL_Point& mpos = input.getMouseP();
        const SDL_Rect& mbox = *getBox();
        ishover = SDL_PointInRect(&mpos, &mbox);
        return ishover;
    }
    // meaningless imps
    virtual void settext(const string& text){}
    virtual string& getText() {}
    // important imps
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
    // constructors and such
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
        if (this != &ui) {
            UIcmds = ui.UIcmds;
            isfocus = ui.isfocus;
            isrevert = ui.isrevert;
            isclick = ui.isclick;
            ishover = ui.ishover;
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
    const UIelement* getref() const override {
        //cout << " UI font change get ref called\n";
        return UICommand::getref();
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
class UIContainer : public UIelement{
    protected:
    vector<UIelement*> UIlist;
    SDL_Rect box;
    SDL_Color fg, bg;
    public:
    UIContainer(): box(SDL_Rect{0, 0, 0, 0}), UIelement(){
    }
    int getsize(){
        return UIlist.size();
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
        uilog << " Rendering UIelements:\n";
        for (UIelement* ui : UIlist) {
            ui->render(renderer, board, drawtype);
        }
    }
    SDL_Color* getCol1(){
        return &fg;
    }
    SDL_Color* getCol2(){
        return &bg;
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
    void setFont(const FONT& font) override {
        if(!UIlist.size())return;
        // cout << " setting all fonts\n";
        for(UIelement* ui : UIlist){
            ui->setFont(font);
        }
    }
    void setCol1(const SDL_Color& col) override {
        if(!UIlist.size())return;
        // cout << " setting all fcolors\n";
        for(UIelement* ui : UIlist){
            ui->setCol1(col);
        }
    }
    void setCol2(const SDL_Color& col) override {
        if(!UIlist.size())return;
        // cout << " setting all fcolors\n";
        for(UIelement* ui : UIlist){
            ui->setCol2(col);
        }
    }
    void onClick(UICommand* cmd = NULL) override {
        UIelement::onClick(cmd);
        int size = UIlist.size();
        if(!size)return;
        for(int i = 0; i < size; i++)
        if(!UIlist[i]->getClickCmd())UIlist[i]->onClick(cmd);
    }
    void onFocus(UICommand* cmd = NULL) override {
        UIelement::onFocus(cmd);
        int size = UIlist.size();
        if(!size)return;
        for(int i = 0; i < size; i++)
        if(!UIlist[i]->getFocusCmd())UIlist[i]->onFocus(cmd);
    }
    void onRevert(UICommand* cmd = NULL) override {
        UIelement::onRevert(cmd);
        int size = UIlist.size();
        if(!size)return;
        for(int i = 0; i < size; i++)
        if(!UIlist[i]->getRevertCmd())UIlist[i]->onRevert(cmd);
    }
    //
    virtual void setPos(int x, int y) override {
        uilog << " setting UIContainer pos:\n";
        box.x = x;
        box.y = y;
        int size = UIlist.size();
        if(!size){
            uilog << " Empty container\n";
            return;
        }
        uilog << " pos0 " << x << " , " << y << endl;
        UIlist[0]->setPos(x, y);
        for(int i = 1; i < size; i++){
            int yp = UIlist[i - 1]->getBox()->h + UIlist[i - 1]->getBox()->y;
            uilog << " pos " << i << " " << x << " , " << yp << endl;
            UIlist[i]->setPos(x, yp);
        }
    }
    virtual void setbox(){
        uilog << " setting UIContainer box\n";
        box.w = 0;
        box.h = 0;
        for(UIelement* ui : UIlist){
            SDL_Rect* rect = ui->getBox();
            if(rect->w > box.w) box.w = rect->w;
            uilog << " rbox: " << rect->w << ", " << rect->h << endl;
            box.h += rect->h;
        }
        uilog << " box: " << box.w << ", " << box.h << endl;
    }
};
class UIPanel : public UIContainer{
    public:
    void setPos(int x, int y) override {
        uilog << " setting UIPanel pos:\n";
        int size = UIlist.size();
        if(!size){
            uilog << " Empty panel\n";
            return;
        }
        uilog << " pos0 " << x << " , " << y << endl;
        UIlist[0]->setPos(x, y);
        for(int i = 1; i < size; i++){
            int xp = UIlist[i - 1]->getBox()->w + UIlist[i - 1]->getBox()->x;
            uilog << " pos " << i << " " << xp << " , " << y << endl;
            UIlist[i]->setPos(xp, y);
        }
    }
    void setbox() override {
        uilog << " setting UIPanel Box\n";
        box.w = 0;
        box.h = 0;
        for(UIelement* ui : UIlist){
            SDL_Rect* rect = ui->getBox();
            if(rect->h > box.h) box.h = rect->h;
            uilog << " rbox: " << rect->w << ", " << rect->h << endl;
            box.w += rect->w;
        }
        uilog << " box: " << box.w << ", " << box.h << endl;
    }
};
/*
🔹 1. Text-Based Components
*/
struct ChangeStringUICmd : public UICommand{
    ChangeStringCommand<UIelement> cmd;
    ChangeStringUICmd(UIelement* ref = NULL, string* textp = NULL) : UICommand(ref), cmd(ref, textp){

    }
    void setref(UIelement& ref) override {
        UICommand::setref(ref);
        cmd.setref(ref);
    }
    void setref(UIelement* ref) override {
        UICommand::setref(ref);
        cmd.setref(ref);
    }
    void setTextP(string* textp = NULL){
        cmd.setStrRef(textp);
    }
    void setNewStr(const string& newstr){
        cmd.setNewString(newstr);
    }
    void setNewStr(const char* newstr = ""){
        cmd.setNewString(newstr);
    }
    virtual void execute(){
        if(!ref){
            // cout << " cmd error no textTo\n";
            return;
        }
        // cout << " executing main command\n";
        cmd.execute();
    }
};
struct InputStringUIcmd : public UICommand {
    InputStringCommand<UIelement> cmd;
    InputStringUIcmd(TextInputHandler* input = NULL, UIelement* ref = NULL, string* textN = NULL, 
        SDL_Scancode quitCase = SDL_SCANCODE_ESCAPE) : command<UIelement>(ref), cmd(input, ref, textN){

    }
    void setref(UIelement& ref){
        UICommand::setref(ref);
        cmd.setref(ref);
    }
    void setref(UIelement* ref = NULL){
        UICommand::setref(ref);
        cmd.setref(ref);
    }
    void setInputer(TextInputHandler& inputH){
        cmd.setInputer(inputH);
    }
    void setInputer(TextInputHandler* inputH = NULL){
        cmd.setInputer(inputH);
    }
    inline TextInputHandler* getInputer() const {
        return cmd.getInputer();
    }
    inline bool iswriting(){
        return cmd.iswriting();
    }
    inline bool iswritingON(){
        return cmd.iswritingON();
    }
    inline void stopwriting(){
        cmd.stopwriting();
    }
    void checktext(){
        if(!iswritingON()){
            setStrRef(NULL);
            return;
        }
        if(!iswriting()){
            // cout << " quitcase\n";
            setStrRef(NULL);
            stopwriting();
            return;
        }
        if(!cmd.getStrRef())setStrRef(UICommand::getref()->getText());
        cmd.execute();
    }
    inline void setwriting(bool write){
        cmd.setwriting(write);
    }
    inline void setStrRef(string* textto = NULL){
        cmd.setStrRef(textto);
    }
    inline void setStrRef(string& textto){
        cmd.setStrRef(textto);
    }
    void execute() override{
        // cout << " exec inbox\n";
        if(!UICommand::ref){
            //cout << " cmd error no ref\n";
            return;
        }
        cmd.execute();
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
        multref.push((new InputStringUIcmd(NULL, this)));
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
        static InputStringUIcmd& inputSetter = *static_cast<InputStringUIcmd*>(multref.getcmd(0));
        //static ChangeStringCmd<UIelement>* inputSetter = reinterpret_cast<ChangeStringCmd<UIelement>*>(multcom.getcmd(0));
        inputSetter.setInputer(inputT);
        string thetext = getText();
        inputSetter.setStrRef(thetext);
        //cout << " checking click\n";
        //if(UIcmds.click == NULL)cout << " click okay\n";;
        Label::update(input);
        inputSetter.checktext();
        settext(thetext);
        //if(!isfocus && input.isMouseReady(SDL_BUTTON_LEFT) || input.isMouseReady(SDL_BUTTON_RIGHT))inputSetter.setwriting(false);
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
    protected:
    int setpath(const string& imgpath){
        if(path == imgpath){
            return 0;
        }
        if(imgpath == ""){
            path.clear();
            return -1;
        }
        path = imgpath;
        return 1;
    }
    int setpath(const char* imgpath = NULL){
        if(!imgpath){
            path.clear();
            return -1;
        }
        if(path == imgpath){
            return 0;
        }
        path = imgpath;
        return 1;
    }
    void resize(){
        if(Box.w > 320)Box.w /= 4;
        if(Box.h > 300)Box.h /= 4;
    }
    SDL_Rect Box;
    FONT font;
    SDL_Color fg, bg;
    string imgname;
    string path, pathholder;
    public:
    void givepath(const char* thepath = NULL){
        pathholder = thepath;
    }
    void givepath(const string& thepath){
        pathholder = thepath;
    }
    virtual void setPos(int x, int y) override {
        Box.x = x;
        Box.y = y;
    }
    virtual void setCol1(const SDL_Color& col) override {
        fg = col;
        return;
    }
    virtual void setCol2(const SDL_Color& col) override {
        bg = col;
        return;
    }
    virtual void setFont(const FONT& font_) override{ 
        font = font_;
        return;
    }
    virtual SDL_Rect* getBox() override{
        return &Box;    
    } 
    virtual FONT* getFont() override{
        return &font;
    }
    virtual SDL_Color* getCol1() override {
        return &fg;   
    }
    virtual SDL_Color* getCol2() override {
        return &bg;
    }
    virtual void render(SDL_Renderer* rend, SDL_Texture*& texture, int drawtype = 2) override {
        int type = checkText(loadImgPath(rend, texture, pathholder.c_str()));
        switch (type){
            case -1:
            {
                if(texture){
                    SDL_DestroyTexture(texture);
                    texture = NULL;
                }
                setBoxDim(50, 50);
                setRenCol(rend, bg);
                SDL_RenderFillRect(rend, &Box);
                setRenCol(rend, fg);
                TEXTURE::drawRect(Box, rend);
                break;
            }
            case -2:
            {
                if(texture)SDL_DestroyTexture(texture);
                SDL_Surface* surf = renderText(font.getfont(), "<img>", fg, bg, 1);
                texture = SDL_CreateTextureFromSurface(rend, surf);
                SDL_FreeSurface(surf);
                setquery(texture);
                resize();
                SDL_Rect newBox = {Box.x - (font.getptsize() / 5), Box.y - (font.getptsize() / 5), Box.w + ((font.getptsize() / 5) * 2), Box.h + ((font.getptsize() / 5) * 2)};
                setRenCol(rend, bg);
                SDL_RenderFillRect(rend, &newBox);
                setRenCol(rend, fg);
                TEXTURE::drawRect(newBox, rend, font.getptsize() / 5);
                if(!texture)uilog << " no texture to draw to\n";
                if(SDL_RenderCopy(rend, texture, NULL, &Box))uilog << " rendering error occured\n";
                break;
            }
            case 0:
            {
                uilog << " redraw\n";
                resize();
                SDL_Rect newBox = {Box.x - drawtype / 2, Box.y - drawtype / 2, Box.w + drawtype, Box.h + drawtype};
                setRenCol(rend, bg);
                SDL_RenderFillRect(rend, &newBox);
                setRenCol(rend, fg);
                TEXTURE::drawRect(newBox, rend, drawtype);
                if(!texture)uilog << " no texture to draw to\n";
                if(SDL_RenderCopy(rend, texture, NULL, &Box) < 0)uilog << " rendering error occured" << SDL_GetError() << endl;
                break;
            }
            case 1:
            {
                uilog << " reload redraw\n";
                // cout << " case reload\n";
                resize();
                SDL_Rect newBox = {Box.x - drawtype / 2, Box.y - drawtype / 2, Box.w + drawtype, Box.h + drawtype};
                setRenCol(rend, bg);
                SDL_RenderFillRect(rend, &newBox);
                setRenCol(rend, fg);
                TEXTURE::drawRect(newBox, rend, drawtype);
                if(!texture)uilog << " no texture to draw to\n";
                if(SDL_RenderCopy(rend, texture, NULL, &Box) < 0)uilog << " rendering error occured" << SDL_GetError() << endl;
                break;
            }
            default:
            {
                if(texture)SDL_DestroyTexture(texture);
                SDL_Surface* surf = renderText(font.getfont(), imgname.c_str(), fg, bg, 3);
                texture = SDL_CreateTextureFromSurface(rend, surf);
                SDL_FreeSurface(surf);
                setquery(texture);
                resize();
                SDL_Rect newBox = {Box.x - (font.getptsize() / 5), Box.y - (font.getptsize() / 5), Box.w + ((font.getptsize() / 5) * 2), Box.h + ((font.getptsize() / 5) * 2)};
                setRenCol(rend, fg);
                TEXTURE::drawRect(newBox, rend, font.getptsize() / 5);
                Box.w = newBox.w;
                Box.h = newBox.h;
                if(!texture)uilog << " no texture to draw to\n";
                if(SDL_RenderCopy(rend, texture, NULL, &Box) < 0)uilog << " rendering error occured" << SDL_GetError() << endl;
                break;
            }
        }
    } 
    //
    void settext(const string& text) override { 
        imgname = text;
    }
    string& getText() override {
        return imgname;
    }
    void update(InputManager& input){
        UIelement::update(input);
    }
    // important imps
    int loadImgPath(SDL_Renderer* rend, SDL_Texture* imgtexture, const char* fpath = NULL){
        uilog << " ImageViewer: Image loading: " << (fpath ? fpath : "NULL") << " > ";
        int ret = setpath(fpath);
        if(ret == -1){
            uilog << " path cleared\n";
            return 0;
        }
        else if(ret > 0 || !imgtexture){
            if(imgtexture)SDL_DestroyTexture(imgtexture);
            imgtexture = IMG_LoadTexture(rend, path.c_str());
            if(!imgtexture){
                uilog << "failed: " << SDL_GetError() << endl;
                path.clear();
                return -1;
            }
        }
        else{
            uilog << " denied (same image)\n";
            return -2;
        }
        uilog << " loaded\n"; 
        setquery(imgtexture);
        return 1;
    }
    inline int loadImg(SDL_Renderer* rend, SDL_Texture* imgtexture){
        return loadImgPath(rend, imgtexture, path.c_str());
    }
    void setquery(SDL_Texture* imgtexture){
        uilog << " setting query\n";
        if(path.empty() && !imgtexture){
            uilog << " ImageViewer: no image loaded\n";
            return;
        }
        if(!SDL_QueryTexture(imgtexture, NULL, NULL, &Box.w, &Box.h)){
            uilog << " ImageViewer: image loaded successfully\n";
        }
        else{
            uilog << " ImageViewer: error loading image: " << SDL_GetError() << "\n";
        }
    }
    inline string& getpathref(){
        return path;
    }
    inline const char* getpath() const {
        return path.c_str();
    }
    inline const char* getname() const {
        return imgname.c_str();
    }
    inline void setBox(const SDL_Rect& SBox){
        Box = SBox;
    }
    inline void setBoxDimP(const SDL_Point& point){
        Box.w = point.x;
        Box.h = point.y;
    }
    inline void setBoxDim(int w, int h){
        Box.w = w;
        Box.h = h;
    }
    int checkText(int ret){
        uilog << " ImageViewer: checking Image for text label option\n";
        if(ret == 1){
            uilog << " image recreated\n";
            return 1;
        }
        if(ret == -1 || ret == 0){
            uilog << " no image loaded, showing text\n";
        }
        else if(ret == -2){
            uilog << " ImageViewer: path exists: is an image\n";
            return 0;
        }
        //
        if(!font.checkfont()){
            uilog << " ImageViewer: Font not initalized\n";
            return -1;
        }
        if(!imgname.empty()){
            uilog << " ImageViewer: font loading on texture\n";
            return 2;
        }
        else{
            uilog << " ImageViewer: image name empty\n";
            return -2;
        }
    }
    //
    ImageViewer(): UIelement(), Box(SDL_Rect{0, 0, 0, 0}), 
    font(FONT()), fg(SDL_Color{0, 0, 0, 255}), bg(SDL_Color{255, 255, 255, 255}), imgname(""), path(""), pathholder("") {
        checkfile();
        uilog << " created ImageViewer\n";
    }
    ImageViewer(const char* fpath): ImageViewer() {
        setpath(fpath);
    }
    ImageViewer(const SDL_Rect& box): ImageViewer() {
        Box = box;
    }
    //
    ~ImageViewer(){
        
    }
};
class MiniMap : public UIelement{

};
/*
🔹 8. Windows and Dialogs
*/
/*
🔹 9. Advanced (for scriptable apps/editors)
*/