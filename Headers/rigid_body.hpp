string body_list[8] = 
        {
            "Lower bod.png",
            "Lower leg.png",
            "Upper leg.png",
            "Upper bod.png",
            "Lower arm.png",
            "Upper arm.png",
            "Head.png",
            "Feet.png"
        };
class doll
{
    public:
        physx_body body[8];
        /*
        * 0 - lower body
        * 1 - lower leg
        * 2 - upper leg
        * 3 - upper body
        * 4 - lower arm
        * 5 - upper arm
        * 6 - head
        * 7 - feet
        */
       doll(){}
       doll(string folderpath, SDL_Renderer* rend){
        for(int i = 0; i < 8; i++)
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
        body[0].set_center_of_mass();
        body[3].set_center_of_mass();
        body[6].set_center_of_mass();
        body[3].setphysx();
        body[6].Position = Vflt2(body[3].image.get_cenpos().x + head_distance * cos(torad(90 + body[3].angle)), body[3].image.get_cenpos().y  - head_distance * sin(torad(90 + body[3].angle)));
        //body[6].Position = Vflt2(body[3].image.get_cenpos().x, body[3].image.get_cenpos().y);
        // body[6].angle = body[3].angle;
        body[6].setphysx();
        body[5].Center_of_mass = Vflt2(21, 10);
        body[5].Position = Vflt2(body[3].image.get_cenpos().x + arm_distance * cos(torad(90 + body[3].angle)), body[3].image.get_cenpos().y  - arm_distance * sin(torad(90 + body[3].angle)));
        // body[5].angle = body[3].angle;
        body[5].setphysx();
        body[0].Position = Vflt2(body[3].image.get_cenpos().x + tors_distance * cos(torad(-90 + body[3].angle)), body[3].image.get_cenpos().y  - tors_distance * sin(torad(-90 + body[3].angle)));
        // body[0].angle = body[3].angle;
        body[0].setphysx();
        body[4].Center_of_mass = Vflt2(12.5, 10);
        body[4].Position = Vflt2(body[5].image.get_cenpos().x + low_arm * cos(torad(-90 + body[5].angle)), body[5].image.get_cenpos().y  - low_arm * sin(torad(-90 + body[5].angle)));
        body[4].angle = body[5].angle;
        body[4].setphysx();
        body[2].Center_of_mass = Vflt2(19.5, 10);
        body[2].Position = Vflt2(body[0].image.get_cenpos().x, body[0].image.get_cenpos().y);
        // body[2].angle = body[0].angle;
        body[2].setphysx();
        body[1].Center_of_mass = Vflt2(16, 10);
        body[1].Position = Vflt2(body[2].image.get_cenpos().x + low_leg * cos(torad(-90 + body[2].angle)), body[2].image.get_cenpos().y  - low_leg * sin(torad(-90 + body[2].angle)));
        // body[1].angle = body[2].angle;
        body[1].setphysx();
        body[7].Center_of_mass = Vflt2(10, 10.5);
        body[7].Position = Vflt2(body[1].image.get_cenpos().x + feet * cos(torad(-90 + body[1].angle)), body[1].image.get_cenpos().y  - feet * sin(torad(-90 + body[1].angle)));
        body[7].angle = body[1].angle;
        body[7].setphysx();
       }
       void setbody(){
        tighten();
        for(int i = 0; i < 8; i++)body[i].setphysx();
       }
       void draw(){
        for(int i = 0; i < 8; i++)body[i].draw();
       }
};