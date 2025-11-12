#include <uitextswitch.hpp>

// UItextswitch implementation

UItextswitch::UItextswitch(FONT* fnt) : font(fnt), currentindex(0), inc(UIBT_INCREMENT), dec(UIBT_DECREMENT) {
    setAtlas();
}

// adds an option to the text switcher
void UItextswitch::push(const std::string& option) {
    options.push_back(option);
    setAtlas();
}
// removes an option from the text switcher
void UItextswitch::pop(const std::string& option) {
    // removes option if it exists
    setAtlas();
}
// sets the current option by index
void UItextswitch::setCurrent(int index) {
    if (index >= 0 && index < static_cast<int>(options.size())) {
        currentindex = index;
    }
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
    box.getContentBox().x = x;
    box.getContentBox().y = y;
    // Position inc and dec buttons accordingly
}
// gets the font of the text switcher
FONT* UItextswitch::getFont() {
    return font;
}
// updates the text switcher state based on input
void UItextswitch::update(InputManager& input) {
    inc.update(input);
    dec.update(input);
    if (inc.isclicked(input)) {
        if (currentindex < static_cast<int>(options.size()) - 1) {
            currentindex++;
        }
    }
    if (dec.isclicked(input)) {
        if (currentindex > 0) {
            currentindex--;
        }
    }
}
// renders the text switcher
void UItextswitch::render(SDL_Renderer* rend, int drawtype) {
    // Render the current option text
    inc.render(rend, drawtype);
    dec.render(rend, drawtype);
}
// gets the number of options in the text switcher
size_t UItextswitch::getSize() const {
    return options.size();
}
// destructor
UItextswitch::~UItextswitch() {
    if (atlas) {
        SDL_DestroyTexture(atlas);
    }
}