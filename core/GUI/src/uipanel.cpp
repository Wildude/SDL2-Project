#include <uipanel.hpp>
// UIpanel implementation

// sets the width of the panel
void UIpanel::setW(int w) {
    box.content.w = w;
    // don't forget to update box
}
// sets the height of the panel
void UIpanel::setH(int h) {
    box.content.h = h;
    // don't forget to update box
}
// sets both width and height of the panel
void UIpanel::setWH(int w, int h) {
    box.content.w = w;
    box.content.h = h;
    // don't forget to update box
}
// adds a UIelement to the panel
void UIpanel::push(UIelement* element) {
    elements.push_back(element);
    // don't forget to update layout
}
// removes a UIelement from the panel
void UIpanel::pop(UIelement* element) {
    // find and remove the element
    // don't forget to update layout
}
// gets the UIelement at the specified index
UIelement* UIpanel::getAt(int index) {
    if(index < 0 || index >= static_cast<int>(elements.size())) {
        return nullptr; // or handle error as appropriate throws
    }
    return elements[index];
}
// returns the size of the panel
size_t UIpanel::getSize() const {
    return elements.size();
}
// sets the position of the panel and updates child elements
void UIpanel::setPos(int x, int y) {
    SDL_Rect& contentBox = box.content;
    contentBox.x = x;
    contentBox.y = y;
    // Update positions of child elements
    int offsetX = x;
    int offsetY = y;
    for(auto& element : elements) {
        element->setPos(offsetX, offsetY);
        offsetY += element->getBox()->getBox().h; // Stack vertically
    }
}
// returns a pointer to the font (for panel, we can return nullptr or a default font)
FONT* UIpanel::getFont() {
    if(!elements.empty()) {
        return elements[0]->getFont();
    }
    return nullptr; // or a default font
}
// updates the panel and its child elements
void UIpanel::update(InputManager& input) {
    UIelement::update(input);
    // Update all child elements
    for(auto& element : elements) {
        element->update(input);
    }
}
// renders the panel and its child elements
void UIpanel::render(SDL_Renderer* rend, int drawtype) {
    // Render the panel itself (background, border, etc.) based on drawtype
    SDL_Rect panelBox = box.getBox();
    if(drawtype & 1) { // Draw background
        SDL_SetRenderDrawColor(rend, box.bgcol.r, box.bgcol.g, box.bgcol.b, box.bgcol.a);
        SDL_RenderFillRect(rend, &panelBox);
    }
    if(drawtype & 2) { // Draw border
        SDL_SetRenderDrawColor(rend, box.bordercol.r, box.bordercol.g, box.bordercol.b, box.bordercol.a);
        for(int i = 0; i < box.border; ++i) {
            SDL_Rect borderRect = {panelBox.x - i, panelBox.y - i, panelBox.w + 2 * i, panelBox.h + 2 * i};
            SDL_RenderDrawRect(rend, &borderRect);
        }
    }
    // Render all child elements
    for(auto& element : elements) {
        element->render(rend, drawtype);
    }
}