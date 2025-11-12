#include <uislider.hpp>
// UIslider implementation

UIslider::UIslider(short portion) : portion(portion) {
    // Constructor implementation
}

// sets the slider's value (0-100)
void UIslider::setValue(int val) {
    if (val < 0) val = 0;
    if (val > 100) val = 100;
    portion = static_cast<short>(val);
}
// gets the slider's value (0-100)
int UIslider::getValue() const {
    return static_cast<int>(portion);
}
// sets the position of the slider
void UIslider::setPos(int x, int y) {
    box.getContentBox().x = x;
    box.getContentBox().y = y;
}
// gets the font of the slider (NULL)
FONT* UIslider::getFont() {
    // Return a pointer to the font used by the slider
    return nullptr; // Placeholder
}
// updates the slider state based on input
void UIslider::update(InputManager& input) {
    // Update logic for the slider
}
// renders the slider
void UIslider::render(SDL_Renderer* rend, int drawtype) {
    // Rendering logic for the slider
}
// destructor
UIslider::~UIslider() {
    // Cleanup if necessary
}