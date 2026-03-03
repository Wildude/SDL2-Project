#include <boxmodel.hpp>
// Simple box implementations
// returns the total box (content + padding + border + margin)
SDL_Rect SimpleBox::getBox() const {
    SDL_Rect box;
    box.x = content.x - padding - border - margin;
    box.y = content.y - padding - border - margin;
    box.w = content.w + 2 * (padding + border + margin);
    box.h = content.h + 2 * (padding + border + margin);
    return box;
}
// Dynamic box implementations

// assigns the content box to "box"
// also updates the padding, border, and margin boxes accordingly
void DynamicBox::setContentBox(const SDL_Rect& box) {
    contentBox = box;
}
// returns a reference to the content box
SDL_Rect& DynamicBox::getContentBox() {
    return contentBox;
}

// returns a const reference to the content box
const SDL_Rect& DynamicBox::getContentBox() const {
    return contentBox;
}

// sets the border color to "col"
void DynamicBox::setBorderColor(const SDL_Color& col) {
    bordercol = col;
}
// returns a reference to the border color
SDL_Color& DynamicBox::getBorderColor() {
    return bordercol;
}

// returns a const reference to the border color
const SDL_Color& DynamicBox::getBorderColor() const {
    return bordercol;
}

// sets the background color to "col"
void DynamicBox::setBackgroundColor(const SDL_Color& col) {
    bgcol = col;
}
// returns a reference to the background color
SDL_Color& DynamicBox::getBackgroundColor() {
    return bgcol;
}

// returns a const reference to the background color
const SDL_Color& DynamicBox::getBackgroundColor() const {
    return bgcol;
}

// sets the border box dimensions
void DynamicBox::setBorder(int x, int y, int w, int h) {
    borderBox = {x != -1 ? x : borderBox.x,
                 y != -1 ? y : borderBox.y,
                 w != -1 ? w : borderBox.w,
                 h != -1 ? h : borderBox.h};
}
// returns a reference to the border box
SDL_Rect& DynamicBox::getBorder() {
    return borderBox;
}

// returns a const reference to the border box
const SDL_Rect& DynamicBox::getBorder() const {
    return borderBox;
}

// sets the padding box dimensions
void DynamicBox::setPadding(int x, int y, int w, int h) {
    paddingBox = {x != -1 ? x : paddingBox.x,
                  y != -1 ? y : paddingBox.y,
                  w != -1 ? w : paddingBox.w,
                  h != -1 ? h : paddingBox.h};
}
// returns a reference to the padding box
SDL_Rect& DynamicBox::getPadding() {
    return paddingBox;
}

// returns a const reference to the padding box
const SDL_Rect& DynamicBox::getPadding() const {
    return paddingBox;
}

// sets the margin box dimensions
void DynamicBox::setMargin(int x, int y, int w, int h) {
    marginBox = {x != -1 ? x : marginBox.x,
                 y != -1 ? y : marginBox.y,
                 w != -1 ? w : marginBox.w,
                 h != -1 ? h : marginBox.h};
}
// returns a reference to the margin box
SDL_Rect& DynamicBox::getMargin() {
    return marginBox;
}

// returns a const reference to the margin box
const SDL_Rect& DynamicBox::getMargin() const {
    return marginBox;
}
// returns the total box (margin box)
SDL_Rect DynamicBox::getBox() const {
    return marginBox;
}
