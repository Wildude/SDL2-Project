/*
*
*
* Physics implementation
* 1. Kinematics
* 2. Dynamics
* 3. Mechanics
*
*/
class physx
{
    static constexpr float delta = 0.1;
    public:
        physx(){}
        physx(Vflt2 pos, Vflt2 vel = Vflt2_0, Vflt2 acc = Vflt2_0){
            Position = pos;
            Velocity = vel;
            Acceleration = acc;
        }
        void app(){
            app_acc();
            app_vel();
            app_ang_acc();
            app_ang_vel();
        }
        void app_acc(){
            Velocity.getx() += Acceleration.getx() * delta;
            Velocity.gety() += Acceleration.gety() * delta;
        }
        void app_vel(){
            Position.getx() += Velocity.getx() * delta;
            Position.gety() -= Velocity.gety() * delta;
        }
        void app_ang_acc(){
            Angular_velocity += Angular_acceleration;
        }
        void app_ang_vel(){
            angle += Angular_velocity * delta;
        }
        void set_center_of_mass(Vflt2 cen = Vflt2(-1, -1))
        {
            Center_of_mass.getx() = (cen.getx() < 0 ? Dimension.getx() / 2 : cen.getx());
            Center_of_mass.gety() = (cen.gety() < 0 ? Dimension.gety() / 2 : cen.gety());
        }
        void set_mass(float m = -1){
            mass = (m < 0 ? Dimension.getx() * Dimension.gety() : m);
        }
        void display(ostream& os = cout){
            os << " Dimension = " << Dimension << endl;
            os << " Position = " << Position << endl;
            os << " Velocity = " << Velocity << endl;
            os << " Acceleration = " << Acceleration << endl;
            os << " Angular_velocity = " << Angular_velocity << endl;
            os << " Angular_acceleration = " << Angular_acceleration << endl;
            os << " mass = " << mass << endl;
            os << " angle = " << angle << endl;
            os << " Center_of_mass = " << Center_of_mass << endl;
        }
        void displayf(ofstream& ofs){
            ofs << " Dimension = " << Dimension << endl;
            ofs << " Position = " << Position << endl;
            ofs << " Velocity = " << Velocity << endl;
            ofs << " Acceleration = " << Acceleration << endl;
            ofs << " Angular_velocity = " << Angular_velocity << endl;
            ofs << " Angular_acceleration = " << Angular_acceleration << endl;
            ofs << " mass = " << mass << endl;
            ofs << " angle = " << angle << endl;
            ofs << " Center_of_mass = " << Center_of_mass << endl;
        }
        Vflt2 Dimension = Vflt2_0; // width x height;
        Vflt2 Position = Vflt2_0;
        Vflt2 Velocity = Vflt2_0;
        Vflt2 Acceleration = Vflt2_0;
        float Angular_velocity = 0;
        float Angular_acceleration = 0;
        float mass = 0;
        float angle = 0;
        Vflt2 Center_of_mass;
};
class physx_surface
{
    public:
    TEXTURE image;
    SDL_Color col = {0, 0, 0, 255};
    float mag = 1;
    float coff = 0.1;
    physx_surface(){}
    physx_surface(SDL_Renderer* rend){image.setren(rend);}
    physx_surface(Vflt2 pos_1, Vflt2 pos_2)
    {
        pos1 = pos_1;
        pos2 = pos_2;
        set();
    }
    void set(){
        angle = angler(pos1, pos2);
        magnitude = (pos1 - pos2).getmag();
    }
    void setmag(float magn){
        mag = (magn <= 1 ? mag : magn);
    }
    void setcolor(Uint8 r = -1, Uint8 g = -1, Uint8 b = -1){
        col.r = r;
        col.g = g;
        col.b = b;
    }
    void query(){
        SDL_Surface* surf = SDL_CreateRGBSurface(0, (!image.getdst().w ? mag : image.getdst().w), (!image.getdst().h ? mag : image.getdst().h), 8, 0, 0, 0, 0);
        SDL_SetSurfaceColorMod(surf, col.r, col.g, col.b);
        image.surfcpy(surf);
        image.queryF();
        image.magnify(mag);
        reset();
    }
    void reset(){
        set();
        image.set_cenpos(pos1.getx(), pos1.gety());
        image.set_dstdim(magnitude, image.getdst().h);
        image.setangle(-angle);
    }
    void draw(){
        image.drawC();
    }
    physx_surface(Vflt2 pos_1, float mag, float ang){}
    void touch(physx& obj){
        if(obj.Position.getx() < pos1.getx() || obj.Position.getx() > pos2.getx())return;
        if(!((int)angle % 90) && angle){
            if(obj.Position.getx() < pos1.getx() && obj.Position.getx() + obj.Dimension.getx() > pos1.getx()){
                Vflt2 
                normA = Vflt2(false, obj.Acceleration.getmag(), (angle) + 90)
                , normV = Vflt2(false, obj.Velocity.getmag(), (angle) + 90);
                // cout << obj.Velocity << " | " << normV << endl;
                obj.Acceleration += normA;
                obj.Velocity += normV;
                return;
            }
        }
        float slope = tan(torad(angle));
        float dx = obj.Position.getx() - pos1.getx();
        float y = -slope * dx + pos1.gety();
        if(obj.Position.gety() >= y)
        {
            obj.Position.gety() = y;
            Vflt2 
            normA = Vflt2(obj.Acceleration.getmag() * cos(torad(angle)), -obj.Acceleration.getmag() * sin(torad(angle)))
            , normV = Vflt2(obj.Velocity.getmag() * cos(torad(angle)), -obj.Velocity.getmag() * sin(torad(angle)));
            cout << obj.Velocity << " | " << normV << endl;
            obj.Acceleration += normA;
            obj.Velocity += normV;
        }
        //float rangle = angler(pos1, obj.Position);
        
        
    }
    float angle = 0;
    float magnitude = 0;
    Vflt2 pos1 = Vflt2_0;
    Vflt2 pos2 = Vflt2_0;
};
class physx_body : public physx
{
    public:
        TEXTURE image;
        Vflt2* rects;
        Vflt2 portion(double angle){
            rectdef();
            double angletet = -(angle + physx::angle);
            Vflt2 actcen(image.getdst().x + image.getdst().w/2, image.getdst().y + image.getdst().h/2);
            Vflt2 cenpos(image.get_cenpos().x, image.get_cenpos().y);
            Vflt2 termray1 = Vflt2(actcen.getx() + image.getdst().h * cos(torad(angle)), actcen.gety() - image.getdst().h * sin(torad(angle)));
            Vflt2 termray = Vflt2(actcen.getx() + image.getdst().h * cos(torad(angletet)), actcen.gety() - image.getdst().h * sin(torad(-angletet)));
            float xd = dx(actcen, termray1);
            float yd = dy(actcen, termray1);
            if(xd < 0){
                // cout << "xd < 0" << endl;
                if(yd < 0){
                    // cout << "yd < 0" << endl;
                    if(intersector_B(actcen, termray, rects[0], rects[1])){
                        // cout << "0 and 1" << endl;
                        return intersector(actcen, termray, rects[0], rects[1]);
                    }
                    else if(intersector_B(actcen, termray, rects[0], rects[3])){
                        // cout << "0 and 3" << endl;
                        return intersector(actcen, termray, rects[0], rects[3]);
                    }
                }
                if(yd > 0){
                    // cout << "yd > 0" << endl;
                    if(intersector_B(actcen, termray, rects[3], rects[2])){
                        // cout << "3 and 2" << endl;
                        return intersector(actcen, termray, rects[3], rects[2]);
                    }
                    else if(intersector_B(actcen, termray, rects[0], rects[3])){
                        // cout << "0 and 3" << endl;
                        return intersector(actcen, termray, rects[0], rects[3]);
                    }
                }
                else{
                    // cout << "yd = 0" << endl;
                    // cout << "0 and 3" << endl;
                    return intersector(actcen, termray, rects[0], rects[3]);
                }
            }
            else if(xd > 0){
                // cout << "xd > 0" << endl;
                if(yd > 0){
                    // cout << "yd > 0" << endl;
                    if(intersector_B(actcen, termray, rects[1], rects[2])){
                        // cout << "1 and 2" << endl;
                        return intersector(actcen, termray, rects[1], rects[2]);
                    }
                    else if(intersector_B(actcen, termray, rects[2], rects[3])){
                        // cout << "2 and 3" << endl;
                        return intersector(actcen, termray, rects[2], rects[3]);
                    }
                }
                else if(yd < 0){
                    // cout << "yd < 0" << endl;
                    if(intersector_B(actcen, termray, rects[0], rects[1])){
                        // cout << "0 and 1" << endl;
                        return intersector(actcen, termray, rects[0], rects[1]);
                    }
                    else if(intersector_B(actcen, termray, rects[1], rects[2])){
                        // cout << "1 and 2" << endl;
                        return intersector(actcen, termray, rects[1], rects[2]);
                    }
                }
                else{
                    // cout << "yd = 0" << endl;
                    // cout << "1 and 2" << endl;
                    return intersector(actcen, termray, rects[1], rects[2]);
                }
            }
            else{
                // cout << "xd = 0" << endl;
                if(yd < 0){
                    // cout << "yd < 0" << endl;
                    // cout << "0 and 1" << endl;
                    return intersector(actcen, termray, rects[0], rects[1]);
                }
                else if(yd > 0){
                    // cout << "yd > 0" << endl;
                    // cout << "3 and 2" << endl;
                    return intersector(actcen, termray, rects[3], rects[2]);
                }
                else{
                    // cout << "yd = 0" << endl;
                    cout << "error" << endl;
                    return Vflt2(numeric_limits<float>::min(), numeric_limits<float>::min());
                }
            }
        }
        physx_body(){
            rects = new Vflt2[4];
        }
        void rectset(){
            rects[0] = Vflt2(image.getdst().x, image.getdst().y);
            rects[1] = Vflt2(image.getdst().x + image.getdst().w, image.getdst().y);
            rects[2] = Vflt2(image.getdst().x + image.getdst().w, image.getdst().y + image.getdst().h);
            rects[3] = Vflt2(image.getdst().x, image.getdst().y + image.getdst().h);
        }
        physx_body(TEXTURE img)
        {
            physx_body();
            image.copy(img);
            rectset();
            rotate_rC(rects, image.getangle(), 4);
        }
        physx_body(const char* path, SDL_Renderer* rend){
            physx_body();
            load(path, rend);
        }
        void setcm(){
            Center_of_mass = Vflt2(image.getcenter().x, image.getcenter().y);
        }
        void load(const char* path, SDL_Renderer* rend){
            image.setren(rend);
            image.load(path);
            queryset();
            rectdef();
        }
        void query(){
            image.queryF();
        }
        void setdims(){
            Dimension = Vflt2(image.getdst().w, image.getdst().h);
        }
        void magnify(float x, float y = -1){
            y = (y <= 0 ? x : y);
            image.magnify(x, y);
            setdims();
        }
        void queryset(float x = -1, float y = -1){
            image.queryF();
            setdims();
            set_center_of_mass(Vflt2(x, y));
        }
        void setphysx(){
            app();
            image.set_dstdim(Dimension.getx(), Dimension.gety());
            image.setcenter(Center_of_mass.getx(), Center_of_mass.gety());
            image.set_cenpos(Position.getx(), Position.gety());
            image.setangle(-angle);
            rectdef();
        }
        void rectdef(){
            rectset();
            rotate_rC(rects, -image.getangle(),  4);
        }
        void draw(){
            setphysx();
            image.drawC();
        }
        void display(ostream& os = cout){
            physx::display(os);
            image.display(os);
        }
        void displayf(ofstream& ofs){
            physx::display(ofs);
            image.display(ofs);
        }
};