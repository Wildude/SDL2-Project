#include <uitab.hpp>
// UItab implementation

UItab::UItab() : currenttab(-1), tablabels(UILC_HORIZONTAL) {
    // default constructor
}

// pushes a new tab page
void UItab::push(UIcontainer* page) {
    if (page) {
        tabpages.push_back(page);
        tablabels.push(new UIlabel("tab" + std::to_string(tabpages.size()), font)); // Add corresponding tab label
        if (currenttab == -1) {
            currenttab = 0; // Set the first tab as current
        }
        // first set the tablabels position
        SDL_Point contentpos = {
            box.content.x + box.margin + box.border + box.padding,
            box.content.y + box.margin + box.border + box.padding
        };
        tablabels.getAt(tabpages.size() - 1)->setPos(contentpos.x, contentpos.y);
        // now set the UIcontainer position
        tabpages.back()->setPos(contentpos.x, contentpos.y + tablabels.getBox()->getBox().h);
    }
}

// pops a tab page
void UItab::pop(UIcontainer* page) {
    // removes a tab page
    /*
    UIcontainer* container = dynamic_cast<UIcontainer*>(page);
    if (container) {
        auto it = std::find(tabpages.begin(), tabpages.end(), container);
        if (it != tabpages.end()) {
            tabpages.erase(it);
            if (currenttab >= static_cast<int>(tabpages.size())) {
                currenttab = static_cast<int>(tabpages.size()) - 1; // Adjust current tab index
            }
        }
    }
    */
}
// sets the current tab by index
void UItab::setCurrent(int index) {
    if (index >= 0 && index < static_cast<int>(tabpages.size())) {
        currenttab = index;
    }
    // throw exception otherwise
}
// gets the current tab index
int UItab::getCurrent() const {
    return currenttab;
}
// gets the current tab page
UIelement* UItab::getCurrentTab() {
    if (currenttab >= 0 && currenttab < static_cast<int>(tabpages.size())) {
        return tabpages[currenttab];
    }
    // throw exception otherwise
}
// sets the position of the tab element
void UItab::setPos(int x, int y) {
    // set the UItab position
    box.content.x = x;
    box.content.y = y;
    SDL_Point contentpos = {
        box.content.x + box.margin + box.border + box.padding,
        box.content.y + box.margin + box.border + box.padding
    };
    // set position for the uilabelcontainer
    tablabels.setPos(contentpos.x, contentpos.y);
    // Set position for the tabpage(s)
    // set the position for all tab pages
    for (auto& page : tabpages) {
        page->setPos(contentpos.x, contentpos.y + tablabels.getBox()->getBox().h);
    }
}
// gets the font used by the tab element
FONT* UItab::getFont() {
    // Return font from the current tab page if available
    UIelement* currentPage = getCurrentTab();
    if (currentPage) {
        return currentPage->getFont();
    }
    return nullptr;
}
// updates the tab element
void UItab::update(InputManager& input) {
    UIelement::update(input);
    if(currenttab < 0 || !isfocus) return;
    // update the uilabelpanels and change the current tab (if needed)
    tablabels.update(input);
    if(tablabels.getfocus())
    for(int i = 0; i < tablabels.getSize(); i++){
        if(tablabels.getAt(i)->isclicked(input)){
            if(i != currenttab) setCurrent(i);
            break;
        }
    }
    // Update the current tab page
    UIelement* currentPage = getCurrentTab();
    if (currentPage) {
        currentPage->update(input);
    }
}
// renders the tab element
void UItab::render(SDL_Renderer* rend, int drawtype) {
    UIelement::render(rend, drawtype);
    if(currenttab < 0) return;
    // Render the uilabelpanels
    tablabels.render(rend, drawtype);
    // scroll implementation later
    // Render the current tab page
    getCurrentTab()->render(rend, drawtype);
}