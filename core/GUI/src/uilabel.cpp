#include <uilabel.hpp>
// UIlabel implementation

UIlabel::UIlabel(const std::string& txt, FONT* fnt)
    : text(txt), font(fnt), board(nullptr) {
    // Initial rendering of the label
    if (font) {
        // board = font->renderTextToTexture(text);
    }
}

// sets the text of the label
void UIlabel::setText(const std::string& txt) {
    text = txt;
    if (font) {
        // board = font->renderTextToTexture(text);
    }
}
// gets the text of the label
std::string UIlabel::getText() const {
    return text;
}
// sets the position of the label
void UIlabel::setPos(int x, int y) {
    box.getContentBox().x = x;
    box.getContentBox().y = y;
}
// gets the font of the label
FONT* UIlabel::getFont() {
    return font;
}
// updates the label (e.g., for hover effects)
void UIlabel::update(InputManager& input) {
    UIelement::update(input);
    // Additional update logic if needed
}
// renders the label
void UIlabel::render(SDL_Renderer* rend, int drawtype) {
    if (board) {
        // Render the texture at the position defined by box
        // SDL_RenderCopy(rend, board, NULL, &box.getSDLRect());
    }
}
// sets the font of the label
void UIlabel::setFont(FONT* fnt) {
    font = fnt;
    if (font) {
        // board = font->renderTextToTexture(text);
    }
}
// destructor
UIlabel::~UIlabel() {
    if (board) {
        SDL_DestroyTexture(board);
    }
}