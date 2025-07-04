// body[Upper_bod].Velocity.getmag() / 5
/*
 * Upper bod and head are centers of the body
 * Upper bod has center: (w/2, 11h/19)
 * Head has center: (w/2, h/2)
 * Lower bod >>: (w/2, h/2)
 * Lower leg >>: ()
 * Lower arm >>: (9w/19, 3h/100)
 * Upper leg >>: ()
 * Upper arm >>: (w/2, 2h/5)
 * Feet >>:
 */
/*
ofstream fileR("../Files/Data/Rigid_body.txt"), fileL("../Files/Data/Rigid_bodyL.txt");
const char* body_list[15] = 
{
    "Lower bod",
    "Lower legR",
    "Upper legR",
    "Lower legL",
    "Upper legL",
    "Upper bod",
    "Lower armR",
    "Upper armR",
    "Lower armL",
    "Upper armL",
    "Head",
    "FeetR",
    "FeetL",
    "HandL",
    "HandR"
};
enum bodynums{
    Lower_bod = 0,
    Lower_legR,
    Upper_legR,
    Lower_legL,
    Upper_legL,
    Upper_bod,
    Lower_armR,
    Upper_armR,
    Lower_armL,
    Upper_armL,
    Head,
    FeetR,
    FeetL,
    HandL,
    HandR
};
enum LoR{
    RIGHT = 0,
    LEFT
};
// a ragdoll player mechanics system 
class ragdoll
{
    // uses a single picture as a texture atlas
    SDL_Texture* atlas;
    SDL_Rect clip[15];
    public:
    void parse(const char* filepath){
        // parse image, uv dimensions, coordinates and centers from file
    }
};
*/