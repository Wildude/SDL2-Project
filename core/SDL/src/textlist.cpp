#include "../include/textlist.hpp"
TextList::TextList(){}
TextList::TextList(const std::vector<TextBox>& texts, int x, int y )
{
    for(size_t i = 0; i < texts.size(); i++)boxes.push_back(texts[i]);
    xpos = x;
    ypos = y;
    setup();
}
void TextList::setpos(int x, int y ){
    xpos = x;
    ypos = y;
    setup();
}
void TextList::setup()
{
    int size = boxes.size();
    for(int i = 0; i < size; i++){
        boxes[i].setboxpos(xpos, i ? boxes[i - 1].getBox().y + boxes[i - 1].getBox().h : ypos);
    }
    // below is a nodestack implementation
    /*
        Lnode<TextBox>* curr = boxes.peek();
        Lnode<TextBox>* prev = NULL;
        if(!curr)return;
        // maybe check for previous push operation to save time used for traversal
        while(curr){
            curr->id.setboxpos(xpos, prev ? prev->id.getBox().h : 0);
            prev = curr;
            curr = curr->next;
        }
    */
}
void TextList::add(const char* txt, FONT* font , SDL_Color* col1 , SDL_Color* col2 ){
    int w, h;
    int size = boxes.size();
    // the following implementation has nodestack adaptations as well
    if(!font){
        if(size/*boxes.peek()*/){
            font = new FONT(boxes[size - 1]/*boxes.peek()->id*/.getFont());
        }
        else font = new FONT();
    }
    font->TEXT_size(txt, &w, &h);
    if(!col1){
        if(size/*boxes.peek()*/)
            col1 = &boxes[size - 1]/*boxes.peek()->id*/.getCol1(); // hmmm
        else col1 = new SDL_Color({0, 0, 0, 0});
    }
    if(!col2)
        col2 = new SDL_Color({
            (Uint8)(255 - col1->r), 
            (Uint8)(255 - col1->g), 
            (Uint8)(255 - col1->b), 
            (Uint8)(255 - col1->a)
        });
    int yoffset = (
        size /*boxes.peek()*/ ? 
        boxes[size - 1]/*boxes.peek()->id*/.getBox().y + boxes[size - 1]/*boxes.peek()->id*/.getBox().h 
        : ypos
    );
    TextBox tbox(txt, *font);
    tbox.setboxpos(xpos, yoffset);
    tbox.setcol1(col1->r, col1->g, col1->b, col1->a);
    tbox.setcol2(col2->r, col2->g, col2->b, col2->a);
    boxes.push_back(tbox);
    //boxes.push(tbox);
}
void TextList::add(std::string txt){return add(txt.c_str());}
void TextList::add(){return add("");}
void TextList::draw(SDL_Renderer* rend, short drawtype ){
    // has nodestack impns
    int size = boxes.size();
    for(int i = 0; i < size; i++){
        SDL_Texture* board = NULL;
        boxes[i].draw(rend, board, drawtype);
    }
    /*
    Lnode<TextBox>* curr = boxes.peek();
    while(curr){
        SDL_Texture* board;
        curr->id.draw(rend, board, drawtype);
        curr = curr->next;
    }
    */
}
void TextList::drawi(int i, SDL_Renderer* rend, SDL_Texture* board, short drawtype ){
    boxes[i].draw(rend, board, drawtype);
    /*
    Lnode<TextBox>* head = boxes.peek();
    Lnode<TextBox>* curr = nextNode(head, i);
    curr->id.draw(rend, board, drawtype);
    */
}
void TextList::edit(const char* text, int i ){
    boxes[i].settext(text);
}
const std::vector<TextBox>& TextList::getBoxes(){
    return boxes;
}
/*
nodestack<TextBox> TextList::getBoxes(){
    return boxes;
}
*/