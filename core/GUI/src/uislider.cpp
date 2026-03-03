#include <uislider.hpp>
#include <texture2D.hpp>
// UIslider implementation

UIslider::UIslider(short portion) : portion(portion) {
    // Constructor implementation
}

// sets the slider type
void UIslider::setType(UIsliderType t) {
    if(type != t){
        if(
            (type == UISL_DEFAULT 
            && t == UISL_VERTICAL)
            ||
            (type == UISL_VERTICAL
             && t == UISL_DEFAULT)
        ){
            // swap width and height for horizontal/vertical toggle
            std::swap(box.content.w, box.content.h);
        }
        // other conversion implementations later
        type = t;
    }
    
}

// gets the slider type
UIsliderType UIslider::getType() const {
    return type;
}

// sets the slider's value (0-100)
void UIslider::setValue(int val) {
    if (val < 0) val = 0;
    if (val > 100) val = 100;
    portion = static_cast<short>(val);
}
// gets the slider's value (0-100)
int UIslider::getValue() const {
    return static_cast<int>(portion);
}
// sets the position of the slider
void UIslider::setPos(int x, int y) {
    box.content.x = x;
    box.content.y = y;
}
// gets the font of the slider (NULL)
FONT* UIslider::getFont() {
    // Return a pointer to the font used by the slider
    return nullptr; // Placeholder
}
// updates the slider state based on input
void UIslider::update(InputManager& input) {
    UIelement::update(input);
    // Update logic for the slider
}
// renders the slider
void UIslider::render(SDL_Renderer* rend, int drawtype) {
    // Rendering logic for the slider
    UIelement::render(rend, drawtype);
    // calculate percentage
    float percent = portion * 0.01f;
    SDL_Rect thebox = {
        box.content.x + box.margin + box.border + box.padding,
        box.content.y + box.margin + box.border + box.padding,
        box.content.w,
        box.content.h
    };
    switch(type){
        // default horizontal slider
        case UISL_DEFAULT:{
            // setting progress width
            int width = (int)((float)thebox.w * percent) - 1;
            if(width < 0)width = 0;
            // setting progress (internal) rectangle
            SDL_Rect boxportion = {thebox.x + 1, thebox.y + 1, width, thebox.h - 1};
            // drawing portion
            SDL_SetRenderDrawColor(rend, bg.r, bg.g, bg.b, bg.a);
            SDL_RenderFillRect(rend, &boxportion);
            // drawing border
            SDL_SetRenderDrawColor(rend, fg.r, fg.g, fg.b, fg.a);
            Texture2D::drawRect(thebox, rend, drawtype / 2);
            break;
        }
        // vertical slider
        case UISL_VERTICAL:{
            // setting progress height
            int height = (int)((float)thebox.h * percent) - 1;
            if(height < 0)height = 0;
            // setting progress (internal) rectangle
            SDL_Rect boxportion = {thebox.x + 1, thebox.y + 1 + (int)((float)thebox.h * (1.0f - percent)), thebox.w - 1, height};
            // drawing portion
            SDL_SetRenderDrawColor(rend, bg.r, bg.g, bg.b, bg.a);
            SDL_RenderFillRect(rend, &boxportion);
            // drawing border
            SDL_SetRenderDrawColor(rend, fg.r, fg.g, fg.b, fg.a);
            Texture2D::drawRect(thebox, rend, drawtype / 2);
            break;
        }
        // circular (arc) slider
        case UISL_ARC:{
            // arc implementation placeholder
            break;
        }
        // circuar gauge slider
        case UISL_GAUGE:{
            // gauge implementation placeholder
            break;
        }
    }
}
// destructor
UIslider::~UIslider() {
    // Cleanup if necessary
}