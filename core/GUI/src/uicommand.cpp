#include <uicommand.hpp>
// UIcommand implementation

// clone is a pure virtual function in the base class UIcommand
// execute too is a pure virtual function in the base class UIcommand

// UIMultiCommand implementations

UIMultiCommand::UIMultiCommand(std::vector<UIcommand*>& cmds)
    : commands(cmds) {
    // Constructor implementation
}

// Push a command by reference
void UIMultiCommand::push(UIcommand& cmd) {
    commands.push_back(&cmd);
}
// Push a command by pointer
void UIMultiCommand::push(UIcommand* cmd) {
    commands.push_back(cmd);
}
// Get command at index
UIcommand*& UIMultiCommand::getcmd(int index) {
    return commands.at(index);
}
// clone method
UIMultiCommand* UIMultiCommand::clone() const {
    return new UIMultiCommand(*this);
}
// Destructor
UIMultiCommand::~UIMultiCommand() {
    // Destructor implementation
}
// Execute all commands
void UIMultiCommand::execute(UIelement* ref) {
    for (auto& cmd : commands) {
        cmd->execute(ref);
    }
}

// UIColor implementations

UIColor::UIColor()
    : newbg({0, 0, 0, 255}), newfg({255, 255, 255, 255}) {
    // Default constructor
}

UIColor::UIColor(const SDL_Color& nfg, const SDL_Color& nbg)
    : newbg(nbg), newfg(nfg) {
    // Parameterized constructor
}

// Set new colors
void UIColor::setNew(const SDL_Color& bnew, const SDL_Color& fnew) {
    newbg = bnew;
    newfg = fnew;
}   
// Clone method
UIColor* UIColor::clone() const {
    return new UIColor(*this);
}
// Execute method to change colors of the UIelement
void UIColor::execute(UIelement* ref) {
    if (ref) {
        ref->setbg(newbg);
        ref->setfg(newfg);
    }
}
// Destructor
UIColor::~UIColor() {
    // Destructor implementation
}

// UIFont implementations
UIFont::UIFont()
    : newfont(FONT()) {
    // Default constructor
}

UIFont::UIFont(const FONT& font)
    : newfont(font) {
    // Constructor from FONT
}
// Set new font
void UIFont::setNew(const FONT& font) {
    newfont = font;
}
// Clone method
UIFont* UIFont::clone() const {
    return new UIFont(*this);
}
// Execute method to change font of the UIelement
void UIFont::execute(UIelement* ref) {
    if (ref) {
        // Assuming UIelement has a method to set its font
        // This is a placeholder; actual implementation may vary
        FONT* theFont = ref->getFont();
        if(theFont){
            *theFont = newfont;
        }
    }
}

