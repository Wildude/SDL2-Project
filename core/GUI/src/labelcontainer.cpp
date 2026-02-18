#include <labelcontainer.hpp>
// UIlabelcontainer implementation

// constructor
UIlabelcontainer::UIlabelcontainer(UIlabelContainerType type) : contype(type) {
    // initialize container type
}


// sets the width of the label container
void UIlabelcontainer::setW(int w) {
    box.content.w = w;
}

// sets the height of the label container
void UIlabelcontainer::setH(int h) {
    box.content.h = h;
}

// sets both width and height of the label container
void UIlabelcontainer::setWH(int w, int h) {
    box.content.w = w;
    box.content.h = h;
}

// sets the type of the label container
void UIlabelcontainer::setType(UIlabelContainerType type) {
    contype = type;
}   
// gets the type of the label container
UIlabelContainerType UIlabelcontainer::getType() const {
    return contype;
}
// pushes a label into the container
void UIlabelcontainer::push(UIlabel* label) {
    labels.push_back(label);
    // set the position of the new label accordingly
    SDL_Point contentpos = {
        box.content.x + box.margin + box.border + box.padding,
        box.content.y + box.margin + box.border + box.padding
    };
    if(labels.size() == 1) {
        label->setPos(contentpos.x, contentpos.y);
    } else {
        if (contype == UILC_VERTICAL) {
            label->setPos(contentpos.x, labels.back()->getBox()->getBox().y + labels.back()->getBox()->getBox().h);
        } else if (contype == UILC_HORIZONTAL) {
            label->setPos(labels.back()->getBox()->getBox().x + labels.back()->getBox()->getBox().w, contentpos.y);
        }
    }
}
// pops a label from the container
void UIlabelcontainer::pop(UIlabel* label) {
    // removes the first occurrence of the label
}
// sets the position of the label container and its labels
void UIlabelcontainer::setPos(int x, int y) {
    box.content.x = x;
    box.content.y = y;
    int offsetx = x + box.margin + box.border + box.padding;
    int offsety = y + box.margin + box.border + box.padding;
    for (auto& label : labels) {
        label->setPos(offsetx, offsety);
        if (contype == UILC_VERTICAL) {
            offsety += label->getBox()->getBox().h;
        } else if (contype == UILC_HORIZONTAL) {
            offsetx += label->getBox()->getBox().w;
        }
    }
}
// gets the font of the label container (returns the font of the first label)
FONT* UIlabelcontainer::getFont() {
    if (!labels.empty()) {
        return labels[0]->getFont();
    }
    return nullptr;
}
// updates the label container and its labels
void UIlabelcontainer::update(InputManager& input) {
    UIelement::update(input);
    if(labels.empty() || !isfocus) return;
    for (auto& label : labels) {
        label->update(input);
    }
}
// renders the label container and its labels
void UIlabelcontainer::render(SDL_Renderer* rend, int drawtype) {
    UIelement::render(rend, drawtype);
    if(labels.empty()) return;
    // scroll implementation later
    for (auto& label : labels) {
        label->render(rend, drawtype);
    }
}
// gets the label at the specified index
UIlabel* UIlabelcontainer::getAt(int index) {
    if (index >= 0 && index < static_cast<int>(labels.size())) {
        return labels[index];
    }
    return nullptr;
}
// gets the size of the label container
size_t UIlabelcontainer::getSize() const {
    return labels.size();
}

// UIClabel implementation  

// sets the atlas texture for the labels
void UIClabel::setAtlas() {
    // implementation to create atlas texture from labels
}

// sets the type of the label container
void UIClabel::setType(UIlabelContainerType type) {
    contype = type;
}

// gets the type of the label container
UIlabelContainerType UIClabel::getType() const {
    return contype;
}
// pushes a label string into the container
void UIClabel::push(const std::string& label) {
    labels.push_back(label);
    setAtlas();
}
// pops a label string from the container
void UIClabel::pop(const std::string& label) {
    // removes the first occurrence of the label string
    setAtlas();
}
// sets the position of the label container and its labels
void UIClabel::setPos(int x, int y) {
    box.content.x = x;
    box.content.y = y;
    int offsetx = x;
    int offsety = y;
    for (const auto& label : labels) {
        // Assuming each label has a fixed height and width for simplicity
        int labelWidth = 100; // Placeholder value
        int labelHeight = 20; // Placeholder value
        if (contype == UILC_VERTICAL) {
            offsety += labelHeight;
        } else if (contype == UILC_HORIZONTAL) {
            offsetx += labelWidth;
        }
    }
}
// gets the font of the label container
FONT* UIClabel::getFont() {
    return font;
}
// updates the label container
void UIClabel::update(InputManager& input) {
    // Update logic if needed
}
// renders the label container
void UIClabel::render(SDL_Renderer* rend, int drawtype) {
    // Render the atlas texture
}
// gets the label string at the specified index
std::string UIClabel::getAt(int index) {
    if (index >= 0 && index < static_cast<int>(labels.size())) {
        return labels[index];
    }
    return "";
}
// gets the size of the label container
size_t UIClabel::getSize() const {
    return labels.size();
}

