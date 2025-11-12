#include <uitab.hpp>
// UItab implementation

UItab::UItab() : currenttab(-1) {
}

// pushes a new tab page
void UItab::push(UIelement* page) {
    UIcontainer* container = dynamic_cast<UIcontainer*>(page);
    if (container) {
        tabpages.push_back(container);
        if (currenttab == -1) {
            currenttab = 0; // Set the first tab as current
        }
    }
}
// pops a tab page
void UItab::pop(UIelement* page) {
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
    return nullptr;
}
// sets the position of the tab element
void UItab::setPos(int x, int y) {
    // Set position for the tab element itself
    this->box.getContentBox().x = x;
    this->box.getContentBox().y = y;
    // Optionally, set position for the current tab page
    UIelement* currentPage = getCurrentTab();
    if (currentPage) {
        currentPage->setPos(x, y);
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
    // Update the current tab page
    UIelement* currentPage = getCurrentTab();
    if (currentPage) {
        currentPage->update(input);
    }
}
// renders the tab element
void UItab::render(SDL_Renderer* rend, int drawtype) {
    // Render the current tab page
    UIelement* currentPage = getCurrentTab();
    if (currentPage) {
        currentPage->render(rend, drawtype);
    }
}