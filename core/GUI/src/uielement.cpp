#include <uielement.hpp>
// UIelement implementation

// sets the position to (x, y)
void UIelement::setPos(int x, int y) {
    box.content.x = x;
    box.content.y = y;
}
// sets the foreground color to "col"
void UIelement::setfg(const SDL_Color& col) {
    fg = col;
    box.bordercol = fg;
}
// sets the background color to "col"
void UIelement::setbg(const SDL_Color& col) {
    bg = col;
    box.bgcol = bg;
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
    SDL_Rect thebox = {
        box.content.x - box.border - box.padding,
        box.content.y - box.border - box.padding,
        box.content.w + 2 * (box.border + box.padding),
        box.content.h + 2 * (box.border + box.padding)
    };
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
// returns discrete click state
bool UIelement::getclick() const {
    return isclick;
}
// returns discrete hover state
bool UIelement::gethover() const {
    return ishover;
}
// returns discrete focus state
bool UIelement::getfocus() const {
    return isfocus;
}
// returns discrete revert state
bool UIelement::getrevert() const {
    return isrevert;
}
// returns discrete current state
bool UIelement::getcurrent() const {
    return iscurrent;
}
// returns discrete revert state
bool UIelement::getstate() const {
    return statechanged;
}
// returns discrete click state reference
bool& UIelement::getclick() {
    return isclick;
}
// returns discrete hover state reference
bool& UIelement::gethover() {
    return ishover;
}
// returns discrete focus state reference
bool& UIelement::getfocus() {
    return isfocus;
}
// returns discrete revert state reference
bool& UIelement::getrevert() {
    return isrevert;
}
// returns discrete current state reference
bool& UIelement::getcurrent() {
    return iscurrent;
}
// returns discrete state state reference
bool& UIelement::getstate() {
    return statechanged;
}
// updates the UI element state based on input
void UIelement::update(InputManager& input) {
    ishovered(input);
    if(ishover){
        isfocus = true;
        if(input.isMousePressed(SDL_BUTTON_LEFT)){
            statechanged = true;
            isclick = true;
        } else {
            statechanged = isclick || isrevert;
            isclick = false;
            // iscurrent logic next time
        }
        isrevert = false;
    }
    else{
        isclick = false;
        if(iscurrent){
            statechanged = !isfocus; // || isfocus;
            isfocus = true;
            isrevert = false;
        } else {
            statechanged = !isrevert; // || isfocus;
            isfocus = false;
            isrevert = true;
        }
    } 
}
// renders the UI element (basic implementation)
void UIelement::render(SDL_Renderer* rend, int drawtype){
    const SDL_Rect& thebox = box.content;
    // Draw border
    if(drawtype){
        SDL_SetRenderDrawColor(rend, box.bordercol.r, box.bordercol.g, box.bordercol.b, box.bordercol.a);
        SDL_Rect borderrect = {
            thebox.x - box.border - box.padding,
            thebox.y - box.border - box.padding,
            thebox.w + 2 * (box.border + box.padding),
            thebox.h + 2 * (box.border + box.padding)
        };
        if(abs(drawtype) == 1) {
            SDL_RenderDrawRect(rend, &borderrect);
        } else if(abs(drawtype) >= 2){
            thickLineRGBA(
                rend, 
                borderrect.x, borderrect.y, 
                borderrect.x + borderrect.w, borderrect.y,
                static_cast<Uint8>(box.border), 
                box.bordercol.r, box.bordercol.g, box.bordercol.b, box.bordercol.a
            );
            thickLineRGBA(
                rend, 
                borderrect.x, borderrect.y, 
                borderrect.x, borderrect.y + borderrect.h, 
                static_cast<Uint8>(box.border), 
                box.bordercol.r, box.bordercol.g, box.bordercol.b, box.bordercol.a
            );
            thickLineRGBA(
                rend, 
                borderrect.x + borderrect.w, 
                borderrect.y, borderrect.x + borderrect.w, 
                borderrect.y + borderrect.h, 
                static_cast<Uint8>(box.border), 
                box.bordercol.r, box.bordercol.g, box.bordercol.b, box.bordercol.a
            );
            thickLineRGBA(
                rend, 
                borderrect.x, 
                borderrect.y + borderrect.h, 
                borderrect.x + borderrect.w, 
                borderrect.y + borderrect.h, 
                static_cast<Uint8>(box.border), 
                box.bordercol.r, box.bordercol.g, box.bordercol.b, box.bordercol.a
            );
        }
        if(drawtype < 0){
            // Fill background
            SDL_SetRenderDrawColor(rend, box.bgcol.r, box.bgcol.g, box.bgcol.b, box.bgcol.a);
            SDL_RenderFillRect(rend, &borderrect);
        }
    }
    // draw content here (to be implemented by derived classes)
    // add padding support later
}

// End of UIelement implementation