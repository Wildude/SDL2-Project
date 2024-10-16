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
class simpledoll{
    public:
    physx_body body[15];
    simpledoll(){}
    void rescale_body(){
        
        body[Lower_bod].image.magnify(112/110, 10/19);

        body[Upper_armL].image.magnify(0.5, 95/190);
        body[Upper_armR].image.magnify(0.5, 95/190);

        body[Lower_armL].image.magnify(0.25, 95/190);
        body[Lower_armR].image.magnify(0.25, 95/190);

        body[Upper_legL].image.magnify(57/110, 95/190);
        body[Upper_legR].image.magnify(57/110, 95/190);

        body[Lower_legL].image.magnify(36/110, 95/190);
        body[Lower_legR].image.magnify(36/110, 95/190);

        body[FeetL].image.magnify(63/110, 37/190);
        body[FeetR].image.magnify(63/110, 37/190);
        
        body[HandL].image.magnify(35/110, 56/190);
        body[HandR].image.magnify(35/110, 56/190);

    }
    void queryset(){
        body[Head].queryset();
        body[Upper_bod].queryset();

        body[Lower_bod].queryset();

        body[Upper_armL].queryset();
        body[Upper_armR].queryset();

        body[Lower_armL].queryset();
        body[Lower_armR].queryset();

        body[Upper_legL].queryset();
        body[Upper_legR].queryset();

        body[Lower_legL].queryset();
        body[Lower_legR].queryset();

        body[FeetL].queryset();
        body[FeetR].queryset();

        body[HandL].queryset();
        body[HandR].queryset();
    }
    void setcms(){
        body[Lower_bod].set_center_of_mass(Vflt2(0.5 * body[Lower_bod].Dimension.getx(), 0.1 * body[Lower_bod].Dimension.gety()));

        body[Upper_armL].set_center_of_mass(Vflt2(0.5 * body[Upper_armL].Dimension.getx(), 0.1 * body[Upper_armL].Dimension.gety()));
        body[Upper_armR].set_center_of_mass(Vflt2(0.5 * body[Upper_armR].Dimension.getx(), 0.1 * body[Upper_armR].Dimension.gety()));

        body[Lower_armL].set_center_of_mass(Vflt2(0.5 * body[Lower_armL].Dimension.getx(), 0.1 * body[Lower_armL].Dimension.gety()));
        body[Lower_armR].set_center_of_mass(Vflt2(0.5 * body[Lower_armR].Dimension.getx(), 0.1 * body[Lower_armR].Dimension.gety()));

        body[Upper_legL].set_center_of_mass(Vflt2(0.5 * body[Upper_legL].Dimension.getx(), 0.1 * body[Upper_legL].Dimension.gety()));
        body[Upper_legR].set_center_of_mass(Vflt2(0.5 * body[Upper_legR].Dimension.getx(), 0.1 * body[Upper_legR].Dimension.gety()));

        body[Lower_legL].set_center_of_mass(Vflt2(0.5 * body[Lower_legL].Dimension.getx(), 0.1 * body[Lower_legL].Dimension.gety()));
        body[Lower_legR].set_center_of_mass(Vflt2(0.5 * body[Lower_legR].Dimension.getx(), 0.1 * body[Lower_legR].Dimension.gety()));

        body[FeetL].set_center_of_mass(Vflt2(0.5 * body[FeetL].Dimension.getx(), 0.1 * body[FeetL].Dimension.gety()));
        body[FeetR].set_center_of_mass(Vflt2(0.5 * body[FeetR].Dimension.getx(), 0.1 * body[FeetR].Dimension.gety()));

        body[HandL].set_center_of_mass(Vflt2(0.5 * body[HandL].Dimension.getx(), 0.1 * body[HandL].Dimension.gety()));
        body[HandR].set_center_of_mass(Vflt2(0.5 * body[HandR].Dimension.getx(), 0.1 * body[HandR].Dimension.gety()));
    }
    simpledoll(SDL_Renderer* rend){
        SDL_Surface* surf = SDL_CreateRGBSurface(0, 1, 1, 8, 0, 0, 0, 0);
        for(int i = 0; i < 15; i++)body[i].image.surfcpy(surf, rend);
        body[Head].image.magnify(3);
        body[Upper_bod].image.magnify(33/5, 57/5);
        rescale_body();
        queryset();
        setcms();
    }
    void magnify(float x, float y = -1){
        y = (y <= 0 ? x : y);
        body[Head].image.magnify(x, y);
        body[Upper_bod].image.magnify((11/5) * x, (19/5) * y);
        rescale_body();
        queryset();
        setcms();
    }
    void tighten(){
        body[Head].Position = 
        Vflt2(
            body[Upper_bod].image.get_cenpos().x 
            + 
            body[Upper_bod].Dimension.gety()/1.5* cos(torad(body[Upper_bod].angle + 90)), 
            body[Upper_bod].image.get_cenpos().y
            - 
            body[Upper_bod].Dimension.gety()/1.5 * sin(torad(body[Upper_bod].angle + 90))
        );
        body[Lower_bod].Position = 
        Vflt2
        (
            body[Upper_bod].image.get_cenpos().x 
            + 
            body[Upper_bod].Dimension.gety()/4 * cos(torad(body[Upper_bod].angle - 90)), 
            body[Upper_bod].image.get_cenpos().y
            - 
            body[Upper_bod].Dimension.gety()/4 * sin(torad(body[Upper_bod].angle - 90))

        );
        body[Upper_armL].Position = body[Upper_bod].portion(150);
        body[Upper_armR].Position = body[Upper_bod].portion(30);
        //
        body[Upper_legL].Position = body[Lower_bod].portion(235);
        body[Upper_legR].Position = body[Lower_bod].portion(305);
        //
        body[Lower_armL].Position = 
        Vflt2
        (
            body[Upper_armL].Position.getx() + (60/95) * body[Upper_armL].Dimension.gety() * cos(torad(body[Upper_armL].angle - 90))
            ,
            body[Upper_armL].Position.gety() - (60/95) * body[Upper_armL].Dimension.gety() * sin(torad(body[Upper_armL].angle - 90))
        );
        body[Lower_armR].Position = 
        Vflt2
        (
            body[Upper_armR].Position.getx() + (60/95) * body[Upper_armR].Dimension.gety() * cos(torad(body[Upper_armR].angle - 90))
            ,
            body[Upper_armR].Position.gety() - (60/95) * body[Upper_armR].Dimension.gety() * sin(torad(body[Upper_armR].angle - 90))
        );
        body[Lower_legR].Position = 
        Vflt2
        (
            body[Upper_legR].Position.getx() + (65/95) * body[Upper_legL].Dimension.gety() * cos(torad(body[Upper_legR].angle - 90))
            ,
            body[Upper_legR].Position.gety() - (65/95) * body[Upper_legL].Dimension.gety() * sin(torad(body[Upper_legR].angle - 90))
        );
        body[Lower_legL].Position = 
        Vflt2
        (
            body[Upper_legL].Position.getx() + (65/95) * body[Upper_legL].Dimension.gety() * cos(torad(body[Upper_legL].angle - 90))
            ,
            body[Upper_legL].Position.gety() - (65/95) * body[Upper_legL].Dimension.gety() * sin(torad(body[Upper_legL].angle - 90))
        );
        body[HandL].Position =
            Vflt2
        (
            body[Lower_armL].Position.getx() + (80/95) * body[Lower_armL].Dimension.getx() * cos(torad(body[Lower_armL].angle - 90))
            ,
            body[Lower_armL].Position.gety() - (80/95) * body[Lower_armL].Dimension.getx() * sin(torad(body[Lower_armL].angle - 90))
        );
        body[HandR].Position =
            Vflt2
        (
            body[Lower_armR].Position.getx() + (80/95) * body[Lower_armR].Dimension.getx() * cos(torad(body[Lower_armR].angle - 90))
            ,
            body[Lower_armR].Position.gety() - (80/95) * body[Lower_armR].Dimension.getx() * sin(torad(body[Lower_armR].angle - 90))
        );
        body[FeetL].Position = 
        Vflt2
        (
            body[Lower_legL].image.get_cenpos().x 
            + 
            (89/95) * body[Lower_legL].Dimension.getx() * cos(torad(body[Lower_legL].angle - 90)), 
            body[Lower_legL].image.get_cenpos().y
            - 
            (89/95) * body[Lower_legL].Dimension.getx() * sin(torad(body[Lower_legL].angle - 90))
        );
        body[FeetR].Position = 
        Vflt2
        (
            body[Lower_legR].image.get_cenpos().x 
            + 
            (89/95) * body[Lower_legR].Dimension.getx() * cos(torad(body[Lower_legR].angle - 90)), 
            body[Lower_legR].image.get_cenpos().y
            - 
            (89/95) * body[Lower_legR].Dimension.getx() * sin(torad(body[Lower_legR].angle - 90))
        );
    }
    void setbody(){
        // tighten();
    }
    void draw(){
        tighten();
        //for(int i = 0; i < 2; i++)body[i].draw();
        body[Upper_armR].draw();
        body[Upper_bod].draw();
        body[Lower_bod].draw();
        body[Head].draw();
        body[Upper_armL].draw();
        body[Lower_armL].draw();
        body[Lower_armR].draw();
        body[HandL].draw();
        body[HandR].draw();
        body[Upper_legL].draw();
        body[Upper_legR].draw();
        body[Lower_legL].draw();
        body[Lower_legR].draw();
        body[FeetL].draw();
        body[FeetR].draw();
    }
};
class doll
{
    public:
        physx_body body[15];
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
        * 13 - hand L
        * 14 - hand R
        */
       doll(){}
       doll(string folderpath, SDL_Renderer* rend){
        /*
        for(int i = 0; i < 13; i++)
        {
            string folder = folderpath;
            folder += body_list[i];
            body[i].image.copy(TEXTURE(folder.c_str(), rend));
            body[i].queryset();
        }
        */
        body[Head].image.copy(TEXTURE((folderpath + "head.png").c_str(), rend));
        //
        body[Upper_bod].image.copy(TEXTURE((folderpath + "upper bod.png").c_str(), rend));
        //
        body[Upper_armL].image.copy(TEXTURE((folderpath + "upper armL.png").c_str(), rend));
        body[Upper_armR].image.copy(TEXTURE((folderpath + "upper armR.png").c_str(), rend));
        //
        body[Lower_armL].image.copy(TEXTURE((folderpath + "lower armL.png").c_str(), rend));
        body[Lower_armR].image.copy(TEXTURE((folderpath + "lower armR.png").c_str(), rend));
        //
        body[HandL].image.copy(TEXTURE((folderpath + "hand L.png").c_str(), rend));
        body[HandR].image.copy(TEXTURE((folderpath + "hand R.png").c_str(), rend));
        //
        body[Upper_legL].image.copy(TEXTURE((folderpath + "upper legL.png").c_str(), rend));
        body[Upper_legR].image.copy(TEXTURE((folderpath + "upper legR.png").c_str(), rend));
        //
        body[Lower_bod].image.copy(TEXTURE((folderpath + "lower bod.png").c_str(), rend));
        //
        body[Lower_bod].queryset();
        //
        body[Lower_legL].image.copy(TEXTURE((folderpath + "lower legL.png").c_str(), rend));
        body[Lower_legR].image.copy(TEXTURE((folderpath + "lower legR.png").c_str(), rend));
        //
        body[Lower_legL].queryset();
        body[Lower_legR].queryset();
        //
        body[FeetL].image.copy(TEXTURE((folderpath + "feet L.png").c_str(), rend));
        body[FeetR].image.copy(TEXTURE((folderpath + "feet R.png").c_str(), rend));
        //
        body[FeetL].queryset();
        body[FeetR].queryset();
        //
        body[Upper_legL].queryset();
        body[Upper_legR].queryset();
        //
        body[HandL].queryset();
        body[HandR].queryset();
        //
        body[Lower_armL].queryset();
        body[Lower_armR].queryset();
        //
        body[Upper_armL].queryset();
        body[Upper_armR].queryset();
        //
        body[Upper_bod].queryset();
        //
        body[Head].queryset();
        //
        body[Upper_armL].set_center_of_mass(Vflt2(27, 20));
        body[Upper_armR].set_center_of_mass(Vflt2(27, 20));
        //
        body[Upper_legL].set_center_of_mass(Vflt2(28, 17));
        body[Upper_legR].set_center_of_mass(Vflt2(28, 17));
        //
        body[Lower_armR].set_center_of_mass(Vflt2(13, 5));
        body[Lower_armL].set_center_of_mass(Vflt2(13, 5));
        //
        body[Lower_legR].set_center_of_mass(Vflt2(18, 5));
        body[Lower_legL].set_center_of_mass(Vflt2(18, 5));
        //
        body[HandR].set_center_of_mass(Vflt2(17, 5));
        body[HandL].set_center_of_mass(Vflt2(17, 5));
        //
        body[Lower_bod].set_center_of_mass(Vflt2(56, 10));
        //
        body[FeetL].set_center_of_mass(Vflt2(15, 15));
        body[FeetR].set_center_of_mass(Vflt2(15, 15));
        //
        body[Head].setphysx();
        body[Upper_bod].setphysx();
        body[Upper_armL].setphysx();
        body[Lower_armL].setphysx();
        body[Lower_armR].setphysx();
        body[HandL].setphysx();
        body[HandR].setphysx();
       }
       void tighten(){
        body[Head].Position = 
        Vflt2(
            body[Upper_bod].image.get_cenpos().x 
            + 
            body[Upper_bod].Dimension.gety()/2 * cos(torad(body[Upper_bod].angle + 90)), 
            body[Upper_bod].image.get_cenpos().y
            - 
            body[Upper_bod].Dimension.gety()/2 * sin(torad(body[Upper_bod].angle + 90))
        );
        body[Upper_armL].Position = body[Upper_bod].portion(150);
        body[Upper_armR].Position = body[Upper_bod].portion(30);
        //
        body[Lower_armL].Position = 
        Vflt2
        (
            body[Upper_armL].Position.getx() + 60 * cos(torad(body[Upper_armL].angle - 90))
            ,
            body[Upper_armL].Position.gety() - 60 * sin(torad(body[Upper_armL].angle - 90))
        );
        body[Lower_armR].Position = 
        Vflt2
        (
            body[Upper_armR].Position.getx() + 60 * cos(torad(body[Upper_armR].angle - 90))
            ,
            body[Upper_armR].Position.gety() - 60 * sin(torad(body[Upper_armR].angle - 90))
        );
        body[Lower_legR].Position = 
        Vflt2
        (
            body[Upper_legR].Position.getx() + 65 * cos(torad(body[Upper_legR].angle - 90))
            ,
            body[Upper_legR].Position.gety() - 65 * sin(torad(body[Upper_legR].angle - 90))
        );
        body[Lower_legL].Position = 
        Vflt2
        (
            body[Upper_legL].Position.getx() + 65 * cos(torad(body[Upper_legL].angle - 90))
            ,
            body[Upper_legL].Position.gety() - 65 * sin(torad(body[Upper_legL].angle - 90))
        );
        body[HandL].Position =
         Vflt2
        (
            body[Lower_armL].Position.getx() + 80 * cos(torad(body[Lower_armL].angle - 90))
            ,
            body[Lower_armL].Position.gety() - 80 * sin(torad(body[Lower_armL].angle - 90))
        );
        body[HandR].Position =
         Vflt2
        (
            body[Lower_armR].Position.getx() + 80 * cos(torad(body[Lower_armR].angle - 90))
            ,
            body[Lower_armR].Position.gety() - 80 * sin(torad(body[Lower_armR].angle - 90))
        );
        body[Lower_bod].Position = 
        Vflt2
        (
            body[Upper_bod].image.get_cenpos().x 
            + 
            body[Upper_bod].Dimension.gety()/4 * cos(torad(body[Upper_bod].angle - 90)), 
            body[Upper_bod].image.get_cenpos().y
            - 
            body[Upper_bod].Dimension.gety()/4 * sin(torad(body[Upper_bod].angle - 90))

        );
        body[FeetL].Position = 
        Vflt2
        (
            body[Lower_legL].image.get_cenpos().x 
            + 
            89 * cos(torad(body[Lower_legL].angle - 90)), 
            body[Lower_legL].image.get_cenpos().y
            - 
            89 * sin(torad(body[Lower_legL].angle - 90))

        );
        body[FeetR].Position = 
        Vflt2
        (
            body[Lower_legR].image.get_cenpos().x 
            + 
            89 * cos(torad(body[Lower_legR].angle - 90)), 
            body[Lower_legR].image.get_cenpos().y
            - 
            89 * sin(torad(body[Lower_legR].angle - 90))

        );
        body[Upper_legL].Position = body[Lower_bod].portion(235);
        body[Upper_legR].Position = body[Lower_bod].portion(305);
       }
       void setbody(){
        // tighten();
       }
       void draw(){
        tighten();
        //for(int i = 0; i < 2; i++)body[i].draw();
        body[Upper_armR].draw();
        body[Upper_bod].draw();
        body[Lower_bod].draw();
        body[Head].draw();
        body[Upper_armL].draw();
        body[Lower_armL].draw();
        body[Lower_armR].draw();
        body[HandL].draw();
        body[HandR].draw();
        body[Upper_legL].draw();
        body[Upper_legR].draw();
        body[Lower_legL].draw();
        body[Lower_legR].draw();
        body[FeetL].draw();
        body[FeetR].draw();
       }
};