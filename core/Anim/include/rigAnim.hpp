// a rig-type animation
#include <iostream>
#include <vector>
#include <SDL.h>
// simple rig
struct rigpart{
    SDL_Rect part;
    // point of rotation
    SDL_Point por; 
    //
};
class RigDoll{
    std::vector<rigpart> parts;
    //
    public:
    // attaches the (first,) part to the (,second) part 
    void attach(int, int); 
};
