class UIelement
{
public:
    UIelement(){}
    UIelement(const UIelement& ui){
        *this = ui;
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
    virtual bool onFocus(const SDL_Point&, command<UIelement>&) = 0;
    virtual bool onClick(const SDL_Point&, bool, command<UIelement>&) = 0;
    virtual bool onHover(const SDL_Point&, command<UIelement>&) = 0;
    virtual void setPos(int, int) = 0;
    virtual void setCol1(const SDL_Color&) = 0;
    virtual void setCol2(const SDL_Color&) = 0;
    virtual void setFont(const FONT&) = 0;
    virtual SDL_Rect* getBox() = 0;
    virtual FONT* getFont() = 0;
    virtual SDL_Color* getCol1() = 0;
    virtual SDL_Color* getCol2() = 0;
    virtual void render(SDL_Renderer*, SDL_Texture*&, int) = 0; // Pure virtual function for rendering the UI element
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
class Label : public UIelement {
    public:
    Label(): labelText(){}
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
        labelText.draw(renderer, board, drawtype);
        // Render the label text using the provided renderer
    }
    bool isHovered(const SDL_Point& point) const {
        // Check if the point is within the label's bounding box
        const SDL_Rect& box = labelText.getBoxc();
        return SDL_PointInRect(&point, &box);
    }
    bool isCurrent(){
        return false;
    }
    bool isFocus(const SDL_Point& point){
        return isHovered(point) || isCurrent();
    }
    bool isClicked(const SDL_Point& point, bool click){
        // Check if the label is clicked based on the mouse position
        return isFocus(point) && click;
    }
    void revert(UICommand& cmd){
        if(cmd.getref() != this)cmd.setref(*this);
        cmd.execute();
    }
    bool onHover(const SDL_Point& point, UICommand& cmd){
        if(isHovered(point)){
            if(cmd.getref() != this)cmd.setref(*this);
            cmd.execute();
            return true;
        }
        return false;
    }
    bool onClick(const SDL_Point& point, bool click, UICommand& cmd){
        if(isClicked(point, click)){
            if(cmd.getref() != this)cmd.setref(*this);
            cmd.execute();
            return true;
        }
        return false;
    }
    bool onFocus(const SDL_Point& point, UICommand& cmd){
        if(isFocus(point)){
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
class UIContainer : public UIelement{
    vector<UIelement*> UIlist;
    public:
    UIContainer(){}
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
        vector<UIelement*>& List = UIlist;
        for(UIelement* ui : List){
            ui->setFont(font);
        }
    }
    void setCol1(const SDL_Color& col){
        if(!UIlist.size())return;
        // cout << " setting all fcolors\n";
        vector<UIelement*>& List = UIlist;
        for(UIelement* ui : List){
            ui->setCol1(col);
        }
    }
    void setCol2(const SDL_Color& col){
        if(!UIlist.size())return;
        // cout << " setting all fcolors\n";
        vector<UIelement*>& List = UIlist;
        for(UIelement* ui : List){
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
    bool onFocus(const SDL_Point& point, UICommand& command){
        return false;
    }
    bool onClick(const SDL_Point& point, bool click, UICommand& command){
        return false;
    }
    bool onHover(const SDL_Point& point, UICommand& command){
        return false;
    }
};