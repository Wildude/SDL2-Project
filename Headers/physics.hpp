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
            if(cen.getx() < 0 || cen.gety() < 0){
                if(Dimension.getx() > 0 && Dimension.gety() > 0){
                    Center_of_mass = Dimension * 0.5;
                }
            }
            else Center_of_mass = cen;
        }
        void set_mass(float m = -1){
            mass = (m < 0 ? Dimension.getx() * Dimension.gety() : m);
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
    physx_surface(){}
    physx_surface(Vflt2 pos_1, Vflt2 pos_2)
    {
        pos1 = pos_1;
        pos2 = pos_2;
        angle = angler(pos1, pos2);
        magnitude = (pos1 - pos2).getmag();
    }
    physx_surface(Vflt2 pos_1, float mag, float ang){}
    void touch(physx obj){
        float rangle = angler(pos1, obj.Position);
        obj.Acceleration += Vflt2(false, obj.Acceleration.getmag(), angle);
        obj.Velocity += Vflt2(obj.Velocity.getmag(), angle);
    }
    private:
    float angle = 0;
    float magnitude = 0;
    Vflt2 pos1 = Vflt2_0;
    Vflt2 pos2 = Vflt2_0;
};
class physx_body : public physx
{
    public:
        TEXTURE image;
        physx_body(){}
        physx_body(TEXTURE img)
        {
            image.copy(img);
        }
        void query(){
            image.queryF();
        }
        void setdims(){
            Dimension = Vflt2(image.getdst().w, image.getdst().h);
        }
        void queryset(){
            query();
            setdims();
        }
        void setphysx(){
            app();
            image.set_dstdim(Dimension.getx(), Dimension.gety());
            image.setcenter(Center_of_mass.getx(), Center_of_mass.gety());
            image.set_cenpos(Position.getx(), Position.gety());
            image.setangle(-angle);
        }
        void draw(){
            setphysx();
            image.drawC();
        }
};