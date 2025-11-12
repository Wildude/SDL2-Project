#include <uicontainer.hpp>
// UIcontainer implementation

// sets the container type
void UIcontainer::setType(UIContainerType type) {
    contype = type;
}
// gets the container type
UIContainerType UIcontainer::getType() const {
    return contype;
}  
// sets the width of the container
void UIcontainer::setW(int w) {
    box.getContentBox().w = w;
    // don't forget to update box
}
// sets the height of the container
void UIcontainer::setH(int h) {
    box.getContentBox().h = h;
    // don't forget to update box
}
// sets both width and height of the container
void UIcontainer::setWH(int w, int h) {
    box.getContentBox().w = w;
    box.getContentBox().h = h;
    // don't forget to update box
}
// adds a UIelement to the container
void UIcontainer::push(UIelement* element) {
    elements.push_back(element);
    // don't forget to update layout
}
// removes a UIelement from the container
void UIcontainer::pop(UIelement* element) {
    // find and remove the element
    // don't forget to update layout
}
// gets the UIelement at the specified index
UIelement* UIcontainer::getAt(int index) {
    if(index < 0 || index >= static_cast<int>(elements.size())) {
        return nullptr; // or handle error as appropriate throws
    }
    return elements[index];
}
// returns the size of the container
size_t UIcontainer::getSize() const {
    return elements.size();
}
// sets the position of the container and updates child elements
void UIcontainer::setPos(int x, int y) {
    SDL_Rect& contentBox = box.getContentBox();
    contentBox.x = x;
    contentBox.y = y;
    // Update positions of child elements based on container type
    int offsetX = x;
    int offsetY = y;
    for(auto& element : elements) {
        element->setPos(offsetX, offsetY);
        if(contype == UIC_VERTICAL) {
            offsetY += element->getBox()->getBox().h; // Stack vertically
        } else if(contype == UIC_HORIZONTAL) {
            offsetX += element->getBox()->getBox().w; // Stack horizontally
        }
    }
}
// gets the font used by the container (returns the font of the first element)
FONT* UIcontainer::getFont() {
    if(!elements.empty()) {
        return elements[0]->getFont();
    }
    return nullptr; // or a default font
}
// updates the container and its child elements
void UIcontainer::update(InputManager& input) {
    UIelement::update(input);
    for(auto& element : elements) {
        element->update(input);
    }
}
// renders the container and its child elements
void UIcontainer::render(SDL_Renderer* rend, int drawtype) {
    // Render the container itself if needed
    for(auto& element : elements) {
        element->render(rend, drawtype);
    }
}