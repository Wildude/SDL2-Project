#include <uibutton.hpp>
// UIbutton implementation

UIbutton::UIbutton(UIButtonType type)
    : buttontype(type) {
    // Constructor implementation
}
// sets the position of the button
void UIbutton::setPos(int x, int y) {
    box.getContentBox().x = x;
    box.getContentBox().y = y;
}
// gets the font of the button
FONT* UIbutton::getFont() {
    // Placeholder implementation, return a default font
    return nullptr;
}
// updates the button (handles hover, click states)
void UIbutton::update(InputManager& input) {
    // Call base class update to handle state changes
    UIelement::update(input);
    // Additional button-specific update logic can go here
}
// renders the button
void UIbutton::render(SDL_Renderer* rend, int drawtype) {
    // Render the button background and text based on its state
    // Placeholder implementation for rendering
}
// destructor for UIbutton
UIbutton::~UIbutton() {
    // Destructor implementation
}
