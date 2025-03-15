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
class sprite
{
    SDL_Texture* image;
    SDL_FPoint clip;
    public:
    sprite(const SDL_FPoint& portion)
    {
        clip = portion;
    }
    void setimage(const char* path){
        image = IMG_LoadTexture(NULL, path);
    }
    void animate(){
        // 
    }
};
class ragdoll
{
    // scale is assumed to be according to a standard 640 x 480 screen
    map<const char*, SDL_Texture*> parts;
    public:
    ragdoll(){
        for(int i = 0; i < 15; i++)parts[body_list[i]] = NULL;
    }
    void setImage(int i, const char* path){
        //
    }
    void draw(SDL_Renderer* rend){
        for(int i = 0; i < 15; i++){
            SDL_RenderCopy(rend, parts[body_list[i]], NULL, NULL);
        }
    }
};