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
    virtual void render(SDL_Renderer*, int) = 0; // Pure virtual function for rendering the UI element
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
    void render(SDL_Renderer* renderer, int drawtype = 2) override {
        checkfile();
        uilog << " Rendering UIelements:\n";
        for (UIelement* ui : UIlist) {
            ui->render(renderer, drawtype);
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
        cout << " setting UIContainer pos:\n";
        box.x = x;
        box.y = y;
        int size = UIlist.size();
        if(!size){
            cout << " Empty container\n";
            return;
        }
        cout << " pos0 " << x << " , " << y << endl;
        UIlist[0]->setPos(x, y);
        for(int i = 1; i < size; i++){
            int yp = UIlist[i - 1]->getBox()->h + UIlist[i - 1]->getBox()->y;
            cout << " pos " << i << " " << x << " , " << yp << endl;
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
    Label(const UIcmdset& cmd = UIcmdset{NULL, NULL, NULL})
        : UIelement(cmd), fg(SDL_Color({0, 0, 0, 255})), bg(SDL_Color({255, 255, 255, 255})),
        text(""), box(SDL_Rect({0, 0, 0, 0})), font(FONT()), texture(NULL){}
    Label(const char* str): Label(){
        settext(str);
    }
    Label(int x, int y): Label(){
        setPos(x, y);
    }
    Label(const FONT& font): Label(){
        setFont(font);
    }
    inline void setPos(int x, int y){
        box.x = x;
        box.y = y;
    }
    inline void setFont(const FONT& newfont){
        // cout <<" setting label font\n";
        font = newfont;
    }
    inline void setCol1(const SDL_Color& col){
        fg = col;
    }
    inline void setCol2(const SDL_Color& col){
        bg = col;
    }
    void setquery(){
        if(!texture){
            uilog << " query failed (no texture)\n";
            return;
        }
        if(SDL_QueryTexture(texture, NULL, NULL, &box.w, &box.h) < 0){
            uilog << " query failed (" << SDL_GetError() << ")\n";
            return;
        }
    }
    inline void delTex(){
        if(texture){
            SDL_DestroyTexture(texture);
            texture = NULL;
        }
    }
    inline void settext(const char* str = NULL){
        if(str == NULL){
            text.clear();
            delTex();
            return;
        }
        if(text == str){
            return;
        }
        text = str;
        delTex();
    }
    inline void settext(const string& str) override {
        if(text == str){
            return;
        }
        text = str;
        delTex();
    }
    void render(SDL_Renderer* renderer, int drawtype = 2) override {
        checkfile();
        uilog << " Rendering label: \n";
        if(!texture){
            if(!font.getfont()){
                box.w = 50;
                box.h = 50;
                setRenCol(renderer, bg);
                SDL_RenderDrawRect(renderer, &box);
                setRenCol(renderer, fg);
                TEXTURE::drawRect(box, renderer, drawtype / 2);
                return;
            }
            else if(!text.empty()){
                SDL_Surface* surf = renderText(font.getfont(), text.c_str(), fg, bg, drawtype);
                texture = SDL_CreateTextureFromSurface(renderer, surf);
                SDL_FreeSurface(surf);
                setquery();
            }
            else{
                SDL_Surface* surf = renderText(font.getfont(), "<label>", fg, bg, drawtype);
                texture = SDL_CreateTextureFromSurface(renderer, surf);
                SDL_FreeSurface(surf);
                setquery();
            }
        }
        SDL_RenderCopy(renderer, texture, NULL, &box);
        // Render the label text using the provided renderer
    }
    string& getText(){
        return text;
    }
    const char* gettext(){
        return text.c_str();
    }
    string& gettextRef(){
        return text;
    }
    FONT* getFont() {
        return &font;
    }
    SDL_Color* getCol1() {
        return &fg;
    }
    SDL_Color* getCol2() {
        return &bg;
    }
    SDL_Rect* getBox(){
        return &box;
    }
    protected:
    SDL_Rect box; // box model
    string text;
    FONT font;
    SDL_Color fg, bg;
    SDL_Texture* texture;
};

class InputBox : public Label{
    multiCommand<UIelement>& multref;
    SDL_Point dims;
public:
    InputBox() : Label(UIcmdset({NULL, new multiCommand<UIelement>(this), NULL})), 
    multref(*static_cast<multiCommand<UIelement>*>(UIcmds.click)), dims(SDL_Point({0, 0})){
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
    inline void setdims(int x, int y){
        dims.x = x;
        dims.y = y;
    }
    inline void onClick(UICommand* cmd = NULL) override {
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
    void render(SDL_Renderer* renderer, int drawtype = 2) override {
        checkfile();
        uilog << " Rendering InputBox: \n";
        if(!texture){
            if(!font.getfont()){
                box.w = dims.x;
                box.h = dims.y;
                setRenCol(renderer, bg);
                SDL_RenderDrawRect(renderer, &box);
                setRenCol(renderer, fg);
                TEXTURE::drawRect(box, renderer, drawtype / 2);
                return;
            }
            else if(!text.empty()){
                
                SDL_Surface* surf = renderText(font.getfont(), text.c_str(), fg, bg, drawtype);
                texture = SDL_CreateTextureFromSurface(renderer, surf);
                SDL_FreeSurface(surf);
                setquery();
            }
            else{
                SDL_Surface* surf = renderText(font.getfont(), "<InputBox>", fg, bg, drawtype);
                texture = SDL_CreateTextureFromSurface(renderer, surf);
                SDL_FreeSurface(surf);
                setquery();
            }
        }
        SDL_RenderCopy(renderer, texture, NULL, &box);
        setRenCol(renderer, bg);
        SDL_RenderDrawRect(renderer, &box);
        setRenCol(renderer, fg);
        TEXTURE::drawRect(box, renderer, drawtype / 2);
        // Render the label text using the provided renderer
    }
    const SDL_Point& getDims() const {
        return dims;
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
    void render(SDL_Renderer* rend, int drawt = 2) override {
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
    /*
    * sets path:
    * returns: -1 on clear, 0 on duplicate, 1 on success
    */ 
    virtual int setpath(const string& imgpath){
        if(path == imgpath){
            return 0;
        }
        if(imgpath == ""){
            path.clear();
            delTex();
            return -1;
        }
        path = imgpath;
        delTex();
        return 1;
    }
    /*
    * sets path:
    * returns: -1 on clear, 0 on duplicate, 1 on success
    */ 
    virtual int setpath(const char* imgpath = NULL){
        if(!imgpath){
            path.clear();
            delTex();
            return -1;
        }
        if(path == imgpath){
            return 0;
        }
        path = imgpath;
        delTex();
        return 1;
    }
    void resize(){
        if(box.w > 320)box.w /= 4;
        if(box.h > 300)box.h /= 4;
    }
    inline void delTex(){
        if(texture){
            SDL_DestroyTexture(texture);
            texture = NULL;
        }
    }
    SDL_Rect box;
    FONT font;
    SDL_Color fg, bg;
    string imgname;
    string path;
    SDL_Texture* texture;
    public:
    virtual void setPos(int x, int y) override {
        box.x = x;
        box.y = y;
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
        return &box;    
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
    virtual void render(SDL_Renderer* rend, int drawtype = 2) override {
        if(!texture){
            int type = loadImg(rend);
            if(type < 0){
                if(!font.getfont()){
                    box.w = box.h = 50;
                    setRenCol(rend, bg);
                    SDL_RenderFillRect(rend, &box);
                    setRenCol(rend, fg);
                    TEXTURE::drawRect(box, rend);
                    return;
                }
                else if(!imgname.empty()){
                    SDL_Surface* surf = renderText(font.getfont(), imgname.c_str(), fg, bg, 3);
                    texture = SDL_CreateTextureFromSurface(rend, surf);
                    SDL_FreeSurface(surf);
                    setquery();
                    resize();
                    SDL_Rect newBox = {box.x - (font.getptsize() / 5), box.y - (font.getptsize() / 5), 
                        box.w + ((font.getptsize() / 5) * 2), box.h + ((font.getptsize() / 5) * 2)};
                    setRenCol(rend, fg);
                    TEXTURE::drawRect(newBox, rend, font.getptsize() / 5);
                    box.w = newBox.w;
                    box.h = newBox.h;
                    if(!texture)uilog << " no texture to draw to\n";
                }
                else{
                    SDL_Surface* surf = renderText(font.getfont(), "<img>", fg, bg, 1);
                    texture = SDL_CreateTextureFromSurface(rend, surf);
                    SDL_FreeSurface(surf);
                    setquery();
                    resize();
                    SDL_Rect newBox = {box.x - (font.getptsize() / 5), box.y - (font.getptsize() / 5), 
                        box.w + ((font.getptsize() / 5) * 2), box.h + ((font.getptsize() / 5) * 2)};
                    setRenCol(rend, bg);
                    SDL_RenderFillRect(rend, &newBox);
                    setRenCol(rend, fg);
                    TEXTURE::drawRect(newBox, rend, font.getptsize() / 5);
                    if(!texture)uilog << " no texture to draw to\n";
                    
                }
            }
            else{
                setquery();
                resize();
            }
        }
        if(SDL_RenderCopy(rend, texture, NULL, &box))uilog << " rendering error occured\n";
        // 
    } 
    //
    void settext(const string& text) override { 
        imgname = text;
    }
    string& getText() override {
        return imgname;
    }
    // important imps
    int loadImgPath(SDL_Renderer* rend, const char* fpath = NULL){
        uilog << " ImageViewer: Image loading: " << (fpath ? fpath : "NULL") << " > ";
        int ret = setpath(fpath);
        if(ret == -1){
            uilog << " path cleared\n";
            return -1;
        }
        else if(ret > 0 || !texture){
            if(texture)SDL_DestroyTexture(texture);
            texture = IMG_LoadTexture(rend, path.c_str());
            if(!texture){
                uilog << "failed: " << SDL_GetError() << endl;
                path.clear();
                return -2;
            }
        }
        else{
            uilog << " denied (same image)\n";
            return 0;
        }
        uilog << " loaded\n"; 
        return 1;
    }
    inline int loadImg(SDL_Renderer* rend){
        uilog << " ImageViewer: Image loading (from path): " << (!path.empty() ? path : "NULL") << " > ";
        if(path.empty()){
            delTex();
            uilog << " path cleared\n";
            return -1;
        }
        else if(!texture){
            texture = IMG_LoadTexture(rend, path.c_str());
            if(!texture){
                uilog << "failed: " << SDL_GetError() << endl;
                path.clear();
                return -2;
            }
        }
        else{
            uilog << " denied (has image)\n";
            return 0;
        }
        uilog << " loaded\n";
        return 1;
    }
    void setquery(){
        uilog << " ImageViewer: setting query >";
        if(!texture){
            uilog << " ERR: no image loaded\n";
            return;
        }
        if(SDL_QueryTexture(texture, NULL, NULL, &box.w, &box.h) == 0){
            uilog << " image queried successfully\n";
        }
        else{
            uilog << " ERR: error quering image: " << SDL_GetError() << "\n";
        }
    }
    inline const char* getpath() const {
        return path.c_str();
    }
    inline const char* getname() const {
        return imgname.c_str();
    }
    inline void setBox(const SDL_Rect& SBox){
        box = SBox;
    }
    inline void setBoxDimP(const SDL_Point& point){
        box.w = point.x;
        box.h = point.y;
    }
    inline void setBoxDim(int w, int h){
        box.w = w;
        box.h = h;
    }
    //
    ImageViewer(): UIelement(), box(SDL_Rect{0, 0, 0, 0}), 
    font(FONT()), fg(SDL_Color{0, 0, 0, 255}), bg(SDL_Color{255, 255, 255, 255}), imgname(""), path(""), texture(NULL) {
        checkfile();
        uilog << " created ImageViewer\n";
    }
    ImageViewer(const char* fpath): ImageViewer() {
        setpath(fpath);
    }
    ImageViewer(const SDL_Rect& tbox): ImageViewer() {
        box = tbox;
    }
    //
    ~ImageViewer(){
        
    }
};
class ImageUI : public ImageViewer{
    protected:
    string pathholder;
    int setpath(const string& fpath) override{
        int ret = ImageViewer::setpath(fpath); 
        if(ret != 0){
            pathholder = path;
        }
    }
    int setpath(const char* fpath) override {
        int ret = ImageViewer::setpath(fpath); 
        if(ret != 0){
            pathholder = path;
        }
    }
    public:
    void update(InputManager& input){
        ImageViewer::update(input);
        setpath(pathholder);
    }
    ImageUI(): ImageViewer(), pathholder(""){}
    ImageUI(const char* fpath): ImageViewer(fpath), pathholder(fpath){}
    ImageUI(const SDL_Rect& tbox): ImageViewer(tbox), pathholder("") {}
};
class MiniMap : public UIelement{

};
/*
🔹 8. Windows and Dialogs
*/
/*
🔹 9. Advanced (for scriptable apps/editors)
*/