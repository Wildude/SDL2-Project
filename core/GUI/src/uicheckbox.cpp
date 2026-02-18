#include <uicheckbox.hpp>
// UIcheckbox implementation

UIcheckbox::UIcheckbox(UICheckboxType type)
    : checkboxType(type), checked(false) {
    // Constructor implementation
}
// sets the checked state of the checkbox
void UIcheckbox::setChecked(bool state) {
    checked = state;
}
// returns whether the checkbox is checked
bool UIcheckbox::isChecked() const {
    return checked;
}
// sets the position of the checkbox
void UIcheckbox::setPos(int x, int y) {
    box.content.x = x;
    box.content.y = y;
}
// gets the font of the checkbox
FONT* UIcheckbox::getFont() {
    // Placeholder implementation, return a default font
    return nullptr;
}
// updates the checkbox (handles hover, click states)
void UIcheckbox::update(InputManager& input) {
    // Call base class update to handle state changes
    UIelement::update(input);
    // Additional checkbox-specific update logic can go here
}
// renders the checkbox
void UIcheckbox::render(SDL_Renderer* rend, int drawtype) {
    // Render the checkbox based on its state (checked/unchecked)
    // Placeholder implementation for rendering
}
// destructor for UIcheckbox
UIcheckbox::~UIcheckbox() {
    // Destructor implementation
}
