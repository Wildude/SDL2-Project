#include <uitextswitch.hpp>

// UItextswitch implementation

UItextswitch::UItextswitch(FONT* fnt) : currentindex(-1), atlas("", fnt), inc(UIBT_INCREMENT), dec(UIBT_DECREMENT) {
    
}

// adds an option to the text switcher
void UItextswitch::push(const std::string& option) {
    options.push_back(option);
}
// removes an option from the text switcher
void UItextswitch::pop(const std::string& option) {
    // removes option if it exists
}
// sets the current option by index
void UItextswitch::setCurrent(int index) {
    if (index >= 0 && index < static_cast<int>(options.size())) {
        currentindex = index;
    }
    // update atlas
}
// gets the current option index
int UItextswitch::getCurrent() const {
    return currentindex;
}
// gets the current option string
std::string UItextswitch::getCurrentOption() const {
    if (options.empty()) return "";
    return options[currentindex];
}
// sets the position of the text switcher
void UItextswitch::setPos(int x, int y) {
    box.content.x = x;
    box.content.y = y;
    SDL_Point theboxpos = {
        x + box.margin + box.border + box.padding,
        y + box.margin + box.border + box.padding
    };
    // Position inc and dec buttons accordingly
    inc.setPos(theboxpos.x, theboxpos.y);
    atlas.setPos(theboxpos.x + inc.getBox()->getBox().x, theboxpos.y);
    dec.setPos(theboxpos.x + atlas.getBox()->getBox().x, theboxpos.y);
}
// gets the font of the text switcher
FONT* UItextswitch::getFont() {
    return atlas.getFont();
}
// updates the text switcher state based on input
void UItextswitch::update(InputManager& input) {
    inc.update(input);
    dec.update(input);
    if (inc.isclicked(input)) {
        currentindex++;
        if(currentindex > options.size() - 1) currentindex = 0;
        atlas.setText(options[currentindex]);
    }
    else if (dec.isclicked(input)) {
        currentindex--;
        if (currentindex < 0) currentindex = options.size() - 1;
        atlas.setText(options[currentindex]);
    }
}
// renders the text switcher
void UItextswitch::render(SDL_Renderer* rend, int drawtype) {
    UIelement::render(rend, drawtype);
    // Render the current option text
    inc.render(rend, drawtype);
    atlas.render(rend, drawtype);
    dec.render(rend, drawtype);
}
// gets the number of options in the text switcher
size_t UItextswitch::getSize() const {
    return options.size();
}
// destructor
UItextswitch::~UItextswitch() {
    
}