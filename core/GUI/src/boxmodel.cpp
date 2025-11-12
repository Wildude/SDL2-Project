#include <boxmodel.hpp>
void SimpleBox::setContentBox(const SDL_Rect& box) {
    content = box;
}
SDL_Rect& SimpleBox::getContentBox() {
    return content;
}
void SimpleBox::setBorderColor(const SDL_Color& col) {
    bordercol = col;
}
SDL_Color& SimpleBox::getBorderColor() {
    return bordercol;
}
void SimpleBox::setBackgroundColor(const SDL_Color& col) {
    bgcol = col;
}
SDL_Color& SimpleBox::getBackgroundColor() {
    return bgcol;
}
