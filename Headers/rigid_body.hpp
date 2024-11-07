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
string body_list[15] = 
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
class simpledoll{
    #define ANGLINC 10.0
    public:
    physx_body body[15];
    simpledoll(){}
    void Vel(const Vflt2& velocity){
        for(int i = 0; i < 15; i++){
            body[i].Velocity = velocity;
        }
    }
    void stabilize(){
        for(int i = 0; i < 15; i++){if(i != FeetL && i != FeetR && i != Upper_bod)body[i].angle = 0; body[i].Velocity = Vflt2_0;}
    }
    void animate(){
            static bool ninreachL = false;
            static bool ninreachR = false;
            if(body[Upper_armL].angle >= 90)ninreachL = true;
            if(body[Upper_armR].angle <= -90)ninreachR = true;
            // arms
            body[Upper_armL].angle += (ninreachL ? -ANGLINC : ANGLINC);
            body[Upper_armR].angle += (ninreachR ? ANGLINC : -ANGLINC);
            body[Lower_armL].angle = body[Upper_armL].angle + 90;
            body[Lower_armR].angle = body[Upper_armR].angle + 90;
            // Legs
            static bool ninreachL_ = false;
            static bool ninreachR_ = false;
            if(body[Upper_legL].angle <= -90)ninreachR_ = true;
            if(body[Upper_legR].angle >= 90)ninreachL_ = true;
            body[Upper_legL].angle += (ninreachR_ ? ANGLINC : -ANGLINC);
            body[Upper_legR].angle += (ninreachL_ ? -ANGLINC : ANGLINC);
            body[Lower_legL].angle = body[Upper_legL].angle - 90;
            body[Lower_legR].angle = body[Upper_legR].angle - 90;
            if(body[Upper_legL].angle >= 90)ninreachR_ = false;
            if(body[Upper_legR].angle <= -90)ninreachL_ = false;
            //
            if(body[Upper_armL].angle < -90)ninreachL = false;
            if(body[Upper_armR].angle > 90)ninreachR = false;
            body[FeetL].angle = body[Lower_legL].angle;
            body[FeetR].angle = body[Lower_legR].angle;
       }
       void animate2(){
            static bool ninreachL = false;
            static bool ninreachR = false;
            if(body[Upper_armR].angle >= 90)ninreachL = true;
            if(body[Upper_armL].angle <= -90)ninreachR = true;
            // arms
            body[Upper_armL].angle += (ninreachL ? ANGLINC : -ANGLINC);
            body[Upper_armR].angle += (ninreachR ? -ANGLINC : ANGLINC);
            body[Lower_armL].angle = body[Upper_armL].angle - 90;
            body[Lower_armR].angle = body[Upper_armR].angle - 90;
            // Legs
            static bool ninreachL_ = false;
            static bool ninreachR_ = false;
            if(body[Upper_legL].angle >= 90)ninreachR_ = true;
            if(body[Upper_legR].angle <= -90)ninreachL_ = true;
            body[Upper_legL].angle += (ninreachR_ ? -ANGLINC : ANGLINC);
            body[Upper_legR].angle += (ninreachL_ ? ANGLINC : -ANGLINC);
            body[Lower_legL].angle = body[Upper_legL].angle + 90;
            body[Lower_legR].angle = body[Upper_legR].angle + 90;
            if(body[Upper_legL].angle <= -90)ninreachR_ = false;
            if(body[Upper_legR].angle >= 90)ninreachL_ = false;
            //
            if(body[Upper_armR].angle < -90)ninreachL = false;
            if(body[Upper_armL].angle > 90)ninreachR = false;
            body[FeetL].angle = body[Lower_legL].angle - 180;
            body[FeetR].angle = body[Lower_legR].angle - 180;
       }
       void animate3(){
            static bool ninreach = false;
            // Legs
            if(body[Upper_legL].angle <= -90)ninreach = true;
            body[Upper_legL].angle += (ninreach ? ANGLINC : -ANGLINC);
            body[Upper_legR].angle += (ninreach ? ANGLINC : -ANGLINC);
            body[Lower_legL].angle += (!ninreach && body[Lower_legL].angle >= body[Upper_legL].angle + 90 || ninreach && body[Lower_legL].angle <= body[Upper_legL].angle ? 0 : (ninreach ? -ANGLINC : ANGLINC));
            body[Lower_legR].angle += (!ninreach && body[Lower_legR].angle >= body[Upper_legR].angle + 90 || ninreach && body[Lower_legR].angle <= body[Upper_legR].angle ? 0 : (ninreach ? -ANGLINC : ANGLINC));
            if(body[Upper_legL].angle > 0)ninreach = false;
            body[FeetL].angle = body[Lower_legL].angle - 180;
            body[FeetR].angle = body[Lower_legR].angle - 180;
       }
       void animate4(){
            static bool ninreach = false;
            // Legs
            if(body[Upper_legL].angle >= 90)ninreach = true;
            body[Upper_legL].angle += (ninreach ? -ANGLINC : ANGLINC);
            body[Upper_legR].angle += (ninreach ? -ANGLINC : ANGLINC);
            body[Lower_legL].angle += (!ninreach && body[Lower_legL].angle <= body[Upper_legL].angle - 90 || ninreach && body[Lower_legL].angle >= body[Upper_legL].angle ? 0 : (ninreach ? ANGLINC : -ANGLINC));
            body[Lower_legR].angle += (!ninreach && body[Lower_legR].angle <= body[Upper_legR].angle - 90 || ninreach && body[Lower_legR].angle >= body[Upper_legR].angle ? 0 : (ninreach ? ANGLINC : -ANGLINC));
            if(body[Upper_legL].angle < 0)ninreach = false;
            body[FeetL].angle = body[Lower_legL].angle;
            body[FeetR].angle = body[Lower_legR].angle;
       }
    void refix(){
        if(body[Head].image.getdst().w < 3){
            for(int i = 0; i < 15; i++)body[i].image.set_dstdim(6, 6);
            rescale_body();
            setdims();
        }
    }
    void rescale_body(){
        body[Upper_bod].image.magnify(3, 4);
        body[Upper_armL].image.magnify(1, 2);
        body[Upper_armR].image.magnify(1, 2);
        body[Lower_armL].image.magnify(0.7, 2);
        body[Lower_armR].image.magnify(0.7, 2);
        body[HandL].image.magnify(0.8, 0.8);
        body[HandR].image.magnify(0.8, 0.8);
        body[Lower_bod].image.magnify(3, 2);
        body[Upper_legL].image.magnify(1.3, 2);
        body[Upper_legR].image.magnify(1.3, 2);
        body[Lower_legL].image.magnify(0.7, 2);
        body[Lower_legR].image.magnify(0.7, 2);
        body[FeetL].image.magnify(1.3, 0.7);
        body[FeetR].image.magnify(1.3, 0.7);
    }
    inline void setdims(){
        for(int i = 0; i < 15; i++)body[i].setdims();
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
    void setcenters(){
        body[Head].image.setcenter();
        body[Upper_bod].image.setcenter();
        body[Lower_bod].image.setcenter(0.5 * body[Lower_bod].image.getdst().w, 0.1 * body[Lower_bod].image.getdst().h);

        body[Upper_armL].image.setcenter(0.5 * body[Upper_armL].image.getdst().w, 0.3 * body[Upper_armL].image.getdst().h);
        body[Upper_armR].image.setcenter(0.5 * body[Upper_armR].image.getdst().w, 0.3 * body[Upper_armR].image.getdst().h);

        body[Lower_armL].image.setcenter(0.5 * body[Lower_armL].image.getdst().w, 0.17 * body[Lower_armL].image.getdst().h);
        body[Lower_armR].image.setcenter(0.5 * body[Lower_armR].image.getdst().w, 0.17 * body[Lower_armR].image.getdst().h);

        body[Upper_legL].image.setcenter(0.5 * body[Upper_legL].image.getdst().w, 0.3 * body[Upper_legL].image.getdst().h);
        body[Upper_legR].image.setcenter(0.5 * body[Upper_legR].image.getdst().w, 0.3 * body[Upper_legR].image.getdst().h);

        body[Lower_legL].image.setcenter(0.5 * body[Lower_legL].image.getdst().w, 0.17 * body[Lower_legL].image.getdst().h);
        body[Lower_legR].image.setcenter(0.5 * body[Lower_legR].image.getdst().w, 0.17 * body[Lower_legR].image.getdst().h);

        body[FeetL].image.setcenter(0.25 * body[FeetL].image.getdst().w, 0.5 * body[FeetL].image.getdst().h);
        body[FeetR].image.setcenter(0.25 * body[FeetR].image.getdst().w, 0.5 * body[FeetR].image.getdst().h);

        body[HandL].image.setcenter(0.5 * body[HandL].image.getdst().w, 0.1 * body[HandL].image.getdst().h);
        body[HandR].image.setcenter(0.5 * body[HandR].image.getdst().w, 0.1 * body[HandR].image.getdst().h);
    }
    void setcms(){
        for(int i = 0; i < 15; i++)body[i].setcm();
    }
    simpledoll(SDL_Renderer* rend){
        SDL_Surface* surf = SDL_CreateRGBSurface(0, 3, 3, 8, 0, 0, 0, 0);
        for(int i = 0; i < 15; i++)body[i].image.setren(rend);
        SDL_SetSurfaceColorMod(surf, 0, 0, 0);
        body[Head].image.surfcpy(surf); //);
        SDL_SetSurfaceColorMod(surf, 0, 0, 100);
        body[Upper_bod].image.surfcpy(surf); //);
        SDL_SetSurfaceColorMod(surf, 0, 100, 0);
        body[Lower_bod].image.surfcpy(surf); //0.5 * body[Lower_bod].image.getdst().w, 0.1 * body[Lower_bod].image.getdst().h)
        SDL_SetSurfaceColorMod(surf, 100, 50, 0);
        body[Upper_armL].image.surfcpy(surf); //0.5 * body[Upper_armL].image.getdst().w, 0.3 * body[Upper_armL].image.getdst().h);
        SDL_SetSurfaceColorMod(surf, 50, 100, 0);
        body[Upper_armR].image.surfcpy(surf); //0.5 * body[Upper_armR].image.getdst().w, 0.3 * body[Upper_armR].image.getdst().h);
        SDL_SetSurfaceColorMod(surf, 150, 50, 0);
        body[Lower_armL].image.surfcpy(surf); //0.5 * body[Lower_armL].image.getdst().w, 0.3 * body[Lower_armL].image.getdst().h);
        SDL_SetSurfaceColorMod(surf, 50, 150, 0);
        body[Lower_armR].image.surfcpy(surf); //0.5 * body[Lower_armR].image.getdst().w, 0.3 * body[Lower_armR].image.getdst().h);
        SDL_SetSurfaceColorMod(surf, 0, 100, 50);
        body[Upper_legL].image.surfcpy(surf); //0.5 * body[Upper_legL].image.getdst().w, 0.3 * body[Upper_legL].image.getdst().h);
        SDL_SetSurfaceColorMod(surf, 0, 50, 100);
        body[Upper_legR].image.surfcpy(surf); //0.5 * body[Upper_legR].image.getdst().w, 0.3 * body[Upper_legR].image.getdst().h);
        SDL_SetSurfaceColorMod(surf, 50, 0, 150);
        body[Lower_legL].image.surfcpy(surf); //0.5 * body[Lower_legL].image.getdst().w, 0.3 * body[Lower_legL].image.getdst().h);
        SDL_SetSurfaceColorMod(surf, 150, 0, 50);
        body[Lower_legR].image.surfcpy(surf); //0.5 * body[Lower_legR].image.getdst().w, 0.3 * body[Lower_legR].image.getdst().h);
        SDL_SetSurfaceColorMod(surf, 50, 200, 0);
        body[FeetL].image.surfcpy(surf); //0.25 * body[FeetL].image.getdst().w, 0.5 * body[FeetL].image.getdst().h);
        SDL_SetSurfaceColorMod(surf, 200, 50, 0);
        body[FeetR].image.surfcpy(surf); //0.25 * body[FeetR].image.getdst().w, 0.5 * body[FeetR].image.getdst().h);
        SDL_SetSurfaceColorMod(surf, 0, 50, 200);
        body[HandL].image.surfcpy(surf); //0.5 * body[HandL].image.getdst().w, 0.1 * body[HandL].image.getdst().h);
        SDL_SetSurfaceColorMod(surf, 0, 200, 50);
        body[HandR].image.surfcpy(surf); //0.5 * body[HandR].image.getdst().w, 0.1 * body[HandR].image.getdst().h);
        queryset();
        setdims();
        rescale_body();
        setcenters();
        setdims();
        setcms();
    }
    void magnify(float x, float y = -1){
        y = (y <= 0 ? x : y);
        for(int i = 0; i < 15; i++)body[i].magnify(x, y);
        refix();
        setcenters();
        setcms();
    }
    void tighten(){
        body[Head].Position = 
        Vflt2(
            body[Upper_bod].Position.getx()
            + 
            body[Upper_bod].Dimension.gety()/1.7 * cos(torad(body[Upper_bod].angle + 90)), 
            body[Upper_bod].Position.gety()
            - 
            body[Upper_bod].Dimension.gety()/1.7 * sin(torad(body[Upper_bod].angle + 90))
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
        body[Upper_armL].Position = body[Upper_bod].portion(135);
        body[Upper_armR].Position = body[Upper_bod].portion(45);
        /*
        body[Upper_armL].Position = 
        Vflt2
        (
            body[Upper_bod].Position.getx() + 0.4 * body[Upper_bod].Dimension.getx() * cos(torad(body[Upper_bod].angle - 180))
            ,
            body[Upper_bod].Position.gety() - body[Upper_bod].Dimension.gety()/4 - 0.4 * body[Upper_bod].Dimension.getx() * sin(torad(body[Upper_bod].angle - 180))
        );
        body[Upper_armR].Position = 
        Vflt2
        (
            body[Upper_bod].Position.getx() + 0.4 * body[Upper_bod].Dimension.getx() * cos(torad(body[Upper_bod].angle))
            ,
            body[Upper_bod].Position.gety() - body[Upper_bod].Dimension.gety()/4 - 0.4 * body[Upper_bod].Dimension.getx() * sin(torad(body[Upper_bod].angle))
        );
        */
        body[Upper_legL].Position =  body[Lower_bod].portion(235);
        body[Upper_legR].Position =  body[Lower_bod].portion(305);
        /*
        body[Upper_legL].Position = 
        Vflt2
        (
            body[Lower_bod].Position.getx() + 0.68 * body[Upper_legL].Dimension.gety() * cos(torad(body[Lower_bod].angle - 90))
            ,
            body[Lower_bod].Position.gety() - 0.68 * body[Upper_legL].Dimension.gety() * sin(torad(body[Lower_bod].angle - 90))
        );
        body[Upper_legR].Position = 
        Vflt2
        (
            body[Lower_bod].Position.getx() + 0.68 * body[Upper_legL].Dimension.gety() * cos(torad(body[Lower_bod].angle - 90))
            ,
            body[Lower_bod].Position.gety() - 0.68 * body[Upper_legL].Dimension.gety() * sin(torad(body[Lower_bod].angle - 90))
        );
        */
        //
        body[Lower_armL].Position = 
        Vflt2
        (
            body[Upper_armL].Position.getx() + 0.632 * body[Upper_armL].Dimension.gety() * cos(torad(body[Upper_armL].angle - 90))
            ,
            body[Upper_armL].Position.gety() - 0.632 * body[Upper_armL].Dimension.gety() * sin(torad(body[Upper_armL].angle - 90))
        );
        body[Lower_armR].Position = 
        Vflt2
        (
            body[Upper_armR].Position.getx() + 0.632 * body[Upper_armR].Dimension.gety() * cos(torad(body[Upper_armR].angle - 90))
            ,
            body[Upper_armR].Position.gety() - 0.632 * body[Upper_armR].Dimension.gety() * sin(torad(body[Upper_armR].angle - 90))
        );
        body[Lower_legR].Position = 
        Vflt2
        (
            body[Upper_legR].Position.getx() + 0.68 * body[Upper_legL].Dimension.gety() * cos(torad(body[Upper_legR].angle - 90))
            ,
            body[Upper_legR].Position.gety() - 0.68 * body[Upper_legL].Dimension.gety() * sin(torad(body[Upper_legR].angle - 90))
        );
        body[Lower_legL].Position = 
        Vflt2
        (
            body[Upper_legL].Position.getx() + 0.68 * body[Upper_legL].Dimension.gety() * cos(torad(body[Upper_legL].angle - 90))
            ,
            body[Upper_legL].Position.gety() - 0.68 * body[Upper_legL].Dimension.gety() * sin(torad(body[Upper_legL].angle - 90))
        );
        body[HandL].Position =
            Vflt2
        (
            body[Lower_armL].Position.getx() + 0.84 * body[Lower_armL].Dimension.gety() * cos(torad(body[Lower_armL].angle - 90))
            ,
            body[Lower_armL].Position.gety() - 0.84 * body[Lower_armL].Dimension.gety() * sin(torad(body[Lower_armL].angle - 90))
        );
        body[HandR].Position =
            Vflt2
        (
            body[Lower_armR].Position.getx() + 0.84 * body[Lower_armR].Dimension.gety() * cos(torad(body[Lower_armR].angle - 90))
            ,
            body[Lower_armR].Position.gety() - 0.84 * body[Lower_armR].Dimension.gety() * sin(torad(body[Lower_armR].angle - 90))
        );
        body[FeetL].Position = 
        Vflt2
        (
            body[Lower_legL].image.get_cenpos().x 
            + 
            0.75 * body[Lower_legL].Dimension.gety() * cos(torad(body[Lower_legL].angle - 90)), 
            body[Lower_legL].image.get_cenpos().y
            - 
            0.75 * body[Lower_legL].Dimension.gety() * sin(torad(body[Lower_legL].angle - 90))
        );
        body[FeetR].Position = 
        Vflt2
        (
            body[Lower_legR].image.get_cenpos().x 
            + 
            0.75 * body[Lower_legR].Dimension.gety() * cos(torad(body[Lower_legR].angle - 90)), 
            body[Lower_legR].image.get_cenpos().y
            - 
            0.75 * body[Lower_legR].Dimension.gety() * sin(torad(body[Lower_legR].angle - 90))
        );
    }
    void setbody(){
        // tighten();
    }
    void draw(){
        tighten();
        //for(int i = 0; i < 2; i++)body[i].draw();
        body[Lower_armR].draw();
        body[Upper_armR].draw();
        body[HandR].draw();
        body[Upper_bod].draw();
        body[Head].draw();
        
        body[Lower_legL].draw();
        body[Lower_legR].draw();
        body[Upper_legL].draw();
        body[Upper_legR].draw();
        body[Lower_bod].draw();
        body[Lower_armL].draw();
        body[Upper_armL].draw();
        body[HandL].draw();
        body[FeetL].draw();
        body[FeetR].draw();
        
        /*
        for(int i = 0; i < 15; i++){
            body[i].setphysx();    
        }
        */
        
    }
    void infof(ofstream& ofs){
        ofs << " ===================================================== " << endl;
        ofs << " Rigid body details: " << endl;
        for(int i = 0; i < 15; i++){
            ofs << " ===================================================== " << endl;
            ofs << ' ' << body_list[i] << " details: " << endl;
            body[i].displayf(ofs);
            ofs << " ===================================================== " << endl;
        }
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
        body[Lower_armR].draw();
        body[Upper_bod].draw();
        body[Lower_bod].draw();
        body[Head].draw();
        body[Upper_armL].draw();
        body[Lower_armL].draw();
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