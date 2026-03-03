// simplest type of 2D animation
#include <iostream>
// spriteClass

class Sprite {
    std::string imgpath;
    // Texture imgatlas;
    public:
    Sprite();
    Sprite(const std::string&);
    //
    void setDim(int, int);
    // ...
};
