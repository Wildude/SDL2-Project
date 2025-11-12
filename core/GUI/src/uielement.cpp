#include <uielement.hpp>
// UIelement implementation

// sets the position to (x, y)
void UIelement::setPos(int x, int y) {
    SDL_Rect& contentBox = box.getContentBox();
    contentBox.x = x;
    contentBox.y = y;
}
// sets the foreground color to "col"
void UIelement::setfg(const SDL_Color& col) {
    fg = col;
}
// sets the background color to "col"
void UIelement::setbg(const SDL_Color& col) {
    bg = col;
}
// returns a pointer to the foreground color
SDL_Color* UIelement::getfg() {
    return &fg;
}
// returns a pointer to the background color
SDL_Color* UIelement::getbg() {
    return &bg;
}
// returns a pointer to the font (pure virtual, must be implemented by derived classes)
// virtual FONT* UIelement::getFont() = 0; // Pure virtual, not implemented here

// returns a pointer to the SimpleBox
SimpleBox* UIelement::getBox() {
    return &box;
}

// checks if the element is clicked
bool UIelement::isclicked(InputManager& input){
    isclick = ishovered(input) && input.isMousePressed(SDL_BUTTON_LEFT);
    return isclick;
}
// checks if the element is hovered
bool UIelement::ishovered(InputManager& input)  {
    SDL_Rect thebox = box.getBox();
    ishover = SDL_PointInRect(&input.getMouseP(), &thebox);
    return ishover;
}
// checks if the element is on focus
bool UIelement::isfocused(InputManager& input) {
    isfocus = ishovered(input) || iscurrent;
    return isfocus;
}
// checks if the element is reverted
bool UIelement::isreverted(InputManager& input) {
    // Implementation for isreverted goes here
    if(isclicked(input) || ishovered(input) || isfocused(input)) {
        isrevert = false;
    }
    else isrevert = true;
    return isrevert;
}
// updates the UI element state based on input
void UIelement::update(InputManager& input) {
    ishovered(input);
    if(ishover){
        statechanged = !isfocus; // || isrevert;
        isfocus = true;
        isrevert = false;
        if(input.isMousePressed(SDL_BUTTON_LEFT)){
            statechanged = !isclick;
            isclick = true;
        } else {
            statechanged = isclick; //|| true;
            isclick = false;
            // iscurrent logic next time
        }
    }
    else{
        isclick = false;
        if(iscurrent){
            statechanged = !iscurrent; // || isfocus;
            isfocus = true;
            isrevert = false;
        } else {
            statechanged = !isrevert; // || isfocus;
            isfocus = false;
            isrevert = true;
        }
    } 
}

// virtual void UIelement::render(SDL_Renderer* rend, int drawtype) = 0; // Pure virtual, not implemented here

// End of UIelement implementation