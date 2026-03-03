#include <ui_inputbox.hpp>
// UIinputbox implementation

UIinputbox::UIinputbox(const std::string& txt, FONT* fnt)
    : text(txt), font(fnt), board(nullptr), inputhandler() {
    // Create a texture for the input box background (board)
    // Placeholder implementation
    // board = SDL_CreateTexture(/* renderer */, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 40);
}
// sets the text of the input box
void UIinputbox::setText(const std::string& txt) {
    text = txt;
}
// gets the text of the input box
std::string UIinputbox::getText() const {
    return text;
}
// sets the position of the input box
void UIinputbox::setPos(int x, int y) {
    box.content.x = x;
    box.content.y = y;
}
// gets the font of the input box
FONT* UIinputbox::getFont() {
    return font;
}
// updates the input box (handles text input)
void UIinputbox::update(InputManager& input) {
    //inputhandler.handleInput(input, text);
}
// renders the input box
void UIinputbox::render(SDL_Renderer* rend, int drawtype) {
    // Render the board texture
    SDL_RenderCopy(rend, board, nullptr, &box.content);
    // Render the text inside the input box
    // Placeholder implementation for text rendering
}
// sets the font of the input box
void UIinputbox::setFont(FONT* fnt) {
    font = fnt;
}
// destructor for UIinputbox
UIinputbox::~UIinputbox() {
    if (board) {
        SDL_DestroyTexture(board);
    }
}
