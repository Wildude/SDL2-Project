string body_list[13] = 
        {
            "Lower bod.png",
            "Lower legR.png",
            "Upper legR.png",
            "Lower legL.png",
            "Upper legL.png",
            "Upper bod.png",
            "Lower armR.png",
            "Upper armR.png",
            "Lower armL.png",
            "Upper armL.png",
            "Head.png",
            "FeetR.png",
            "FeetL.png"
        };
class doll
{
    public:
        physx_body body[13];
        /*
        * 0 - lower body
        * 1 - lower leg R
        * 2 - upper leg R
        * 3 - lower leg L
        * 4 - upper leg L
        * 5 - upper body
        * 6 - lower arm R
        * 7 - upper arm R
        * 8 - lower arm L
        * 9 - upper arm L
        * 10 - head
        * 11 - feet R
        * 12 - feet L
        */
       doll(){}
       doll(string folderpath, SDL_Renderer* rend){
        for(int i = 0; i < 13; i++)
        {
            string folder = folderpath;
            folder += body_list[i];
            body[i].image.copy(TEXTURE(folder.c_str(), rend));
            body[i].queryset();
        }
       }
       void fix(){
        body[3].Position = Vflt2(320, 240);
        body[3].setphysx();
        body[6].Position = Vflt2(body[3].image.get_cenpos().x, body[3].image.get_cenpos().y - 51);
        body[6].setphysx();
       }
       void tighten(){
        float head_distance = 57;
        float arm_distance = 30;
        float tors_distance = 53;
        float low_arm = 55;
        float low_leg = 60;
        float feet = 70;
       }
       void setbody(){
        tighten();
        for(int i = 0; i < 8; i++)body[i].setphysx();
       }
       void draw(){
        for(int i = 0; i < 8; i++)body[i].draw();
       }
};