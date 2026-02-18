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
    box.content.w = w;
}
// sets the height of the container
void UIcontainer::setH(int h) {
    box.content.h = h;
}
// sets both width and height of the container
void UIcontainer::setWH(int w, int h) {
    box.content.w = w;
    box.content.h = h;
}
// adds a UIelement to the container
void UIcontainer::push(UIelement* element) {
    elements.push_back(element);
    // update position based on container type
    if(elements.size() == 1) {
        element->setPos(box.content.x, box.content.y);
        box.content.w = element->getBox()->content.w;
        box.content.h = element->getBox()->content.h;
        std::cout << " size 1 set\n";
    } else {
        if (contype == UIC_VERTICAL) {
            std::cout << " vertical setting\n";
            element->setPos(
                box.content.x, 
                elements.back()->getBox()->getBox().y 
                + 
                elements.back()->getBox()->getBox().h
            );
            int wid = 0;
            for(UIelement* ui : elements){
                wid = std::max(wid, ui->getBox()->getBox().w);
            }
            box.content.w = wid;
            box.content.h += element->getBox()->content.h;
        } else if (contype == UIC_HORIZONTAL) {
            element->setPos(
                elements.back()->getBox()->getBox().x
                + 
                elements.back()->getBox()->getBox().w, 
                box.content.y
            );
            int hei = 0;
            for(UIelement* ui : elements){
                hei = std::max(hei, ui->getBox()->getBox().h);
            }
            box.content.h = hei;
            box.content.w += elements.back()->getBox()->getBox().w;
        }
        // for scroll based containers
        /*
        int wid = 0, hei = 0;
        for(UIelement* ui : elements){
            wid = std::max(wid, ui->getBox()->getBox().w);
            hei = std::max(hei, ui->getBox()->getBox().h);
        }
        */
        //
    }
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
    box.content.x = x;
    box.content.y = y;
    // Update positions of child elements based on container type
    int offsetX = x + box.margin + box.border + box.padding;
    int offsetY = y + box.margin + box.border + box.padding;
    if(contype == UIC_VERTICAL) {
        for(auto& element : elements){
            element->setPos(offsetX, offsetY);
            offsetY += element->getBox()->content.h; // Stack vertically
        }
    }
    else if(contype == UIC_HORIZONTAL) {
        for(auto& element : elements){
            element->setPos(offsetX, offsetY);
            offsetX += element->getBox()->content.w; // Stack horizontally
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
    if(elements.empty() || contype == UIC_FIXED || !isfocus) {
        return; // No layout update needed
    }
    for(auto& element : elements) {
        element->update(input);
        if(isrevert){
            if(!element->getrevert()){
                element->getstate() = true;
                element->getrevert() = true;
            }
        }
    }
}
// renders the container and its child elements
void UIcontainer::render(SDL_Renderer* rend, int drawtype) {
    // Render the container itself if needed
    UIelement::render(rend, drawtype);
    // Render child elements
    // scroll implementation later
    for(auto& element : elements) {
        element->render(rend, drawtype);
    }
}


