/*
*
*
* Physics implementation
*
*
*/
#include "vector2D.h"
const float quanta = 0.1;
const float gravity = -10;
class kinematics
{
    public:
    Vflt2 pos;
    Vflt2 vel = Vflt2_0;
    Vflt2 accI = Vflt2_0;
    Vflt2 accF = Vflt2_0;
    Vflt2 up_accF(bool grav = false, bool drag = false)
    {
        accF = accI;
        accF.getx() += (drag ? 0.5 * gravity * 1 * (abs(vel.getx()) / vel.getx()) : 0);
        accF.gety() += (grav ? gravity : 0);
        return accF;
    }
    Vflt2 up_vel()
    {
        vel.getx() += accF.getx() * quanta;
        vel.gety() += accF.gety() * quanta;
        return vel;
    }
    Vflt2 up_pos()
    {
        pos.getx() += vel.getx() * quanta;
        pos.gety() -= vel.gety() * quanta;
        return pos;
    }
};
