#include <uilabel.hpp>
// UIlabel implementation

UIlabel::UIlabel(const std::string& txt, FONT* fnt)
    : text(txt), font(fnt), board(nullptr), qual(UILABEL_QUALITY_BLENDED) {
    // Initial rendering of the label
    if (font) {
        if(text != "")font->TEXT_size(text.c_str(), &box.content.w, &box.content.h);
    }
}

// sets the quality of the label
void UIlabel::setQual(UILabelQuality quality){
    if(qual != quality){
        statechanged = true;
        qual = quality;
    }
}

// gets the quality of the label
UILabelQuality UIlabel::getQual(){
    return qual;
}

// sets the text of the label
void UIlabel::setText(const std::string& txt) {
    if(text == txt)return;
    text = txt;
    if (font) {
        if(text != "")font->TEXT_size(text.c_str(), &box.content.w, &box.content.h);
    }
}
// gets the text of the label
std::string UIlabel::getText() const {
    return text;
}
// sets the position of the label
void UIlabel::setPos(int x, int y) {
    box.content.x = x;
    box.content.y = y;
}
// gets the font of the label
FONT* UIlabel::getFont() {
    return font;
}
// updates the label (e.g., for hover effects)
void UIlabel::update(InputManager& input) {
    UIelement::update(input);
    // re-draw on texture upon state change
    if(statechanged){
        if (board) {
            SDL_DestroyTexture(board);
            board = nullptr;
        }
    }
}
// renders the label
void UIlabel::render(SDL_Renderer* rend, int drawtype) {
    UIelement::render(rend, drawtype);
    SDL_Rect thebox = {
        box.content.x,
        box.content.y,
        box.content.w,
        box.content.h
    };
    if (board) {
        // Render the texture at the position defined by box
        SDL_RenderCopy(rend, board, NULL, &thebox);
    }
    else{
        // Create texture from text
        // include UIe identification rendering later
        if(font && text != ""){
            board = SDL_CreateTextureFromSurface(rend, renderText(font->getfont(), text.c_str(), fg, bg, (int)qual));
            // Render the newly created texture
            if(board){
                SDL_RenderCopy(rend, board, NULL, &thebox);
            }
        }
    }
}
// sets the font of the label
void UIlabel::setFont(FONT* fnt) {
    font = fnt;
    if (font) {
        if(text != "")font->TEXT_size(text.c_str(), &box.content.w, &box.content.h);
    }
}
// destructor
UIlabel::~UIlabel() {
    if (board) {
        SDL_DestroyTexture(board);
    }
}