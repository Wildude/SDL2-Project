#include <GUI.hpp>
#include <command.hpp>
#include <renderer.hpp>
#include <fstream>
#include <vector>
#include <SDL2_gfx/SDL2_gfxPrimitives.h>
std::ofstream uilog("../Files/Data/GUI.log");
// UIelement
// abstract imps
//virtual void setPos(int, int) = 0;
//virtual void setCol1(const SDL_Color&) = 0;
//virtual void setCol2(const SDL_Color&) = 0;
//virtual void setFont(const FONT&) = 0;
//virtual SDL_Rect* getBox() = 0;
//virtual FONT* getFont() = 0;
//virtual SDL_Color* getCol1() = 0;
//virtual SDL_Color* getCol2() = 0;
//virtual void render(SDL_Renderer*, int) = 0; // Pure virtual function for rendering the UI element
// repeated imps
/* virtual */ bool UIelement::focusCheck(const InputManager& input){
    return isHovered(input) || isCurrent(input);
}
/* virtual*/ bool UIelement::isFocused(InputManager& input){
    isfocus = isHovered(input) || isCurrent(input);
    return isfocus;
}
/* virtual*/ bool UIelement::isClicked(InputManager& input){
    isclick = isHovered(input) && input.isMousePressed(SDL_BUTTON_LEFT);
    return isclick;
}
/* virtual*/ bool UIelement::isCurrent(const InputManager& input) {
    return false;
}
/* virtual*/ void UIelement::update(InputManager& input){
    isClicked(input);
    if(isclick){
        isrevert = false;
        if(UIcmds.click){
            system("cls");
            std::cout << " click executing\n";
            std::cout << " switching from pointer " << UIcmds.click->getref() << " to " << this << "\n";
            if(UIcmds.click->getref() != this)UIcmds.click->setref(this);
            UIcmds.click->execute();
            statechanged = true;
        }
    }
    else if(focusCheck(input))
    {
        isrevert = false;
        
        if(!isfocus){
            system("cls");
            std::cout << " focusing\n";
            isfocus = true;
            if(UIcmds.focus){
                std::cout << " switching from pointer " << UIcmds.focus->getref() << " to " << this << "\n";
                if(UIcmds.focus->getref() != this)UIcmds.focus->setref(this);
                UIcmds.focus->execute();
                statechanged = true;
            }
        }
        else statechanged = false;
    }
    else {
        if(!isrevert){
            system("cls");
            std::cout << " reverting\n";
            isfocus = false;
            isrevert = true;
            std::cout << " switching from pointer " << UIcmds.revert->getref() << " to " << this << "\n";
            if(UIcmds.revert){
                if(UIcmds.revert->getref() != this)UIcmds.revert->setref(this);
                UIcmds.revert->execute();
                statechanged = true;
            }
        }
        else statechanged = false;
    }
};
/* virtual*/ void UIelement::onFocus(UICommand* focus ){
    UIcmds.focus = focus;
    if(focus){
        //std::cout << " setting focus command reference\n";
        //focus->setref(this);
    }
}
/* virtual*/ void UIelement::onClick(UICommand* click ){
    UIcmds.click = click;
    if(click){
        //std::cout << " setting click command reference\n";
        //click->setref(this);
    }
}
/* virtual*/ void UIelement::onRevert(UICommand* revert ){
    UIcmds.revert = revert;
    if(revert){
        //std::cout << " setting revert command reference\n";
        //revert->setref(this);
    }
}
void UIelement::clearCMD(){
    UIcmds.focus = NULL;
    UIcmds.click = NULL;
    UIcmds.revert = NULL;
}
/* virtual*/ bool UIelement::isHovered(const InputManager& input){
    const SDL_Point& mpos = input.getMouseP();
    const SDL_Rect& mbox = *getBox();
    ishover = SDL_PointInRect(&mpos, &mbox);
    return ishover;
}
// meaningless imps
/* virtual*/ void UIelement::settext(const std::string& text){}
/* virtual*/ std::string& UIelement::getText() {}
// important imps
bool UIelement::gethover() const {
    return ishover;
}
bool UIelement::getfocus() const {
    return isfocus;
}
bool UIelement::getclick() const {
    return isclick;
}
bool UIelement::getrevert() const {
    return isrevert;
}
bool UIelement::getstateChanged() const {
    return statechanged;
}
UICommand* UIelement::getFocusCmd() const {
    return UIcmds.focus;
}
UICommand* UIelement::getClickCmd() const {
    return UIcmds.click;
}
UICommand* UIelement::getRevertCmd() const{
    return UIcmds.revert;
}
// constructors and such
UIelement::UIelement(const UIcmdset& cmd, 
    bool focus , bool hover , bool click , bool revert ) 
    : UIcmds(cmd), isfocus(focus), ishover(hover), isclick(click), isrevert(revert){
    checkfile();
    uilog << " created UIelement\n";
}
UIelement::UIelement(const UIelement& ui): UIelement(){
    *this = ui;
}
UIelement& UIelement::operator=(const UIelement& ui) {
    if (this != &ui) {
        UIcmds = ui.UIcmds;
        isfocus = ui.isfocus;
        isrevert = ui.isrevert;
        isclick = ui.isclick;
        ishover = ui.ishover;
    }
    return *this;
}
/* inline*/ void UIelement::checkfile(){
    if(!uilog.is_open()){
        uilog.open("../Files/Data/GUI.log", std::ios::app);
    }
}
UIelement::~UIelement() {
    uilog << " destroying UIelement\n";
    uilog.close();
    // Destructor implementation
    // Clean up any resources if needed
}

//
//typedef command<UIelement> UICommand;
// UIMultiCommand
UIMultiCommand::UIMultiCommand(UIelement* ref) : UICommand(ref){}
UIMultiCommand::UIMultiCommand(std::vector<UICommand*>& cmds): UIMultiCommand(){
    commands = cmds;
}
void UIMultiCommand::setref(UIelement& ref) /* override */ {
    //std::cout << " setting UIMultiCommand reference\n";
    UICommand::setref(ref);
    int size = commands.size();
    for(int i = 0; i < size; i++){
        commands[i]->setref(ref);
    }
}
void UIMultiCommand::push(UICommand& cmd){
    push(&cmd);
}
void UIMultiCommand::push(UICommand* cmd){
    //std::cout << " pushing command\n";
    commands.push_back(cmd);
}
UICommand*& UIMultiCommand::getcmd(int index ){
    return commands[index];
}
UIMultiCommand* UIMultiCommand::clone() const /* override */ {
    return new UIMultiCommand(*this);
}
UIMultiCommand::~UIMultiCommand(){
    commands.clear();
}
void UIMultiCommand::execute() /* override */ {
    //std::cout << " executing multicommand\n";
    if(!UICommand::ref){
            // std::cout << " no reference\n";
        return;
    }
    int size = commands.size();
    if(!size){
            // std::cout << " no executions\n";
        return;
    }
    for(int i = 0; i < size; i++){
        // std::cout << " executing cmd " << i << endl;
        commands[i]->setref(*UICommand::ref);
        commands[i]->execute();
    }
}
//
// UIColor
UIColor::UIColor(): UICommand() , cmd(){}
UIColor::UIColor(UIelement& uref) : UICommand(uref), cmd(*ref->getCol2(), *ref->getCol1()){}
UIColor::UIColor(const SDL_Color& nbg, const SDL_Color& nfg): UICommand(), cmd(nbg, nfg){}
void UIColor::setNew(const SDL_Color& bnew, const SDL_Color& fnew){
    //std::cout << " setting UI color news\n";
    cmd.setNew(bnew, fnew);
}
void UIColor::setref(UIelement& tref) /* override */ {
    std::cout << " setting UI color references\n";
    UICommand::setref(tref);
    cmd.setRef(ref->getCol2(), ref->getCol1());
}
UIColor* UIColor::clone() const /* override */ {
    return new UIColor(*this);
}

void UIColor::execute() /* override */{
    //std::cout << " executing UI color\n";
    // important to check color references in case they weren't set
    if(!cmd.bg || !cmd.fg){
        //std::cout << " references reset\n";
        cmd.setRef(ref->getCol2(), ref->getCol1());
    }
    if(!ref){
        //std::cout << " no UI reference\n";
        return;
    }
    cmd.execute();
}
UIColor::~UIColor(){}
// UIFont
UIFont::UIFont(): UICommand(), cmd(){}
UIFont::UIFont(UIelement& uref) : UICommand(uref), cmd(*ref->getFont()){}
UIFont::UIFont(const FONT& font): UICommand(), cmd(font){}
void UIFont::setNew(const FONT& font){
    //std::cout << " setting UI Font news\n";
    cmd.newFont = font;
}
void UIFont::setref(UIelement& tref){
    //std::cout << " setting UI Font references\n";
    ref = &tref;
    cmd.setRef(ref->getFont());
}
const UIelement* UIFont::getref() const /* override */ {
    //std::cout << " UI font change get ref called\n";
    return UICommand::getref();
}
void UIFont::execute(){
    //std::cout << " executing UI font\n";
    // important to check font reference in case it wasn't set
    if(!cmd.fontRef){
        //std::cout << " reference reset\n";
        cmd.setRef(ref->getFont());
    }
    if(!ref){
        //std::cout << " no UI reference\n";
        return;
    }
    cmd.execute();
}
UIFont* UIFont::clone() const /* override */ {
    return new UIFont(*this);
}
//
// UIContainer
UIContainer::UIContainer(): box(SDL_Rect{0, 0, 0, 0}), UIelement(){
}
int UIContainer::getsize(){
    return UIlist.size();
}
void UIContainer::setBoxW(int width){
    box.w = width;
}
void UIContainer::setBoxH(int height){
    box.h = height;
}
std::vector<UIelement*>& UIContainer::getList(){
    return UIlist;
}
const UIContainer& UIContainer::operator=(const std::vector<UIelement*>& UIC){
    if(&this->UIlist != &UIC){
        UIlist = UIC;
    }
    return *this;
}
const UIContainer& UIContainer::operator=(const UIContainer& UIC){
    if(this != &UIC){
        UIlist = UIC.UIlist;
    }
    return *this;
}
void UIContainer::update(InputManager& input) /* override */ {
    for(int i = 0; i < UIlist.size(); i++){
        UIcmds.click->setref(UIlist[i]);
        UIcmds.focus->setref(UIlist[i]);
        UIcmds.revert->setref(UIlist[i]);
        UIlist[i]->update(input);
    }
}
UIContainer::UIContainer(std::vector<UIelement*>& UIs): UIContainer(){
    for (UIelement* UI : UIs){
        UIlist.push_back(UI);
    }
    setPos(box.x, box.y);
    setbox();
}
void UIContainer::push(UIelement& ui){
    push(&ui);
}
void UIContainer::push(UIelement* ui){
    UIlist.push_back(ui);
    setPos(box.x, box.y);
    setbox();
}
void UIContainer::render(SDL_Renderer* renderer, int drawtype ) /* override */ {
    setRenCol(renderer, bg);
    SDL_RenderFillRect(renderer, &box);
    setRenCol(renderer, fg);
    Texture2D::drawRect(box, renderer, drawtype / 2);
    checkfile();
    uilog << " Rendering UIelements:\n";
    for (UIelement* ui : UIlist) {
        ui->render(renderer, drawtype);
    }
}
SDL_Color* UIContainer::getCol1(){
    return &fg;
}
SDL_Color* UIContainer::getCol2(){
    return &bg;
}
FONT* UIContainer::getFont(){
    return (UIlist.size() ? UIlist[0]->getFont() : NULL);
}
SDL_Rect* UIContainer::getBox(){
    return &box;
}
void UIContainer::apply(){
    applyFont();
    applyCol1();
    applyCol2();
    setPos(box.x, box.y);
    setbox();
}
void UIContainer::applyFont(){
    int size = UIlist.size();
    if(!size)return;
    for(int i = 1; i < size - 1; i++){
        UIlist[i]->setFont(*UIlist[0]->getFont());
    }
    setPos(box.x, box.y);
    setbox();
}
void UIContainer::applyCol1(){
    int size = UIlist.size();
    if(!size)return;
    for(int i = 1; i < size - 1; i++){
        UIlist[i]->setCol1(*UIlist[0]->getCol1());
    }
}
void UIContainer::applyCol2(){
    int size = UIlist.size();
    if(!size)return;
    for(int i = 1; i < size - 1; i++){
        UIlist[i]->setCol2(*UIlist[0]->getCol2());
    }
}
void UIContainer::setFont(const FONT& font) /* override */ {
    if(!UIlist.size())return;
    // std::cout << " setting all fonts\n";
    for(UIelement* ui : UIlist){
        ui->setFont(font);
    }
    setPos(box.x, box.y);
    setbox();
}
void UIContainer::setCol1(const SDL_Color& col) /* override */ {
    fg = col;
    if(!UIlist.size())return;
    // std::cout << " setting all fcolors\n";
    for(UIelement* ui : UIlist){
        ui->setCol1(col);
    }
}
void UIContainer::setCol2(const SDL_Color& col) /* override */ {
    bg = col;
    if(!UIlist.size())return;
    // std::cout << " setting all fcolors\n";
    for(UIelement* ui : UIlist){
        ui->setCol2(col);
    }
}
void UIContainer::onClick(UICommand* cmd ) /* override */ {
    UIelement::onClick(cmd);
    int size = UIlist.size();
    if(!size)return;
    for(int i = 0; i < size; i++){
        //std::cout << " checking click cmd for element " << i << std::endl;
        if(!UIlist[i]->getClickCmd()){
            //std::cout << " setting click cmd for element " << i << std::endl;   
            UIlist[i]->onClick(cmd->clone());
        }
    }
}
void UIContainer::onFocus(UICommand* cmd ) /* override */ {
    UIelement::onFocus(cmd);
    int size = UIlist.size();
    if(!size)return;
    for(int i = 0; i < size; i++){
        //std::cout << " checking focus cmd for element " << i << std::endl;
        if(!UIlist[i]->getFocusCmd()){
            //std::cout << " setting focus cmd for element " << i << std::endl;
            UIlist[i]->onFocus(cmd->clone());
        }
    }
}
void UIContainer::onRevert(UICommand* cmd ) /* override */ {
    UIelement::onRevert(cmd);
    int size = UIlist.size();
    if(!size)return;
    for(int i = 0; i < size; i++){
        //std::cout << " checking revert cmd for element " << i << std::endl;
        if(!UIlist[i]->getRevertCmd()){
            //std::cout << " setting revert cmd for element " << i << std::endl;
            UIlist[i]->onRevert(cmd->clone());
        }
    }
}
//
/* virtual*/ void UIContainer::setPos(int x, int y) /* override */ {
    uilog << " setting UIContainer pos:\n";
    box.x = x;
    box.y = y;
    int size = UIlist.size();
    if(!size){
        std::cout << " Empty container\n";
        return;
    }
    uilog << " pos0 " << x << " , " << y << std::endl;
    UIlist[0]->setPos(x, y);
    for(int i = 1; i < size; i++){
        int yp = UIlist[i - 1]->getBox()->h + UIlist[i - 1]->getBox()->y;
        uilog << " pos " << i << " " << x << " , " << yp << std::endl;
        UIlist[i]->setPos(x, yp);
    }
}
/* virtual*/ void UIContainer::setbox(){
    uilog << " setting UIContainer box\n";
    box.w = 0;
    box.h = 0;
    for(UIelement* ui : UIlist){
        SDL_Rect* rect = ui->getBox();
        if(rect->w > box.w) box.w = rect->w;
        uilog << " rbox: " << rect->w << ", " << rect->h << std::endl;
        box.h += rect->h;
    }
    uilog << " box: " << box.w << ", " << box.h << std::endl;
}
// UIPanel
void UIPanel::setPos(int x, int y) /* override */ {
    uilog << " setting UIPanel pos:\n";
    box.x = x;
    box.y = y;
    int size = UIlist.size();
    if(!size){
        uilog << " Empty panel\n";
        return;
    }
    uilog << " pos0 " << x << " , " << y << std::endl;
    UIlist[0]->setPos(x, y);
    for(int i = 1; i < size; i++){
        int xp = UIlist[i - 1]->getBox()->w + UIlist[i - 1]->getBox()->x;
        uilog << " pos " << i << " " << xp << " , " << y << std::endl;
        UIlist[i]->setPos(xp, y);
    }
}
void UIPanel::setbox() /* override */ {
    uilog << " setting UIPanel Box\n";
    box.w = 0;
    box.h = 0;
    for(UIelement* ui : UIlist){
        SDL_Rect* rect = ui->getBox();
        if(rect->h > box.h) box.h = rect->h;
        uilog << " rbox: " << rect->w << ", " << rect->h << std::endl;
        box.w += rect->w;
    }
    uilog << " box: " << box.w << ", " << box.h << std::endl;
}
//
/*
🔹 1. Text-Based Components
*/
// ChangeStringUICmd
ChangeStringUICmd::ChangeStringUICmd(UIelement* ref, std::string* textp) : UICommand(ref), cmd(ref, textp){

}
void ChangeStringUICmd::setref(UIelement& ref) /* override */ {
    UICommand::setref(ref);
    cmd.setref(ref);
}
void ChangeStringUICmd::setref(UIelement* ref) /* override */ {
    UICommand::setref(ref);
    cmd.setref(ref);
}
void ChangeStringUICmd::setTextP(std::string* textp ){
    cmd.setStrRef(textp);
}
void ChangeStringUICmd::setNewStr(const std::string& newstr){
    cmd.setNewString(newstr);
}
void ChangeStringUICmd::setNewStr(const char* newstr ){
    cmd.setNewString(newstr);
}
/* virtual*/ void ChangeStringUICmd::execute(){
    if(!ref){
        // std::cout << " cmd error no textTo\n";
        return;
    }
    // std::cout << " executing main command\n";
    cmd.execute();
}
// InputStringUIcmd
InputStringUIcmd::InputStringUIcmd(TextInputHandler* input , UIelement* ref , std::string* textN , 
    SDL_Scancode quitCase ) : command<UIelement>(ref), cmd(input, ref, textN){

}
void InputStringUIcmd::setref(UIelement& ref){
    UICommand::setref(ref);
    cmd.setref(ref);
}
void InputStringUIcmd::setref(UIelement* ref ){
    UICommand::setref(ref);
    cmd.setref(ref);
}
void InputStringUIcmd::setInputer(TextInputHandler& inputH){
    cmd.setInputer(inputH);
}
void InputStringUIcmd::setInputer(TextInputHandler* inputH ){
    cmd.setInputer(inputH);
}
/* inline*/ TextInputHandler* InputStringUIcmd::getInputer() const {
    return cmd.getInputer();
}
/* inline*/ bool InputStringUIcmd::iswriting(){
    return cmd.iswriting();
}
/* inline*/ bool InputStringUIcmd::iswritingON(){
    return cmd.iswritingON();
}
/* inline*/ void InputStringUIcmd::stopwriting(){
    cmd.stopwriting();
}
void InputStringUIcmd::checktext(){
    if(!iswritingON()){
        setStrRef(NULL);
        return;
    }
    if(!iswriting()){
        // std::cout << " quitcase\n";
        setStrRef(NULL);
        stopwriting();
        return;
    }
    if(!cmd.getStrRef())setStrRef(UICommand::getref()->getText());
    cmd.execute();
}
/* inline*/ void InputStringUIcmd::setwriting(bool write){
    cmd.setwriting(write);
}
/* inline*/ void InputStringUIcmd::setStrRef(std::string* textto ){
    cmd.setStrRef(textto);
}
/* inline*/ void InputStringUIcmd::setStrRef(std::string& textto){
    cmd.setStrRef(textto);
}
InputStringUIcmd* InputStringUIcmd::clone() const /* override */ {
    return new InputStringUIcmd(*this);
}
void InputStringUIcmd::execute() /* override */{
    // std::cout << " exec inbox\n";
    if(!UICommand::ref){
        //std::cout << " cmd error no ref\n";
        return;
    }
    cmd.execute();
}
// Label
const Label& Label::operator=(const Label& label) {
    if (this != &label) {
        UIelement::operator=(label);
        fg = label.fg;
        bg = label.bg;
        text = label.text;
        box = label.box;
        font = label.font;
        texture = label.texture;
    }
    return *this;
}
Label::Label(const UIcmdset& cmd , const SDL_Color& fcolor 
    , const SDL_Color& bcolor , const std::string& ttext 
    , const SDL_Rect& rbox , const FONT& ffont , SDL_Texture* tex )
    : UIelement(cmd), fg(fcolor), bg(bcolor), text(ttext), box(rbox), font(ffont), texture(tex) {

    }
Label::Label(const char* str): Label(){
    text = str;
}
Label::Label(int x, int y): Label(){
    setPos(x, y);
}
Label::Label(const FONT& font): Label(){
    setFont(font);
}
/* inline*/ void Label::setPos(int x, int y){
    box.x = x;
    box.y = y;
}
void Label::setFont(const FONT& newfont){
    // std::cout <<" setting label font\n";
    if(font.getfont() == newfont.getfont()){
        return;
    }
    font = newfont;
    if(font.getfont()){
        font.TEXT_size(text.c_str(), &box.w, &box.h);
        delTex();
    }
}
/* inline*/ void Label::setCol1(const SDL_Color& col){
    fg = col;
    delTex();
}
/* inline*/ void Label::setCol2(const SDL_Color& col){
    bg = col;
    delTex();
}
void Label::setquery(){
    if(!texture){
        uilog << " query failed (no texture)\n";
        return;
    }
    if(SDL_QueryTexture(texture, NULL, NULL, &box.w, &box.h) < 0){
        uilog << " query failed (" << SDL_GetError() << ")\n";
        return;
    }
}
/* inline*/ void Label::delTex(){
    if(texture){
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}
void Label::settext(const char* str ){
    if(str == NULL){
        text.clear();
        delTex();
        return;
    }
    if(text == str){
        return;
    }
    text = str;
    if(font.getfont()){
        font.TEXT_size(text.c_str(), &box.w, &box.h);
    }
    delTex();
}
void Label::settext(const std::string& str) /* override */ {
    if(text == str){
        return;
    }
    text = str;
    if(font.getfont()){
        font.TEXT_size(text.c_str(), &box.w, &box.h);
    }
    delTex();
}
/* virtual */ void Label::update(InputManager& input) /* override */ {
    UIelement::update(input);
    if(statechanged){
        //std::cout << " Label state changed, updating texture\n";
        delTex();
    }
    // Additional update logic for the label can be added here
}
/* virtual*/ void Label::render(SDL_Renderer* renderer, int drawtype ) /* override */ {
    checkfile();
    uilog << " Rendering label: \n";
    if(!texture){
        if(!font.getfont()){
            box.w = 50;
            box.h = 50;
            setRenCol(renderer, bg);
            SDL_RenderDrawRect(renderer, &box);
            setRenCol(renderer, fg);
            Texture2D::drawRect(box, renderer, drawtype / 2);
            return;
        }
        else if(!text.empty()){
            SDL_Surface* surf = renderText(font.getfont(), text.c_str(), fg, bg, drawtype / 2);
            texture = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_FreeSurface(surf);
            setquery();
        }
        else{
            SDL_Surface* surf = renderText(font.getfont(), "<label>", fg, bg, drawtype / 2);
            texture = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_FreeSurface(surf);
            setquery();
        }
    }
    SDL_RenderCopy(renderer, texture, NULL, &box);
    // Render the label text using the provided renderer
}
/* virtual*/ /* inline*/ std::string& Label::getText(){
    return text;
}
/* virtual*/ /* inline*/ const char* Label::gettext(){
    return text.c_str();
}
/* virtual*/ /* inline*/ std::string& Label::gettextRef(){
    return text;
}
/* virtual*/ /* inline*/ FONT* Label::getFont() {
    return &font;
}
/* virtual*/ /* inline*/ SDL_Color* Label::getCol1() {
    return &fg;
}
/* virtual*/ /* inline*/ SDL_Color* Label::getCol2() {
    return &bg;
}
/* virtual*/ /* inline*/ SDL_Rect* Label::getBox(){
    return &box;
}
// LabelPanel
LabelPanel::LabelPanel(): box(SDL_Rect{0, 0, 0, 0}), UIelement(){
}
int LabelPanel::getsize(){
    return labelList.size();
}
std::vector<Label>& LabelPanel::getList(){
    return labelList;
}
const LabelPanel& LabelPanel::operator=(const std::vector<Label>& UIC){
    if(&this->labelList != &UIC){
        labelList = UIC;
    }
    return *this;
}
const LabelPanel& LabelPanel::operator=(const LabelPanel& UIC){
    if(this != &UIC){
        labelList = UIC.labelList;
    }
    return *this;
}
void LabelPanel::update(InputManager& input) /* override */ {
    for(Label& ui : labelList)
    ui.update(input);
}
LabelPanel::LabelPanel(std::vector<Label>& UIs): LabelPanel(){
    for (Label& UI : UIs){
        labelList.push_back(UI);
    }
}
void LabelPanel::push(const Label& ui){
    labelList.push_back(ui);
}
void LabelPanel::push(Label* ui){
    labelList.push_back(*ui);
}
void LabelPanel::render(SDL_Renderer* renderer, int drawtype) {
    checkfile();
    uilog << " Rendering Labels:\n";
    for (Label& ui : labelList) {
        ui.render(renderer, drawtype);
    }
}
SDL_Color* LabelPanel::getCol1(){
    return &fg;
}
SDL_Color* LabelPanel::getCol2(){
    return &bg;
}
FONT* LabelPanel::getFont(){
    return (labelList.size() ? labelList[0].getFont() : NULL);
}
SDL_Rect* LabelPanel::getBox(){
    setbox();
    return &box;
}
void LabelPanel::apply(){
    applyFont();
    applyCol1();
    applyCol2();
}
void LabelPanel::applyFont(){
    int size = labelList.size();
    if(!size)return;
    for(int i = 1; i < size - 1; i++){
        labelList[i].setFont(*labelList[0].getFont());
    }
}
void LabelPanel::applyCol1(){
    int size = labelList.size();
    if(!size)return;
    for(int i = 1; i < size - 1; i++){
        labelList[i].setCol1(*labelList[0].getCol1());
    }
}
void LabelPanel::applyCol2(){
    int size = labelList.size();
    if(!size)return;
    for(int i = 1; i < size - 1; i++){
        labelList[i].setCol2(*labelList[0].getCol2());
    }
}
void LabelPanel::setFont(const FONT& font) {
    if(!labelList.size())return;
    for(Label& ui : labelList){
        ui.setFont(font);
    }
}
void LabelPanel::setCol1(const SDL_Color& col) {
    if(!labelList.size())return;
    for(Label& ui : labelList){
        ui.setCol1(col);
    }
}
void LabelPanel::setCol2(const SDL_Color& col) {
    if(!labelList.size())return;
    for(Label& ui : labelList){
        ui.setCol2(col);
    }
}
void LabelPanel::onClick(UICommand* cmd) {
    UIelement::onClick(cmd);
    int size = labelList.size();
    if(!size)return;
    for(int i = 0; i < size; i++)
        if(!labelList[i].getClickCmd())labelList[i].onClick(cmd);
}
void LabelPanel::onFocus(UICommand* cmd) {
    UIelement::onFocus(cmd);
    int size = labelList.size();
    if(!size)return;
    for(int i = 0; i < size; i++)
        if(!labelList[i].getFocusCmd())labelList[i].onFocus(cmd);
}
void LabelPanel::onRevert(UICommand* cmd) {
    UIelement::onRevert(cmd);
    int size = labelList.size();
    if(!size)return;
    for(int i = 0; i < size; i++)
        if(!labelList[i].getRevertCmd())labelList[i].onRevert(cmd);
}
/* virtual */ void LabelPanel::setPos(int x, int y) {
    std::cout << " setting UIContainer pos:\n";
    box.x = x;
    box.y = y;
    int size = labelList.size();
    if(!size){
        std::cout << " Empty container\n";
        return;
    }
    std::cout << " pos0 " << x << " , " << y << std::endl;
    labelList[0].setPos(x, y);
    for(int i = 1; i < size; i++){
        int yp = labelList[i - 1].getBox()->h + labelList[i - 1].getBox()->y;
        std::cout << " pos " << i << " " << x << " , " << yp << std::endl;
        labelList[i].setPos(x, yp);
    }
}
/* virtual */ void LabelPanel::setbox(){
    uilog << " setting UIContainer box\n";
    box.w = 0;
    box.h = 0;
    for(Label& ui : labelList){
        SDL_Rect* rect = ui.getBox();
        if(rect->w > box.w) box.w = rect->w;
        uilog << " rbox: " << rect->w << ", " << rect->h << std::endl;
        box.h += rect->h;
    }
    uilog << " box: " << box.w << ", " << box.h << std::endl;
}
// UITab
void UITab::setbox(){
    int size = tabs.size();
    if(!size){
        Box.w = 0;
        Box.h = 0;
        return;
    }
    Box.w = std::max(tabs[currenttab]->getBox()->w, calcWidthSum());
    Box.h = tabs[currenttab]->getBox()->h + getLargestLabelHeight();
}
int UITab::calcWidthSum(){
    std::vector<Label>& LabelBoxes = labelList.getList();
    int width = 0;
    int size = tabnames.size();
    if(!size)return width;
    for(int i = 0; i < size; i++){
        width += LabelBoxes[i].getBox()->w;
    }
    return width;
}
void UITab::setLabels(){
    int size = tabnames.size();
    if(!size)return;
    std::vector<Label>& LabelBoxes = labelList.getList();
    for(int i = 0; i < size; i++){
        LabelBoxes[i].settext(tabnames[i] != "" ? 
            tabnames[i] : (i == (int)currenttab) ? "tabc" : "tab" + std::to_string(i + 1));
    }
}
void UITab::setallwidths(){
    std::vector<Label>& LabelBoxes = labelList.getList();
    int size = tabnames.size();
    if(!size)return;
    int width = calcWidthSum();
    for(int i = 0; i < size; i++){
        LabelBoxes[i].getBox()->w = width / size;
        LabelBoxes[i].getBox()->x = i * (width / size);
    }
}
int UITab::getLargestLabelHeight(){
    std::vector<Label>& LabelBoxes = labelList.getList();
    int height = 0;
    int size = tabnames.size();
    if(!size)return height;
    for(int i = 0; i < size; i++){
        Label& label = LabelBoxes[i];
        if(label.getBox()->h > height)height = label.getBox()->h;
    }
    return height;
}
int UITab::getLargestUICwidth(){
    int width = 0;
    for(UIContainer* ui : tabs)
    if(width < ui->getBox()->w)width = ui->getBox()->w;
    return width;
}
int UITab::getLargestUICheight(){
    int height = 0;
    for(UIContainer* ui : tabs)
    if(height < ui->getBox()->h)height = ui->getBox()->h;
    return height;
}
UITab::UITab(): UIelement(), currenttab(0), labelList(LabelPanel()), 
Box(SDL_Rect({0, 0, 0, 0})), fg(SDL_Color({0, 0, 0, 255})), bg(SDL_Color({255, 255, 255, 255})), font(FONT()){}
void UITab::update(InputManager& input) {
    tabs[currenttab]->update(input);
    int size = tabs.size();
    std::vector<Label>& labelboxes = labelList.getList();
    labelboxes[currenttab].clearCMD();
    for(int i = 0; i < size; i++){
        if(i != currenttab){
            labelboxes[i].update(input);
            if(labelboxes[i].getclick()){
                labelboxes[currenttab].onFocus(getFocusCmd());
                labelboxes[currenttab].onClick(getClickCmd());
                labelboxes[currenttab].onRevert(getRevertCmd());
                currenttab = i;
                labelboxes[i].clearCMD();
            }
        }
    }
}
void UITab::render(SDL_Renderer* rend, int drawtype) {
    int size = tabnames.size();
    if(!size)return;
    setbox();
    std::vector<Label>& labelboxes = labelList.getList();
    setLabels();
    int labheight = getLargestLabelHeight();
    int labswidth = calcWidthSum();
    int currtabwidth = tabs[currenttab]->getBox()->w;
    boxes[0].x = Box.x;
    if(labswidth > currtabwidth){
        tabs[currenttab]->setBoxW(labswidth);
        boxes[0].w = labelboxes[0].getBox()->w;
        for(int i = 1; i < size; i++){
            boxes[i].w = labelboxes[i].getBox()->w;
            boxes[i].x = boxes[i - 1].x + boxes[i - 1].w;
        }
    }
    else{
        int width = currtabwidth / size;
        boxes[0].w = width;
        for(int i = 1; i < size; i++){
            boxes[i].w = width;
            boxes[i].x = boxes[i - 1].x + boxes[i - 1].w;
        }
        if(currtabwidth % labswidth){
            boxes[size - 1].w += (currtabwidth - size * width);
        }
    }
    tabs[currenttab]->setPos(Box.x, Box.y + labheight - drawtype / 2);
    tabs[currenttab]->render(rend, drawtype);
    for(int i = 0; i < size; i++){
        boxes[i].h = labheight;
        SDL_Rect boxy = boxes[i];
        if(i == currenttab){
            boxy.y += 1;
            setRenCol(rend, bg);
            SDL_RenderFillRect(rend, &boxy);
            setRenCol(rend, fg);
            SDL_RenderDrawLine(rend, boxes[i].x, boxes[i].y, boxes[i].x + boxes[i].w, boxes[i].y);
            if(!i)SDL_RenderDrawLine(rend, boxes[i].x, boxes[i].y, boxes[i].x, boxes[i].y + labheight);
            if(i == size - 1)SDL_RenderDrawLine(rend, boxes[i].x + boxes[i].w, boxes[i].y, boxes[i].x + boxes[i].w, boxes[i].y + labheight);
        }
        else{
            float t = 0.5;
            SDL_Color col = darken(bg);
            setRenCol(rend, col);
            SDL_RenderFillRect(rend, &boxy);
            setRenCol(rend, fg);
            Texture2D::drawRect(boxy, rend, drawtype/2);
        }
        labelboxes[i].setPos(boxes[i].x, boxes[i].y);
        labelboxes[i].render(rend, drawtype);
    }
}
void UITab::setPos(int x, int y) {
    Box.x = x;
    Box.y = y;
    if (!tabs.empty()) {
        for(UIContainer* uic : tabs)
        uic->setPos(x, y);
        for(SDL_Rect& box: boxes)
        {
            box.x = x;
            box.y = y;
        }
    }
}
void UITab::setCol1(const SDL_Color& col) {
    fg = col;
    labelList.setCol1(fg);
    for (auto* tab : tabs) {
        tab->setCol1(col);
    }
}
void UITab::setCol2(const SDL_Color& col) {
    bg = col;
    labelList.setCol2(bg);
    for (auto* tab : tabs) {
        tab->setCol2(col);
    }
}
void UITab::setFont(const FONT& font_) {
    font = font_;
    for (auto* tab : tabs) {
        tab->setFont(font);
    }
    labelList.setFont(font);
}
SDL_Rect* UITab::getBox() {
    if (!tabs.empty()) {
        return tabs[currenttab]->getBox();
    }
    static SDL_Rect dummy = {0, 0, 0, 0};
    return &dummy;
}
FONT* UITab::getFont() {
    if (!tabs.empty()) {
        return tabs[currenttab]->getFont();
    }
    return nullptr;
}
SDL_Color* UITab::getCol1() {
    if (!tabs.empty()) {
        return tabs[currenttab]->getCol1();
    }
    return nullptr;
}
SDL_Color* UITab::getCol2() {
    if (!tabs.empty()) {
        return tabs[currenttab]->getCol2();
    }
    return nullptr;
}
void UITab::onFocus(UICommand* cmd) {
    UIelement::onFocus(cmd);
    int size = tabs.size();
    if(!size)return;
    for(int i = 0; i < size; i++)
    if(i != currenttab)labelList.getList()[i].onFocus(cmd);
    for (auto* tab : tabs) {
        tab->onFocus(cmd);
    }
}
void UITab::onClick(UICommand* cmd) {
    UIelement::onClick(cmd);
    int size = tabs.size();
    if(!size)return;
    for(int i = 0; i < size; i++)
    if(i != currenttab)labelList.getList()[i].onClick(cmd);
    for (auto* tab : tabs) {
        tab->onClick(cmd);
    }
}
void UITab::onRevert(UICommand* cmd) {
    UIelement::onRevert(cmd);
    int size = tabs.size();
    if(!size)return;
    for(int i = 0; i < size; i++)
    if(i != currenttab)labelList.getList()[i].onRevert(cmd);
    for (auto* tab : tabs) {
        tab->onRevert(cmd);
    }
}
void UITab::push(UIContainer& tab, const char* name){
    tabs.push_back(&tab);
    tabnames.push_back(name ? name : "");
    labelList.push(Label());
    boxes.push_back(SDL_Rect({0, 0, 0, 0}));
}
void UITab::push(UIContainer* tab, const char* name){
    tabs.push_back(tab);
    tabnames.push_back(name ? name : "");
    labelList.push(Label(tabnames.back().c_str()));
    boxes.push_back(SDL_Rect({0, 0, 0, 0}));
}
void UITab::settabname(int i, const char* name){
    tabnames[i] = (name ? name : "");
}
void UITab::settabname(int i, const std::string& name){
    tabnames[i] = name;
}
void UITab::setCurrentTab(int i){
    if(i < 0 || i >= tabs.size())return;
    currenttab = i;
}
int UITab::getCurrentTab() const {
    return currenttab;
}
UIContainer* UITab::getCurrentTabContainer() const {
    if(currenttab < 0 || currenttab >= tabs.size())return NULL;
    return tabs[currenttab];
}
// InputBox 
InputBox::InputBox() : Label(UIcmdset({NULL, new UIMultiCommand(this), NULL})), 
    multref(*static_cast<UIMultiCommand*>(UIcmds.click)), dims(SDL_Point({0, 0})){
    //std::cout << " input boxing\n";
    //if(UIcmds.click == NULL)std::cout << " click not okay\n";
    multref.push((new InputStringUIcmd(NULL, this)));
    //ChangeStringCmd<UIelement>* temp = new ChangeStringCmd<UIelement>(NULL, this, &labelText.getTextRef());
    //multcom.push(static_cast<UICommand*>(temp));
}
InputBox::InputBox(const char* str) : InputBox() {
    settext(str);
}
InputBox::InputBox(int x, int y) : InputBox() {
    setPos(x, y);
}
InputBox::InputBox(const FONT& font) : InputBox() {
    setFont(font);
}
/* inline*/ void InputBox::setdims(int x, int y){
    dims.x = x;
    dims.y = y;
}
/* inline*/ void InputBox::onClick(UICommand* cmd){
    multref.push(cmd);
    //multcom.push(cmd);
}
void InputBox::update(InputManager& input){
    TextInputHandler& inputT = *static_cast<TextInputHandler*>(&input);
    static InputStringUIcmd& inputSetter = *static_cast<InputStringUIcmd*>(multref.getcmd(0));
    //static ChangeStringCmd<UIelement>* inputSetter = reinterpret_cast<ChangeStringCmd<UIelement>*>(multcom.getcmd(0));
    inputSetter.setInputer(inputT);
    std::string thetext = getText();
    inputSetter.setStrRef(thetext);
    iswrite = inputSetter.iswritingON();
    //std::cout << " checking click\n";
    //if(UIcmds.click == NULL)std::cout << " click okay\n";;
    Label::update(input);
    inputSetter.checktext();
    settext(thetext);
    //if(!isfocus && input.isMouseReady(SDL_BUTTON_LEFT) || input.isMouseReady(SDL_BUTTON_RIGHT))inputSetter.setwriting(false);
}
void InputBox::render(SDL_Renderer* renderer, int drawtype){
    checkfile();
    uilog << " Rendering InputBox: \n";
    if(!texture){
        if(!font.getfont()){
            box.w = dims.x;
            box.h = dims.y;
            setRenCol(renderer, bg);
            SDL_RenderDrawRect(renderer, &box);
            setRenCol(renderer, fg);
            Texture2D::drawRect(box, renderer, drawtype / 2);
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
    Texture2D::drawRect(box, renderer, drawtype / 2);
    // Render the label text using the provided renderer
}
const SDL_Point& InputBox::getDims() const {
    return dims;
}
bool InputBox::isWritingON() const{
    return iswrite;
}
InputBox::~InputBox(){
    delete multref.getcmd(0);
}
// LabelArea
void LabelArea::setBox() {
    Box.w = Box.h = 0;
    int size = lines.size();
    if(!size){
        Box.w = Label::getBox()->w;
        Box.h = Label::getBox()->h;
        return;
    }
    for(int i = 0; i < size; i++){
        int w, h;
        getFont()->TEXT_size(lines[i].c_str(), &w, &h);
        if(Box.w < w)Box.w = w;
        Box.h += h + linespacing;
    }
}

void LabelArea::setPos(int x, int y) {
    Box.x = x;
    Box.y = y;
    Label::setPos(x, y);
}

void LabelArea::setCol1(const SDL_Color& col) {
    fg = col;
    Label::setCol1(col);
}

void LabelArea::setCol2(const SDL_Color& col) {
    bg = col;
    Label::setCol2(col);
}

void LabelArea::setFont(const FONT& font) {
    Label::setFont(font);
    setBox();
}

SDL_Rect* LabelArea::getBox() {
    setBox();
    return &Box;
}

void LabelArea::render(SDL_Renderer* rend, int drawtype) {
    setRenCol(rend, bg);
    SDL_RenderFillRect(rend, &Box);
    setRenCol(rend, fg);
    Texture2D::drawRect(Box, rend, drawtype / 2);
    int size = lines.size();
    if(!size){
        Label::render(rend, drawtype);
        return;
    }
    settext(lines[0]);
    Label::setPos(Box.x, Box.y);
    Label::render(rend, drawtype);
    int h = Label::getBox()->h + Label::getBox()->y;
    for(int i = 1; i < size; i++){
        settext(lines[i]);
        Label::setPos(Box.x, h + linespacing);
        Label::render(rend, drawtype);
        h = Label::getBox()->h + Label::getBox()->y;
    }
}

LabelArea::LabelArea() : Label(), linespacing(0), Box(SDL_Rect({0, 0, 0, 0})), 
    fg(SDL_Color({0, 0, 0, 255})), bg(SDL_Color({255, 255, 255, 255})) {}

void LabelArea::push(const std::string& str){
    lines.push_back(str);
    setBox();
}

void LabelArea::push(const char* str){
    lines.push_back(str ? str : "");
    setBox();
}

// InputArea
// No methods defined in the original class, so nothing to move here.

// PasswordBox
// No methods defined in the original class, so nothing to move here.
/*
class InputArea : public LabelArea{
    // 
};
class PasswordBox : public InputBox {

};
*/
/*
🔹 2. Buttons & Interaction
*/

// ...existing code...

// --- Begin extracted Button and below methods ---

void Button::setPos(int x, int y) {
    Box.x = x; Box.y = y;
}
void Button::setCol1(const SDL_Color& col) {
    fg = col;
}
void Button::setCol2(const SDL_Color& col) {
    bg = col;
}
void Button::setFont(const FONT& font) {}
SDL_Rect* Button::getBox() {return &Box;}
FONT* Button::getFont() {return NULL;}
SDL_Color* Button::getCol1() {return &fg;}
SDL_Color* Button::getCol2() {return &bg;}
//void Button::update(InputManager& input) {}
// Button implementation
Button::Button() : UIelement(), fg(SDL_Color({0, 0, 0, 255})), bg(SDL_Color({255, 255, 255, 255})) {}
void Button::setBoxDim(int w, int h){
    Box.w = w;
    Box.h = h;
}

void CheckBox::update(InputManager& input) {
    //std::cout << " updating\n";
    Button::update(input);
    if(getclick()){
        clickstate = !clickstate;
    }
}
void CheckBox::render(SDL_Renderer* rend, int drawtype) {
    //std::cout << " rendering\n";
    switch(type){
        case CLASSIC:{
            if(clickstate){
                setRenCol(rend, bg);
                SDL_RenderFillRect(rend, &Box);
            }
            setRenCol(rend, fg);
            Texture2D::drawRect(Box, rend, drawtype / 2);
            return;
        }
        case FLIPBOX:{
            setRenCol(rend, fg);
            Texture2D::drawRect(Box, rend, drawtype / 2);
            const SDL_Rect bBox = {Box.x + drawtype / 2, Box.y + drawtype / 2, Box.w - drawtype + 1, Box.h - drawtype + 1};
            if(clickstate){
                const SDL_Rect tbox = {Box.x, Box.y,
                    Box.h <= Box.w / 4 ? Box.h : Box.w / 4, Box.h};
                setRenCol(rend, bg);
                SDL_RenderFillRect(rend, &bBox);
                SDL_RenderFillRect(rend, &tbox);
                setRenCol(rend, fg);
                Texture2D::drawRect(tbox, rend, drawtype / 2);
                return;
            }
            else{
                const SDL_Rect tbox = {Box.x + (int)((float)Box.w * 0.75), Box.y,
                    Box.h <= Box.w / 4 ? Box.h : Box.w / 4, Box.h};
                SDL_Color col = greenToRed(bg);
                setRenCol(rend, col);
                SDL_RenderFillRect(rend, &bBox);
                SDL_RenderFillRect(rend, &tbox);
                setRenCol(rend, fg);
                Texture2D::drawRect(tbox, rend, drawtype / 2);
                return;
            }
        }
        case TICKBOX:{
            setRenCol(rend, fg);
            Texture2D::drawRect(Box, rend, drawtype / 2);
            if(clickstate)// draw tick;
            {
                setRenCol(rend, bg);
                int avgbox = (Box.w + Box.h) / 2;
                thickLineRGBA(rend, Box.x + Box.w / 4, Box.y + Box.h / 4, 
                    Box.x + Box.w / 4, Box.y + (int)((float)Box.h * 0.75), drawtype, fg.r, fg.g, fg.b, fg.a);
                thickLineRGBA(rend, Box.x + Box.w / 4, Box.y + (int)((float)Box.h * 0.75), 
                Box.x + Box.w, Box.y, drawtype, fg.r, fg.g, fg.b, fg.a);
            }
            return;
        }
        default:{
            if(clickstate){
                setRenCol(rend, bg);
                SDL_RenderFillRect(rend, &Box);
            }
            setRenCol(rend, fg);
            Texture2D::drawRect(Box, rend, drawtype / 2);
            return;
        }
    }
}
//
CheckBox::CheckBox(checkType typei) : Button(), clickstate(false), type(typei){
    settype(type);
}
const CheckBox& CheckBox::operator=(const CheckBox& sbox){
    if(this != &sbox){
        fg = sbox.fg;
        bg = sbox.bg;
        clickstate = sbox.clickstate;
        Box = sbox.Box;
        type = sbox.type;
    }
    return *this;
}
//
void CheckBox::settype(checkType typei){
    int nowsize = 50;
    type = typei;
    switch (type)
    {
        case CLASSIC:{
            Box.w = Box.h = nowsize;
            break;
        }
        case FLIPBOX:{
            Box.w = nowsize;
            Box.h = nowsize / 4;
            break;
        }
        default:{
            Box.w = Box.h = nowsize;
            break;
        }
    }
}
bool CheckBox::getState() const {
    return clickstate;
}
void CheckBox::setState(){
    clickstate = true;
}
void CheckBox::clearState() {
    clickstate = false;
}
void CheckBox::toogleState() {
    clickstate = !clickstate;
}
void CheckBox::executeClick() {
    UIcmds.click->setref(this);
    UIcmds.click->execute();
}
void CheckBox::executeFocus() {
    UIcmds.focus->setref(this);
    UIcmds.focus->execute();
}
void CheckBox::executeRevert() {
    UIcmds.revert->execute();
}
// RadioButton
void RadioButton::setPos(int x , int y) {
    Box.x = x;
    Box.y = y;
    if(!size)return;
    for(CheckBox& cb: cboxes){
        cb.setPos(x, y);
        y += cb.getBox()->h;
    }
}
void RadioButton::setCol1(const SDL_Color& col){
    fg = col;
    for(CheckBox& cb: cboxes){
        cb.setCol1(col);
        std::cout << " col: " << (int)cb.getCol1()->r << ", " << (int)cb.getCol1()->g << ", " << (int)cb.getCol1()->b << ", " << (int)cb.getCol1()->a << std::endl;
    }
}
void RadioButton::setCol2(const SDL_Color& col){
    bg = col;
    for(CheckBox& cb: cboxes)cb.setCol2(col);
}
void RadioButton::setFont(const FONT& font){}
SDL_Rect* RadioButton::getBox(){
    return &Box;
}
FONT* RadioButton::getFont(){
    return NULL;
}
SDL_Color* RadioButton::getCol1(){
    return &fg;
}
SDL_Color* RadioButton::getCol2(){
    return &bg;
}
void RadioButton::update(InputManager& input) {
    UIelement::update(input);
    if(!size)return;
    for(int i = 0; i < size; i++){
        cboxes.at(i).Button::update(input);
        if(cboxes.at(i).getclick()){
            if(current != i){
                if(current >= 0 && current < size){
                    cboxes.at(current).clearState();
                }
                cboxes.at(i).setState();
                current = i;
            }
        }
    }
}
void RadioButton::render(SDL_Renderer* rend, int drawtype) {
    if(!size)return;
    for(CheckBox& cb: cboxes)cb.render(rend, drawtype);
}
void RadioButton::onFocus(UICommand* cmd) {
    UIelement::onFocus(cmd);
    for(CheckBox& cb: cboxes)cb.onFocus(cmd);
}
void RadioButton::onClick(UICommand* cmd) {
    UIelement::onClick(cmd);
    for(CheckBox& cb: cboxes)cb.onClick(cmd);
}
void RadioButton::onRevert(UICommand* cmd) {
    UIelement::onRevert(cmd);
    for(CheckBox& cb: cboxes)cb.onRevert(cmd);
}
RadioButton::RadioButton() : UIelement(), size(0), current(-1), fcurrent(-1), Box(SDL_Rect({0, 0, 0, 0})), 
fg(SDL_Color({0, 0, 0, 255})), bg(SDL_Color({255, 255, 255, 255})){}

void RadioButton::push(){
    cboxes.push_back(CheckBox(size ? cboxes.at(0).type : CLASSIC));
    size++;
    cboxes.back().setCol1(fg);
    cboxes.back().setCol2(bg);
    Box.w = std::max(Box.w, cboxes.back().getBox()->w);
    Box.h += cboxes.back().getBox()->h;
    cboxes.back().setPos(Box.x, Box.y + Box.h);
}
void RadioButton::setbox() {
    if(!size)return;
}
int RadioButton::getCurrent() const {
    return current;
}
int RadioButton::getFCurrent() const {
    return fcurrent;
}
// IncDecButton
void IncDecButton::render(SDL_Renderer* rend, int drawtype){
    switch (type){
        case INC_HORI:{
            def:
            if(getfocus()){
                if(getclick())setRenCol(rend, fg);
                else setRenCol(rend, bg);
                SDL_Point 
                p0 = {Box.x, Box.y}, 
                p1 = {Box.x, Box.y + Box.h},
                p2 = {Box.x + Box.w, Box.y + Box.h / 2};
                fillTriangle(rend, p0, p1, p2);
            }
            setRenCol(rend, fg);
            thickLineRGBA(rend, Box.x, Box.y, Box.x, Box.y + Box.h, drawtype / 2, fg.r, fg.g, fg.b, fg.a);
            thickLineRGBA(rend, Box.x, Box.y + Box.h, Box.x + Box.w, Box.y + Box.h / 2, drawtype / 2, fg.r, fg.g, fg.b, fg.a);
            thickLineRGBA(rend, Box.x + Box.w, Box.y + Box.h / 2, Box.x, Box.y, drawtype/2, fg.r, fg.g, fg.b, fg.a);
            break;
        }
        case DEC_HORI:{
            if(getfocus()){
                if(getclick())setRenCol(rend, fg);
                else setRenCol(rend, bg);
                SDL_Point 
                p0 = {Box.x + Box.w, Box.y}, 
                p1 = {Box.x + Box.w, Box.y + Box.h},
                p2 = {Box.x, Box.y + Box.h / 2};
                fillTriangle(rend, p0, p1, p2);
            }
            setRenCol(rend, fg);
            thickLineRGBA(rend, Box.x, Box.y + Box.h / 2, Box.x + Box.w, Box.y, drawtype / 2, fg.r, fg.g, fg.b, fg.a);
            thickLineRGBA(rend, Box.x, Box.y + Box.h / 2, Box.x + Box.w, Box.y + Box.h, drawtype / 2, fg.r, fg.g, fg.b, fg.a);
            thickLineRGBA(rend, Box.x + Box.w, Box.y, Box.x + Box.w, Box.y + Box.h, drawtype / 2, fg.r, fg.g, fg.b, fg.a);
            break;
        }
        case INC_VERT:{
            if(getfocus()){
                if(getclick())setRenCol(rend, fg);
                else setRenCol(rend, bg);
                SDL_Point 
                p0 = {Box.x + Box.w / 2, Box.y}, 
                p1 = {Box.x + Box.w, Box.y + Box.h},
                p2 = {Box.x, Box.y + Box.h};
                fillTriangle(rend, p0, p1, p2);
            }
            setRenCol(rend, fg);
            thickLineRGBA(rend, Box.x, Box.y + Box.h, Box.x + Box.w, Box.y + Box.h, drawtype / 2, fg.r, fg.g, fg.b, fg.a);
            thickLineRGBA(rend, Box.x, Box.y + Box.h, Box.x + Box.w / 2, Box.y, drawtype / 2, fg.r, fg.g, fg.b, fg.a);
            thickLineRGBA(rend, Box.x + Box.w / 2, Box.y, Box.x + Box.w, Box.y + Box.h, drawtype / 2, fg.r, fg.g, fg.b, fg.a);
            break;
        }
        case DEC_VERT:{
            if(getfocus()){
                if(getclick())setRenCol(rend, fg);
                else setRenCol(rend, bg);
                SDL_Point 
                p0 = {Box.x, Box.y}, 
                p1 = {Box.x + Box.w, Box.y},
                p2 = {Box.x + Box.w / 2, Box.y + Box.h};
                fillTriangle(rend, p0, p1, p2);
            }
            setRenCol(rend, fg);
            thickLineRGBA(rend, Box.x, Box.y, Box.x + Box.w, Box.y, drawtype / 2, fg.r, fg.g, fg.b, fg.a);
            thickLineRGBA(rend, Box.x, Box.y, Box.x + Box.w / 2, Box.y + Box.h, drawtype / 2, fg.r, fg.g, fg.b, fg.a);
            thickLineRGBA(rend, Box.x + Box.w / 2, Box.y + Box.h, Box.x + Box.w, Box.y, drawtype / 2, fg.r, fg.g, fg.b, fg.a);
            break;
        }
        default: {
            goto def;
            break;
        }
    }
}
// imps
IncDecButton::IncDecButton(Orientation typei) : Button(), type(typei) {}
void IncDecButton::setType(Orientation typei){
    type = typei;
}
Orientation IncDecButton::getType() const {return type;}

void IncDecCheckbox::update(InputManager& input) {
    IncDecButton::update(input);
    if(getclick()){
        clickstate = !clickstate;
    }
}
void IncDecCheckbox::render(SDL_Renderer* rend, int drawtype) {
    if(clickstate){
        if(type == VERT){
            IncDecButton::setType(INC_VERT);
        }
        else IncDecButton::setType(INC_HORI);
    }
    else if(type == VERT){
        IncDecButton::setType(DEC_VERT);
    }
    else IncDecButton::setType(DEC_HORI);
    IncDecButton::render(rend, drawtype);
}
//
IncDecCheckbox::IncDecCheckbox(orient typei) : IncDecButton(), clickstate(false), type(typei){}
void IncDecCheckbox::setType(orient typei){
    type = typei;
}
bool IncDecCheckbox::getState() const {
    return clickstate;
}
void IncDecCheckbox::setState(){
    clickstate = true;
}
void IncDecCheckbox::clearState(){
    clickstate = false;
}
void IncDecCheckbox::toggleState(){
    clickstate = !clickstate;
}

void TextSwitch::setPos(int x , int y) {
    setBox();
    Box.x = x;
    Box.y = y;
    //inc.setType(INC_HORI);
    //dec.setType(DEC_HORI);
    dec.setPos(x, y);
    theText.setPos(dec.getBox()->x + dec.getBox()->w, y);
    inc.setPos(theText.getBox()->x + theText.getBox()->w, y);
}
void TextSwitch::setCol1(const SDL_Color& col) {
    fg = col;
    theText.setCol1(col);
    inc.setCol1(col);
    dec.setCol1(col);
}
void TextSwitch::setCol2(const SDL_Color& col) {
    bg = col;
    theText.setCol2(col);
    inc.setCol2(col);
    dec.setCol2(col);
}
void TextSwitch::setFont(const FONT& font) {
    theText.setFont(font);
}
SDL_Rect* TextSwitch::getBox() {
    setBox();
    return &Box;
}
FONT* TextSwitch::getFont() {
    return theText.getFont();
}
SDL_Color* TextSwitch::getCol1() {
    return &fg;
}
SDL_Color* TextSwitch::getCol2() {
    return &bg;
}
void TextSwitch::update(InputManager& input) {
    dec.update(input);
    inc.update(input);
    theText.update(input);
    int size = texts.size();
    if(!size)return;
    if(dec.getclick()){
        current--;
        if(current < 0) current = size - 1;
    }
    else if(inc.getclick() || theText.getclick()){
        current++;
        if(current == size) current = 0;
    }
    theText.settext(texts[current]);
    setPos(Box.x, Box.y);
}
void TextSwitch::render(SDL_Renderer* rend, int drawtype) {
    setRenCol(rend, fg);
    Texture2D::drawRect(Box, rend, drawtype / 2);
    dec.render(rend, drawtype);
    inc.render(rend, drawtype);
    theText.render(rend, drawtype);
}
//
void TextSwitch::onFocus(UICommand* cmd){
    UIelement::onFocus(cmd);
    theText.onFocus(cmd);
    dec.onFocus(cmd);
    inc.onFocus(cmd);
}
void TextSwitch::onClick(UICommand* cmd){
    UIelement::onClick(cmd);
    theText.onClick(cmd);
    dec.onClick(cmd);
    inc.onClick(cmd);
}
void TextSwitch::onRevert(UICommand* cmd){
    UIelement::onRevert(cmd);
    theText.onRevert(cmd);
    dec.onRevert(cmd);
    inc.onRevert(cmd);
}
//
std::string& TextSwitch::getText() {
    return texts[current];
}
//
TextSwitch::TextSwitch() : UIelement(), current(0), Box(SDL_Rect({0, 0, 0, 0})), fg(SDL_Color({0, 0, 0, 255})),
bg(SDL_Color({255, 255, 255, 255})), theText(), inc(INC_HORI), dec(DEC_HORI) {}
void TextSwitch::setBox(){
    Box.w = Box.h = 0;
    inc.setBoxDim(theText.getBox()->h, theText.getBox()->h);
    dec.setBoxDim(theText.getBox()->h, theText.getBox()->h);
    Box.w += 2 * inc.getBox()->w + theText.getBox()->w;
    Box.h += theText.getBox()->h;
}
void TextSwitch::push(const std::string& txt){
    texts.push_back(txt);
}
void TextSwitch::push(const char* txt){
    texts.push_back(txt);
}
/*
🔹 3. Selection & Lists
*/
// Dropdown
void Dropdown::setBox() {
    Box.w = Box.h = 0;
    int width = largestwidth();
    int height = largestheight();
    width = width ? width : 70;
    height = height ? height : 18;
    updown.setBoxDim(height, height);
    Box.w = width + height;
    Box.h = height;
    if(updown.getState()){
        if(options.empty())Box.h += height;
        else{
            Box.h += height * (options.size() - 1);
        }
    }
}

int Dropdown::largestheight() {
    if(options.empty())return 0;
    int height = 0;
    for(Label& opt : options){
        if(height < opt.getBox()->h)height = opt.getBox()->h;
    }
    return height;
}

int Dropdown::largestwidth() {
    if(options.empty())return 0;
    int width = 0;
    for(Label& opt : options){
        if(width < opt.getBox()->w)width = opt.getBox()->w;
    }
    return width;
}

void Dropdown::setPos(int x , int y) {
    setBox();
    Box.x = x;
    Box.y = y;
    int size = options.size();
    updown.setPos(Box.x + Box.w - updown.getBox()->w, y);
    if(!size)return;
    options[0].setPos(x, y);
    for(int i = 1; i < size; i++){
        options[i].setPos(x, options[i - 1].getBox()->y + options[i - 1].getBox()->h);
    }
}

void Dropdown::setCol1(const SDL_Color& col){
    fg = col;
    int size = options.size();
    if(!size)return;
    for(int i = 0; i < size; i++){
        options[i].setCol1(col);
    }
    setPos(Box.x, Box.y);
}

void Dropdown::setCol2(const SDL_Color& col){
    bg = col;
    int size = options.size();
    if(!size)return;
    for(int i = 0; i < size; i++){
        options[i].setCol2(col);
    }
    setPos(Box.x, Box.y);
}

void Dropdown::setFont(const FONT& font){
    int size = options.size();
    if(!size)return;
    for(int i = 0; i < size; i++){
        options[i].setFont(font);
    }
    setPos(Box.x, Box.y);
}

SDL_Rect* Dropdown::getBox(){
    setBox();
    return &Box;
}

FONT* Dropdown::getFont(){
    int size = options.size();
    if(!size)return NULL;
    return options[0].getFont();
}

SDL_Color* Dropdown::getCol1(){
    return &fg;
}

SDL_Color* Dropdown::getCol2(){
    return &bg;
}

void Dropdown::update(InputManager& input) {
    updown.update(input);
    if(options.empty())return;
    if(updown.getState()){
        for(Label& opt : options){
            opt.update(input);
            if(opt.getclick()){
                std::swap(opt, options[0]);
                updown.clearState();
            }
        }
    }
    else{
        options[0].update(input);
        if(options[0].getclick()){
            updown.setState();
        }
    }
    setPos(Box.x, Box.y);
}

void Dropdown::render(SDL_Renderer* rend, int drawtype) {
    setRenCol(rend, bg);
    SDL_RenderFillRect(rend, &Box);
    setRenCol(rend, fg);
    Texture2D::drawRect(Box, rend, drawtype / 2);
    if(updown.getState()){
        if(!options.empty()){
            for(Label& opt : options)
                opt.render(rend, drawtype);
        }
        setRenCol(rend, fg);
        for(int line = updown.getBox()->h; line < Box.h; line += updown.getBox()->h){
            DrawThickLine(rend, Box.x, Box.y + line, Box.x + Box.w, Box.y + line, drawtype / 2);
        }
    }
    else if(!options.empty())options[0].render(rend, drawtype);
    updown.render(rend, drawtype);
}

Dropdown::Dropdown() : UIelement(), Box(SDL_Rect({0, 0, 0, 0})), fg(SDL_Color({0, 0, 0, 255})), 
    bg(SDL_Color({255, 255, 255, 255})), updown(VERT){}

void Dropdown::push(const Label& opt){
    options.push_back(opt);
    setPos(Box.x, Box.y);
}

void Dropdown::push(const std::string& str){
    options.push_back(Label(str.c_str()));
    setPos(Box.x, Box.y);
}

void Dropdown::push(const char* str){
    options.push_back(Label(str));
    setPos(Box.x, Box.y);
}
/*
class ListBox : public Dropdown{

};

class MultiSelect : public ListBox{

};

class AutoCompleteBox : public Dropdown{

};

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
*/
// ChangeLevelUIcmd
ChangeLevelUIcmd::ChangeLevelUIcmd(InputManager* input , UIelement* ref , 
    SDL_Scancode quiter ): UICommand(ref), 
    inputHandler(input), quitCase(quiter), 
    increaseCase(SDL_SCANCODE_UP), decreaseCase(SDL_SCANCODE_DOWN){}
void ChangeLevelUIcmd::setRef(InputManager* input ){
    inputHandler = input;
}
void ChangeLevelUIcmd::quitit(){
    increase = NULL;
    decrease = NULL;
}
cond ChangeLevelUIcmd::checkcond(){
    cond ret = NTN;
    if(!increase || !decrease)return EXT;
    if(!inputHandler)return EXT;
    if(inputHandler->isKeyDown(quitCase)){
        ret = EXT;
    }
    else{
        if(*increase)ret = INC;
        else if(*decrease)ret = DEC;
    }
    return ret;
}
void ChangeLevelUIcmd::setIncrease(SDL_Scancode inced ){
    increaseCase = inced;
}
void ChangeLevelUIcmd::setDecrease(SDL_Scancode deced ){
    decreaseCase = deced;
}
void ChangeLevelUIcmd::setQuit(SDL_Scancode quitC){
    quitCase = quitC;
}
ChangeLevelUIcmd* ChangeLevelUIcmd::clone() const {
    return new ChangeLevelUIcmd(*this);
}
void ChangeLevelUIcmd::execute(){
    if(!inputHandler){
        return;
    }
    std::array<bool, SDL_NUM_SCANCODES>& keyDowns = inputHandler->getKeyDowns();
    increase = &keyDowns[increaseCase];
    decrease = &keyDowns[decreaseCase];
}
// Slider

Slider::Slider(bool focus, bool hover, bool click, bool revert)
    : UIelement(UIcmdset({NULL, new UIMultiCommand(this)}), focus, hover, click, revert), 
    multref(*static_cast<UIMultiCommand*>(UIcmds.click)), portion(50){
    multref.push(new ChangeLevelUIcmd(NULL, this));
}

Slider::Slider(orient slideType): UIelement(UIcmdset({NULL, new UIMultiCommand(this)})), 
    type(slideType), multref(*static_cast<UIMultiCommand*>(UIcmds.click)), portion(50){
    multref.push(new ChangeLevelUIcmd(NULL, this));
}

Slider::Slider(const SDL_Rect& slidebox): UIelement(UIcmdset({NULL, new UIMultiCommand(this)})), 
    box(slidebox), multref(*static_cast<UIMultiCommand*>(UIcmds.click)), portion(50){
    multref.push(new ChangeLevelUIcmd(NULL, this));
    checkbox();
}

void Slider::setType(orient slideType){
    type = slideType;
}

void Slider::setportion(short port){
    portion = port;
    checkportion();
}

void Slider::checkbox(){
    if(box.w > box.h)type = HORI;
    else type = VERT;
}

void Slider::setPos(int x, int y) {
    box.x = x;
    box.y = y;
}

void Slider::setBox(int w, int h){
    box.w = w;
    box.h = h;
    checkbox();
}

SDL_Color* Slider::getCol1() {
    return &fg;
}

SDL_Color* Slider::getCol2() {
    return &bg;
}

FONT* Slider::getFont() {
    return NULL;
}

SDL_Rect* Slider::getBox() {
    return &box;
}

void Slider::update(InputManager& input) {
    static ChangeLevelUIcmd& refcheck = *static_cast<ChangeLevelUIcmd*>(multref.getcmd(0));
    refcheck.setRef(&input);
    UIelement::update(input);
    cond curr = refcheck.checkcond();
    setascond(curr);
    if(curr == EXT){
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

void Slider::checkportion(){
    if(portion > 100)portion = 100;
    if(portion < 0)portion = 0;
}

short Slider::getportion() const {
    return portion;
}

void Slider::setascond(cond curr){
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

void Slider::render(SDL_Renderer* rend, int drawt) {
    float percent = portion * 0.01f;
    int width = type == HORI ? (int)((float)box.w * percent) - 1 : box.w - 1;
    int height = type == VERT ? (int)((float)box.h * percent) - 1 : box.h - 1;
    if(width < 0)width = 0;
    if(height < 0)height = 0;
    SDL_Rect boxportion = {box.x + 1, type == HORI ? box.y + 1 : box.y + 1 + (int)((float)box.h * (1.0f - percent)), width, height};
    setRenCol(rend, bg);
    SDL_RenderFillRect(rend, &boxportion);
    setRenCol(rend, fg);
    int drawtype = drawt <= 2 ? type == HORI ? box.h/2 : box.w/2 : drawt;
    Texture2D::drawRect(box, rend, drawtype);
}

void Slider::setCol1(const SDL_Color& col) {
    fg = col;
}

void Slider::setCol2(const SDL_Color& col) {
    bg = col;
}

void Slider::setFont(const FONT& font) {
    return;
}

void Slider::onClick(UICommand* cmd) {
    multref.push(cmd);
}

Slider::~Slider(){
    delete multref.getcmd(0);
}
// SpinBox

void SpinBox::setasType(){
    if(type == VERT){
        inc.setType(INC_VERT);
        dec.setType(DEC_VERT);
    }
    else{
        inc.setType(INC_HORI);
        dec.setType(DEC_HORI);
    }
}

void SpinBox::setBox(){
    Box.w = Box.h = 0;
    if(type == VERT){
        inc.setBoxDim(thenum.getBox()->h / 2, thenum.getBox()->h / 2);
        dec.setBoxDim(thenum.getBox()->h / 2, thenum.getBox()->h / 2);
        Box.w += inc.getBox()->w + thenum.getBox()->w;
    }
    else{
        inc.setBoxDim(thenum.getBox()->h, thenum.getBox()->h);
        dec.setBoxDim(thenum.getBox()->h, thenum.getBox()->h);
        Box.w += 2 * inc.getBox()->w + thenum.getBox()->w;
    }
    Box.h = thenum.getBox()->h;
}

void SpinBox::setPos(int x, int y){
    setBox();
    Box.x = x;
    Box.y = y;
    if(type == VERT){
        inc.setPos(x, y);
        dec.setPos(x, inc.getBox()->y + inc.getBox()->h);
        thenum.setPos(inc.getBox()->x + inc.getBox()->w, y);
    }
    else{
        dec.setPos(x, y);
        thenum.setPos(dec.getBox()->x + dec.getBox()->w, y);
        inc.setPos(thenum.getBox()->x + thenum.getBox()->w, y);
    }
}

void SpinBox::setCol1(const SDL_Color& col) {
    fg = col;
    thenum.setCol1(col);
    inc.setCol1(col);
    dec.setCol1(col);
    setPos(Box.x, Box.y);
}

void SpinBox::setCol2(const SDL_Color& col) {
    bg = col;
    thenum.setCol2(col);
    inc.setCol2(col);
    dec.setCol2(col);
    setPos(Box.x, Box.y);
}

void SpinBox::setFont(const FONT& font) {
    thenum.setFont(font);
    setPos(Box.x, Box.y);
}

FONT* SpinBox::getFont() {
    return thenum.getFont();
}

SDL_Rect* SpinBox::getBox(){
    setBox();
    return &Box;
}

SDL_Color* SpinBox::getCol1() {
    return &fg;
}

SDL_Color* SpinBox::getCol2() {
    return &bg;
}
bool is_number(const std::string& text){
    for(const char& i : text){
        if(i < 48 && i > 57)return false;
    }
    return true;
}
void SpinBox::update(InputManager& input) {
    inc.update(input);
    dec.update(input);
    thenum.update(input);
    if(!thenum.isWritingON()){
        if(inc.getclick())num++;
        else if(dec.getclick())num--;
        thenum.settext(std::to_string(num));
    }
    else{
        if(is_number(thenum.gettext())){
            num = atoi(thenum.gettext());
        }
    }
    setPos(Box.x, Box.y);
}

void SpinBox::render(SDL_Renderer* rend, int drawtype) {
    setRenCol(rend, bg);
    SDL_RenderFillRect(rend, &Box);
    setRenCol(rend, fg);
    Texture2D::drawRect(Box, rend, drawtype / 2);
    inc.render(rend, drawtype);
    dec.render(rend, drawtype);
    thenum.render(rend, drawtype);
}

SpinBox::SpinBox(orient typei) : UIelement(), thenum("0"), num(0), type(typei), Box(SDL_Rect({0, 0, 0, 0})), fg(SDL_Color({0, 0, 0, 255})), 
    bg(SDL_Color({255, 255, 255, 255})){setasType();}

void SpinBox::setType(orient typei){
    type = typei;
    setasType();
}
/*
class ColorPicker : public UIelement{

};

class DatePicker : public UIelement{

};

class ProgressBar : public UIelement{

};

class Spinner : public UIelement{

};

class Tooltip : public Label{

};

class Notification : public LabelArea{

};

class Canvas : public UIelement{

};
*/
// ImageViewer

int ImageViewer::setpath(const std::string& imgpath){
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

int ImageViewer::setpath(const char* imgpath){
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

void ImageViewer::resize(){
    if(box.w > 320)box.w /= 4;
    if(box.h > 300)box.h /= 4;
}

void ImageViewer::delTex(){
    if(texture){
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void ImageViewer::setPos(int x, int y) {
    box.x = x;
    box.y = y;
}

void ImageViewer::setCol1(const SDL_Color& col) {
    fg = col;
    return;
}

void ImageViewer::setCol2(const SDL_Color& col) {
    bg = col;
    return;
}

void ImageViewer::setFont(const FONT& font_) { 
    font = font_;
    return;
}

SDL_Rect* ImageViewer::getBox(){
    return &box;    
} 

FONT* ImageViewer::getFont(){
    return &font;
}

SDL_Color* ImageViewer::getCol1() {
    return &fg;   
}

SDL_Color* ImageViewer::getCol2() {
    return &bg;
}

void ImageViewer::render(SDL_Renderer* rend, int drawtype) {
    if(!texture){
        int type = loadImg(rend);
        if(type < 0){
            if(!font.getfont()){
                box.w = box.h = 50;
                setRenCol(rend, bg);
                SDL_RenderFillRect(rend, &box);
                setRenCol(rend, fg);
                Texture2D::drawRect(box, rend);
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
                Texture2D::drawRect(newBox, rend, font.getptsize() / 5);
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
                Texture2D::drawRect(newBox, rend, font.getptsize() / 5);
                if(!texture)uilog << " no texture to draw to\n";
            }
        }
        else{
            setquery();
            resize();
        }
    }
    if(SDL_RenderCopy(rend, texture, NULL, &box))uilog << " rendering error occured\n";
}

void ImageViewer::settext(const std::string& text) { 
    imgname = text;
}

std::string& ImageViewer::getText() {
    return imgname;
}

int ImageViewer::loadImgPath(SDL_Renderer* rend, const char* fpath){
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
            uilog << "failed: " << SDL_GetError() << std::endl;
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

int ImageViewer::loadImg(SDL_Renderer* rend){
    uilog << " ImageViewer: Image loading (from path): " << (!path.empty() ? path : "NULL") << " > ";
    if(path.empty()){
        delTex();
        uilog << " path cleared\n";
        return -1;
    }
    else if(!texture){
        texture = IMG_LoadTexture(rend, path.c_str());
        if(!texture){
            uilog << "failed: " << SDL_GetError() << std::endl;
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

void ImageViewer::setquery(){
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

const char* ImageViewer::getpath() const {
    return path.c_str();
}

const char* ImageViewer::getname() const {
    return imgname.c_str();
}

void ImageViewer::setBox(const SDL_Rect& SBox){
    box = SBox;
}

void ImageViewer::setBoxDimP(const SDL_Point& point){
    box.w = point.x;
    box.h = point.y;
}

void ImageViewer::setBoxDim(int w, int h){
    box.w = w;
    box.h = h;
}

ImageViewer::ImageViewer(): UIelement(), box(SDL_Rect{0, 0, 0, 0}), 
    font(FONT()), fg(SDL_Color{0, 0, 0, 255}), bg(SDL_Color{255, 255, 255, 255}),
    imgname(""), path(""), texture(NULL) {
    checkfile();
    uilog << " created ImageViewer\n";
}

ImageViewer::ImageViewer(const char* fpath): ImageViewer() {
    setpath(fpath);
}

ImageViewer::ImageViewer(const SDL_Rect& tbox): ImageViewer() {
    box = tbox;
}

ImageViewer::~ImageViewer(){
}

// ImageUI
int ImageUI::setpath(const std::string& fpath){
    int ret = ImageViewer::setpath(fpath); 
    if(ret != 0){
        pathholder = path;
    }
    return ret;
}

int ImageUI::setpath(const char* fpath){
    int ret = ImageViewer::setpath(fpath); 
    if(ret != 0){
        pathholder = path;
    }
    return ret;
}

void ImageUI::update(InputManager& input){
    ImageViewer::update(input);
    setpath(pathholder);
}

ImageUI::ImageUI(): ImageViewer(), pathholder(""){}
ImageUI::ImageUI(const char* fpath): ImageViewer(fpath), pathholder(fpath){}
ImageUI::ImageUI(const SDL_Rect& tbox): ImageViewer(tbox), pathholder("") {}
std::string& ImageUI::getpathholder() {
    return pathholder;
}
/*
class ListBox : public Dropdown{

};
class MultiSelect : public ListBox{

};
class AutoCompleteBox : public Dropdown{

};
*/
/*
🔹 4. Containers & Layouts
*/
/*
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
*/