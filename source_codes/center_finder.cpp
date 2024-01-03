#include "../Files/Headers/vector2D.h"
int main(int argn, char** args)
{
    int sides, sidelength;
    cout<<" Enter number of sides: ";
    cin >> sides;
    cout<<" Enter sidelengths: ";
    cin >> sidelength;
    Vint2 center(320, 240);
    int radius = sidelength * (1 / (2 * sinf(3.14 / (float)sides)));
    Vint2* vertices = new Vint2 [sides];
    double cen_angle = (2 * 3.14) / sides;
    for(int i = 0; i < sides; i++)vertices[i] = Vint2(center.getx() + radius * cosf(cen_angle * i), center.gety() - radius * sinf(cen_angle * i));
    int cx = 0;
    int cy = 0;
    int Area = 0;
    int area = (0.5) * (radius * cosf(cen_angle/2)) * (sides * sidelength);
    for(int i = 0; i < sides; i++)
    {
        Area
        +=
        (
            (vertices[i].getx() * vertices[i != sides-1 ? i + 1 : 0].gety())
            -
            (vertices[i != sides-1 ? i + 1 : 0].getx() * vertices[i].gety())
        );
    }
    Area /= 2;
    for(int i = 0; i < sides; i++)
    {
        cx
        +=
        (
            (vertices[i].getx() + vertices[i != sides-1 ? i + 1 : 0].getx())
            *
            (
                (vertices[i].getx() * vertices[i != sides-1 ? i + 1 : 0].gety())
                -
                (vertices[i != sides-1 ? i + 1 : 0].getx() * vertices[i].gety())
            )
        );
        cy
        +=
        (
            (vertices[i].gety() + vertices[i != sides-1 ? i + 1 : 0].gety())
            *
            (
                (vertices[i].getx() * vertices[i != sides-1 ? i + 1 : 0].gety())
                -
                (vertices[i != sides-1 ? i + 1 : 0].getx() * vertices[i].gety())
            )
        );
    }
    Vint2 centroids(cx, cy);
    Vint2 calc_center(cx/(6 * Area), cy/(6 * Area));
    Vint2 calc_center2(cx/(6 * area), cy/(6 * area));
    cout<<" given center: "<<center<<endl;
    cout<<" found center1: "<<calc_center<<endl;
    cout<<" found center2: "<<calc_center2<<endl;
    return 0;
}
