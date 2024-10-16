class weapon : public physx_body{
    Vflt2 target;
    bool twoside = false;
    Vflt2 maincenter;
    //float width = -1;
    public:
    weapon(){}
    weapon(const Vflt2& tar, bool two = false){
        twoside = false;
        target = tar;
    }
    void set_target(const Vflt2& tar){
        target = tar;
    }
    void aim(){
        angle = angler(Vflt2(image.get_cenpos().x, image.get_cenpos().y), target);
        image.set_srcpos(0, 0);
        Center_of_mass = maincenter;
        if(twoside){
            if(target.getx() < image.get_cenpos().x)switchside();
            //else normside();
        }
    }
    void setmaincenter(const Vflt2& center){
        maincenter = center;
    }
    void setmaincenter(float x, float y){
        maincenter = Vflt2(x, y);
    }
    void setwidth(float w = -1){
        if(twoside){
            w = (w <= 0 ? image.getsrc().w / 2 : w);
            image.set_srcdim(w, image.getsrc().h);
        }
        else return;
    }
    void switchside(){
        if(!twoside)return;
        image.set_srcpos(image.getsrc().w, 0);
        Center_of_mass = Vflt2(image.getdst().w - maincenter.getx(), Center_of_mass.gety());
        angle += 180;
    }
    void disptar(ostream& os = cout){
        os << " target = " << target << endl;
    }
    void disptarf(ofstream& of){
        of << " target = " << target << endl;
    }
    void setbool(bool bul = false){
        twoside = bul;
        if(twoside)setwidth(65);
    }
};