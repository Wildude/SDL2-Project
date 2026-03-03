#pragma once
#include "textbox.hpp"
#include <vector>
class TextList{
    //improved from vector (12 bytes) to nodestack (8 bytes)
    //nodestack<TextBox> boxes;
    std::vector<TextBox> boxes;
    int xpos, ypos; // 4 bytes
    // total = 12 bytes
    public:
    TextList();
    TextList(const std::vector<TextBox>& texts, int x, int y = 0);
    void setpos(int x, int y = 0);
    void setup();
    void add(const char* txt, FONT* font = NULL, SDL_Color* col1 = NULL, SDL_Color* col2 = NULL);
    void add(std::string txt);
    void add();
    void draw(SDL_Renderer* rend, short drawtype = 2);
    void drawi(int i, SDL_Renderer* rend, SDL_Texture* board, short drawtype = 2);
    void edit(const char* text, int i = 0);
    const std::vector<TextBox>& getBoxes();
    /*
    nodestack<TextBox> getBoxes();
    */
};