/*
*
*
* Physics implementation
* 1. Kinematics
* 2. Dynamics
* 3. Mechanics
*
*/
// requires copy constructor, destructor and a few operators
class physx
{
    public:
    static constexpr float delta = 0.1;
        physx(){}
        physx(const Vflt2& pos, const Vflt2& vel = Vflt2_0, const Vflt2& acc = Vflt2_0, const Vflt2& dim = Vflt2_0, 
              const Vflt2& com = Vflt2_0, float ang = 0, float ang_vel = 0, float ang_acc = 0, float m = 0) {
            //Position = pos;
            Velocity = vel;
            Acceleration = acc;
            //Dimension = dim;
            //Center_of_mass = com;
            //angle = ang;
            Angular_velocity = ang_vel;
            Angular_acceleration = ang_acc;
            mass = m;
        }
        void app(SDL_FPoint& pos, double& angle) {
            app_acc();
            app_vel(pos);
            app_ang_acc();
            app_ang_vel(angle);
        }
        inline void app_acc(){
            Velocity.getx() += Acceleration.getx() * delta;
            Velocity.gety() += Acceleration.gety() * delta;
        }
        inline void app_vel(SDL_FPoint& pos){
            pos.x += Velocity.getx() * delta;
            pos.y -= Velocity.gety() * delta;
        }
        inline void app_ang_acc(){
            Angular_velocity += Angular_acceleration * delta;
        }
        inline void app_ang_vel(double& angle){
            angle += Angular_velocity * delta;
        }
        inline void set_center_of_mass(const SDL_FPoint& cen)
        {
            //Center_of_mass.getx() = (cen.getx() == -1 ? Dimension.getx() / 2 : cen.getx());
            //Center_of_mass.gety() = (cen.gety() == -1 ? Dimension.gety() / 2 : cen.gety());
        }
        inline void set_mass(float m = -1){
            mass = (m < 0 ? 0 : m);
        }
        void display(ostream& os = cout){
            os << " Velocity = " << Velocity << endl;
            os << " Acceleration = " << Acceleration << endl;
            os << " Angular_velocity = " << Angular_velocity << endl;
            os << " Angular_acceleration = " << Angular_acceleration << endl;
            os << " mass = " << mass << endl;
        }
        void displayf(ofstream& ofs){
            ofs << " Velocity = " << Velocity << endl;
            ofs << " Acceleration = " << Acceleration << endl;
            ofs << " Angular_velocity = " << Angular_velocity << endl;
            ofs << " Angular_acceleration = " << Angular_acceleration << endl;
            ofs << " mass = " << mass << endl;
        }
        /*
        Dimensions,
        center of mass, 
        position, 
        angle are assumed to be extended on physx to save memory
        */
        Vflt2 Velocity; // 8 bytes
        Vflt2 Acceleration; // 8 bytes
        float Angular_velocity; // 4 bytes
        float Angular_acceleration; // 4 bytes
        float mass; // 4 bytes
        // total = 28 bytes
};
class physx_surface // static object
{
    public:
    Vflt2* vecs;
    float coff = 0.1;
    physx_surface(){}
    physx_surface(Vflt2* veclist)
    {
        vecs = veclist;
    }
    virtual void touch(physx& obj) = 0;
};
class physx_body : public physx
{
    public:
        physx_body(){
            
        }
};