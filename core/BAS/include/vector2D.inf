float PI = 3.14;
inline int todeg(double rad)
{
    return (rad * (180/PI));
}
inline double torad(int deg)
{
    return (deg * (PI/180));
}
template <class T> 
class VECTOR2
{    
    T x, y;
    public:
        VECTOR2(T xcomp = 0, T ycomp = 0)
        {
            x = xcomp;
            y = ycomp;
            //cout<<" contructor called for points\n";
        }
        VECTOR2(bool noth, float mag, float angle){
            x = ((angle && !((int)angle % 90)) ? 0 : mag * cos(torad(angle)));
            y = (!((int)angle % 180) ? 0 : mag * sin(torad(angle)));
        }
        inline string tostring(){
            string str = "(" + strmap::to_str((int)x) + "," + strmap::to_str((int)y) + ")";
            return str;
        }
        T getx() const {return x;}
        T gety() const {return y;}
        T& getx() {return x;}
        T& gety() {return y;}
        T getmag() {return sqrt(x * x + y * y);}
        const VECTOR2& operator*=(T num)
        {
            x *= num;
            y *= num;
            return *this;
        }
        bool operator!=(VECTOR2 vec)
        {
            return (x != vec.getx() || y != vec.gety());
        }
        bool operator==(VECTOR2 vec)
        {
            return (this->getx() == vec.getx() && this->gety() == vec.gety());
        }
        inline VECTOR2 getU2() {return VECTOR2(x/getmag(), y/getmag());}      
        const VECTOR2& operator=(const VECTOR2& v)
        {
            x = v.x;
            y = v.y;
            return *this;
        }
        VECTOR2 operator*(T num)
        {
            return VECTOR2(num * this->getx(), num * this->gety());
        }
        VECTOR2 operator+(const VECTOR2& v)
        {
            return VECTOR2(this->x + v.x, this->y + v.y);
        }
        VECTOR2 operator*(const VECTOR2& v)
        {
            return VECTOR2(this->x * v.x, this->y * v.y);
        }
        VECTOR2 operator-(const VECTOR2& v)
        {
            return VECTOR2(this->x - v.x, this->y - v.y);
        }
        const VECTOR2& operator+=(const VECTOR2& v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }
        const VECTOR2& operator-=(const VECTOR2& v)
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }
        const VECTOR2& operator*=(const VECTOR2& v)
        {
            x *= v.x;
            y *= v.y;
            return *this;
        }
        template <class Y> VECTOR2<Y> friend operator*(T, VECTOR2<Y>);
        template <class Y> friend ostream& operator<<(ostream&, const VECTOR2<Y>&);
        friend istream& operator>>(istream&, VECTOR2<int>&);
        friend istream& operator>>(istream&, VECTOR2<float>&);
        friend istream& operator>>(istream&, VECTOR2<double>&);
};
typedef VECTOR2<int> Vint2;
typedef VECTOR2<float> Vflt2;
typedef VECTOR2<double> Vdb2;
const Vint2 Vint2_0 = Vint2(0, 0);
const Vflt2 Vflt2_0 = Vflt2(0, 0);
const Vdb2 Vdb2_0 = Vdb2(0, 0);
template <class T> VECTOR2<T> operator*(T num, VECTOR2<T> vec)
{
    return VECTOR2<T>(vec.getx() * num, vec.gety() * num);
}
istream& operator>>(istream& in, Vint2& v)
{
    in >> v.getx() >> v.gety();
    return in;
}
istream& operator>>(istream& in, Vflt2& v)
{
    in >> v.getx() >> v.gety();
    return in;
}
istream& operator>>(istream& in, Vdb2& v)
{
    in >> v.getx() >> v.gety();
    return in;
}
template <class T> ostream& operator<<(ostream& out, const VECTOR2<T>& v)
{
    out<<'('<<v.x<<','<<v.y<<')';
    return out;
}
template <class T> T dx(const VECTOR2<T>& v1, const VECTOR2<T>& v2)
{
    return v2.getx() - v1.getx();
}
template <class T> T dy(const VECTOR2<T>& v1, const VECTOR2<T>& v2)
{
    return v2.gety() - v1.gety();
}
template <class T> double angle_bn(const VECTOR2<T>& v1, const VECTOR2<T>& v2, bool yi = true)
{
    T y = dy(v1, v2);
    T x = dx(v1, v2);
    double rang = (x ? (180 / PI) * atan(((float)(yi ? -y : y)/(float)x)) : (y > 0 ? (yi ? -90 : 90) : (yi ? 90 : -90)));
    bool xl = (x < 0);
    bool yl = (y < 0);
    if(xl && yl){rang += 180;return rang;}
    else if(xl){rang = 180 - (-1 * (rang)); return rang;}
    else if(yl){rang += 360; return rang;}
    else return rang;
}
template <class T> T p_l_mag(const VECTOR2<T>& p, const VECTOR2<T>& lpos1, float angle)
{
    return (p - intersection(p, p + VECTOR2<T>(100 * cos(torad(angle - 90)), -100 * sin(torad(angle - 90))), lpos1, lpos1 + VECTOR2<T>(100 * cos(torad(angle)), -100 * sin(torad(angle))))).getmag();
}
template <class T> VECTOR2<T>* n_gonr(const VECTOR2<T>& v, int sides, float sidelength, double angle = 0)
{
    VECTOR2<T>* vertices = new VECTOR2<T>[sides];
    T radius = sidelength * 0.5 * (sin(PI / sides));
    double central_angle = (2 * PI) / sides;
    for(int i = 0; i < sides; i++)
    {
        vertices[i]
        = 
        VECTOR2<T>
        (
            v.getx() + radius * cos(central_angle * i + angle)
            , 
            v.gety() - radius * sin(central_angle * i + angle)
        );
    }
    return vertices;
}
template <class T> VECTOR2<T> C_x_y_find(const vector<VECTOR2<T>>& vertices)
{
    VECTOR2<T> C_x_y;
    T Area = 0;
    T cx= 0, cy = 0;
    for(int i = 0; i < vertices.size(); i++)
    {
        Area
        +=
        (
            (vertices[i].getx() * vertices[i != vertices.size()-1 ? i + 1 : 0].gety())
            -
            (vertices[i != vertices.size()-1 ? i + 1 : 0].getx() * vertices[i].gety())
        );
    }
    Area /= 2;
    for(int i = 0; i < vertices.size(); i++)
    {
        cx
        +=
        (
            (vertices[i].getx() + vertices[i != vertices.size()-1 ? i + 1 : 0].getx())
            *
            (
                (vertices[i].getx() * vertices[i != vertices.size()-1 ? i + 1 : 0].gety())
                -
                (vertices[i != vertices.size()-1 ? i + 1 : 0].getx() * vertices[i].gety())
            )
        );
        cy
        +=
        (
            (vertices[i].gety() + vertices[i != vertices.size()-1 ? i + 1 : 0].gety())
            *
            (
                (vertices[i].getx() * vertices[i != vertices.size()-1 ? i + 1 : 0].gety())
                -
                (vertices[i != vertices.size()-1 ? i + 1 : 0].getx() * vertices[i].gety())
            )
        );
    }
    cx /= 6 * Area;
    cy /= 6 * Area;
    C_x_y = VECTOR2<T>(cx , cy);
    return C_x_y;
}
template <class T> VECTOR2<T> C_x_y_find(VECTOR2<T>* vertices, int size)
{
    VECTOR2<T> C_x_y;
    T Area = 0;
    T cx= 0, cy = 0;
    for(int i = 0; i < size; i++)
    {
        Area
        +=
        (
            (vertices[i].getx() * vertices[i != size-1 ? i + 1 : 0].gety())
            -
            (vertices[i != size-1 ? i + 1 : 0].getx() * vertices[i].gety())
        );
    }
    Area /= 2;
    for(int i = 0; i < size; i++)
    {
        cx
        +=
        (
            (vertices[i].getx() + vertices[i != size-1 ? i + 1 : 0].getx())
            *
            (
                (vertices[i].getx() * vertices[i != size-1 ? i + 1 : 0].gety())
                -
                (vertices[i != size-1 ? i + 1 : 0].getx() * vertices[i].gety())
            )
        );
        cy
        +=
        (
            (vertices[i].gety() + vertices[i != size-1 ? i + 1 : 0].gety())
            *
            (
                (vertices[i].getx() * vertices[i != size-1 ? i + 1 : 0].gety())
                -
                (vertices[i != size-1 ? i + 1 : 0].getx() * vertices[i].gety())
            )
        );
    }
    cx /= 6 * Area;
    cy /= 6 * Area;
    C_x_y = VECTOR2<T>(cx , cy);
    return C_x_y;
}
template <class T> bool in_RECT(VECTOR2<T>* vecs, const VECTOR2<T>& point, int size)
{
    //implement
    bool xcr = false;
    bool ycr = false;
    bool xcr1 = true;
    bool ycr1 = true;
    for(int i = 0; i < size; i++)
    {
        if(vecs[i].getx() > point.getx())xcr = true;
        if(vecs[i].gety() < point.gety())ycr = true;
        if(vecs[i].getx() < point.getx())xcr1 = false;
        if(vecs[i].gety() > point.gety())ycr1 = false;
    }
    if(!xcr || xcr1)return false;
    else if(!ycr || ycr1)return false;
    else return true;
}
template <class T> VECTOR2<T> intersection(const VECTOR2<T>& vec11, const VECTOR2<T>& vec12, const VECTOR2<T>& vec21, const VECTOR2<T>& vec22, bool yi = true)
{
    double xd1 = dx(vec11, vec12), xd2 = dx(vec21, vec22);
    double yd1 = dy(vec11, vec12), yd2 = dy(vec21, vec22);
    double m1 = (yi ? -yd1 : yd1) / xd1;
    double m2 = (yi ? -yd2 : yd2) / xd2;
    T x1 = vec11.getx(), x2 = vec21.getx(), y1 = vec11.gety(), y2 = vec21.gety();
    T x, y;
    if(!dx(vec11, vec12) || !dx(vec21, vec22))
    {
        if(!dx(vec11, vec12) && dx(vec21, vec22))
        {
            x = x1;
            y = (yi ? -1 : 1) * m2 * (x - x2) + y2;
        }
        else if(dx(vec11, vec12) && !dx(vec21, vec22))
        {
            x = x2;
            y = (yi ? -1 : 1) * m1 * (x - x1) + y1;
        }
        else 
        {
            return VECTOR2<T>(-1000000, -1000000);
        }
    }
    else
    {
        x = ((yi ? -1 : 1) * (m1 * x1 - m2 * x2) + y2 - y1)/((yi ? -1 : 1) * (m1 - m2));
        y = (yi ? -1 : 1) * m1 * (x - x1) + y1;
    }
    return VECTOR2<T>(x, y);
}
template <class T> bool bound_r(const VECTOR2<T>& v11, const VECTOR2<T>& v12, const VECTOR2<T>& vec)
{
    if(const_cast<VECTOR2<T>&>(v11) == v12)
    {
        return vec == v11;
    }
    else
    {
        if(v11.getx() == v12.getx())
        {
            return 
            (
                vec.getx() == v11.getx()
                &&
                vec.gety() <= (v11.gety() > v12.gety() ? v11.gety() : v12.gety())
                &&
                vec.gety() >= (v11.gety() < v12.gety() ? v11.gety() : v12.gety())
            );
        }
        else if(v11.gety() == v12.gety())
        {
            return 
            (
                vec.gety() == v11.gety()
                &&
                vec.getx() <= (v11.getx() > v12.getx() ? v11.getx() : v12.getx())
                &&
                vec.getx() >= (v11.getx() < v12.getx() ? v11.getx() : v12.getx())
            );
        }
        else
        {
            if
            (
                (angle_bn(v11, v12) == angle_bn(v11, vec)) || (v11 == vec)
                ||
                (angle_bn(v12, v11) == angle_bn(v12, vec)) || (v12 == vec)
            )
            {
                return
                (
                    vec.getx() >= (v11.getx() < v12.getx() ? v11.getx() : v12.getx())
                    &&
                    vec.getx() <= (v11.getx() > v12.getx() ? v11.getx() : v12.getx())
                );
            }
            else return 0;
        }
    }
}
template <class T> bool bound_rL(const VECTOR2<T>& v11, const VECTOR2<T>& v12, const VECTOR2<T>& vec)
{
    if(const_cast<VECTOR2<T>&>(v11) == const_cast<VECTOR2<T>&>(v12))
    {
        return const_cast<VECTOR2<T>&>(vec) == const_cast<VECTOR2<T>&>(v11);
    }
    else
    {
        if(v11.getx() == v12.getx())
        {
            return 
            (
                vec.getx() == v11.getx()
                &&
                vec.gety() <= (v11.gety() > v12.gety() ? v11.gety() : v12.gety())
                &&
                vec.gety() >= (v11.gety() < v12.gety() ? v11.gety() : v12.gety())
            );
        }
        else if(v11.gety() == v12.gety())
        {
            return 
            (
                vec.gety() == v11.gety()
                &&
                vec.getx() <= (v11.getx() > v12.getx() ? v11.getx() : v12.getx())
                &&
                vec.getx() >= (v11.getx() < v12.getx() ? v11.getx() : v12.getx())
            );
        }
        else
        {
            return
            (
                vec.getx() >= (v11.getx() < v12.getx() ? v11.getx() : v12.getx())
                &&
                vec.getx() <= (v11.getx() > v12.getx() ? v11.getx() : v12.getx())
                &&
                vec.gety() <= (v11.gety() > v12.gety() ? v11.gety() : v12.gety())
                &&
                vec.gety() >= (v11.gety() < v12.gety() ? v11.gety() : v12.gety())
            );
        }
    }
}
template <class T> bool intersector_B(const VECTOR2<T>& vec11, const VECTOR2<T>& vec12, const VECTOR2<T>& vec21, const VECTOR2<T>& vec22)
{
    bool l1 = bound_rL(vec11, vec12, intersection(vec11, vec12, vec21, vec22));
    bool l2 = bound_rL(vec21, vec22, intersection(vec11, vec12, vec21, vec22));
    return l1 && l2;
}
template <class T> bool in_polyB(VECTOR2<T>* vecs, const VECTOR2<T>& point, const VECTOR2<T>& term, int size)
{
    int c = 0;
    int count = 0;
    //for(int i = 0; i < size; i++)//cout<<" vec["<<i<<"] = "<<vecs[i]<<endl;
    for(int i = 0; i < size; i++)
    {
        if(intersector_B(point, term, vecs[i], vecs[i != size-1 ? i + 1: 0]))
        {
            c++;
            //cout<<" vec["<<i<<"] & vec["<<(i != size-1 ? i + 1 : 0)<<"]: "<<intersection(point, term, vecs[i], vecs[i != size-1 ? i + 1: 0])<<endl;
            //cout<<" checking intersection point similarities of:\n";
            //cout<<" vertices: "<<i<<(i != size-1 ? i + 1 : 0)<<intersection(point, term, vecs[i], vecs[i != size-1 ? i + 1: 0])<<" and "<<(i != size-1? i + 1 : 0)<<(i < size-2 ? i + 2: (i == size-2 ? 0 : 1))<<intersection(point, term, vecs[i != size-1 ? i + 1: 0], vecs[i < size-2 ? i + 2: (i == size-2 ? 0 : 1)])<<endl;
            if(
                (intersection(point, term, vecs[i], vecs[i != size-1 ? i + 1: 0]) - intersection(point, term, vecs[i != size-1 ? i + 1: 0], vecs[i < size-2 ? i + 2: (i == size-2 ? 0 : 1)])).getmag() > 10
            )
            {
                //cout<<" approved\n";
                count++;
            }
        }
    }
    if(!count && c)
    {
        //cout<<" one counted compensatedly\n";
        count++;
    }
    //cout<<" count: "<<count<<endl;
    if(count == 1)
    {
        //cout<<" second check (crosses once) => \n";
        int s = 0;
        int scount = 0;
        term *= -1;
        for(int i = 0; i < size; i++)
        {
            if(intersector_B(point, term, vecs[i], vecs[i != size-1 ? i + 1: 0]))
            {
                s++;
                //cout<<" vec["<<i<<"] & vec["<<(i != size-1 ? i + 1 : 0)<<"]: "<<intersection(point, term, vecs[i], vecs[i != size-1 ? i + 1: 0])<<endl;
                //cout<<" checking intersection point similarities of:\n";
                //cout<<" vertices: "<<i<<(i != size-1 ? i + 1 : 0)<<intersection(point, term, vecs[i], vecs[i != size-1 ? i + 1: 0])<<" and "<<(i != size-1? i + 1 : 0)<<(i < size-2 ? i + 2: (i == size-2 ? 0 : 1))<<intersection(point, term, vecs[i != size-1 ? i + 1: 0], vecs[i < size-2 ? i + 2: (i == size-2 ? 0 : 1)])<<endl;
                if((intersection(point, term, vecs[i], vecs[i != size-1 ? i + 1: 0]) - intersection(point, term, vecs[i != size-1 ? i + 1: 0], vecs[i < size-2 ? i + 2: (i == size-2 ? 0 : 1)])).getmag() > 10)
                {
                    //cout<<" approved\n";
                    scount++;
                }
            }
        }
        if(!scount && s)
        {
            //cout<<" one counted compensatedly\n";
            scount++;
        }
        //cout<<" second count: "<<scount<<endl;
        return scount;
    }
    else if(count > 1) return (count % 2);
    else return 0;
}
template <class T> bool p_poly(VECTOR2<T>* vecs, const VECTOR2<T>& point, int size)
{
    return in_polyB(vecs, point, point + VECTOR2<T>(2000, 0), size);
}
template <class T> bool in_polyB(const vector<VECTOR2<T>>& vecs, const VECTOR2<T>& point, const VECTOR2<T>& term)
{
    int c = 0;
    int count = 0;
    //for(int i = 0; i < vecs.size(); i++)cout<<" vec["<<i<<"] = "<<vecs[i]<<endl;
    for(int i = 0; i < vecs.size(); i++)
    {
        if(intersector_B(point, term, vecs[i], vecs[i != vecs.size()-1 ? i + 1: 0]))
        {
            c++;
            //cout<<" vec["<<i<<"] & vec["<<(i != vecs.size()-1 ? i + 1 : 0)<<"]: "<<intersection(point, term, vecs[i], vecs[i != vecs.size()-1 ? i + 1: 0])<<endl;
            //cout<<" checking intersection point similarities of:\n";
            //cout<<" vertices: "<<i<<(i != vecs.vecs.size()()-1 ? i + 1 : 0)<<intersection(point, term, vecs[i], vecs[i != vecs.size()-1 ? i + 1: 0])<<" and "<<(i != vecs.size()-1? i + 1 : 0)<<(i < vecs.size()-2 ? i + 2: (i == vecs.size()-2 ? 0 : 1))<<intersection(point, term, vecs[i != vecs.size()-1 ? i + 1: 0], vecs[i < vecs.size()-2 ? i + 2: (i == vecs.size()-2 ? 0 : 1)])<<endl;
            if((intersection(point, term, vecs[i], vecs[i != vecs.size()-1 ? i + 1: 0]) - intersection(point, term, vecs[i != vecs.size()-1 ? i + 1: 0], vecs[i < vecs.size()-2 ? i + 2: (i == vecs.size()-2 ? 0 : 1)])).getmag() > 10)
            {
          //      cout<<" approved\n";
                count++;
            }
        }
    }
    if(!count && c)
    {
        //cout<<" one counted compensatedly\n";
        count++;
    }
    //cout<<" count: "<<count<<endl;
    if(count == 1)
    {
        //cout<<" second check (crosses once) => \n";
        int s = 0;
        int scount = 0;
        term *= -1;
        for(int i = 0; i < vecs.size(); i++)
        {
            if(intersector_B(point, term, vecs[i], vecs[i != vecs.size()-1 ? i + 1: 0]))
            {
                s++;
                //cout<<" vec["<<i<<"] & vec["<<(i != vecs.size()-1 ? i + 1 : 0)<<"]: "<<intersection(point, term, vecs[i], vecs[i != size-1 ? i + 1: 0])<<endl;
                //cout<<" checking intersection point similarities of:\n";
                //cout<<" vertices: "<<i<<(i != size-1 ? i + 1 : 0)<<intersection(point, term, vecs[i], vecs[i != vecs.size()-1 ? i + 1: 0])<<" and "<<(i != vecs.size()-1? i + 1 : 0)<<(i < vecs.size()-2 ? i + 2: (i == vecs.size()-2 ? 0 : 1))<<intersection(point, term, vecs[i != vecs.size()-1 ? i + 1: 0], vecs[i < vecs.size()-2 ? i + 2: (i == vecs.size()-2 ? 0 : 1)])<<endl;
                if((intersection(point, term, vecs[i], vecs[i != vecs.size()-1 ? i + 1: 0]) - intersection(point, term, vecs[i != vecs.size()-1 ? i + 1: 0], vecs[i < vecs.size()-2 ? i + 2: (i == vecs.size()-2 ? 0 : 1)])).getmag() > 10)
                {
                    //cout<<" approved\n";
                    scount++;
                }
            }
        }
        if(!scount && s)
        {
            //cout<<" one counted compensatedly\n";
            scount++;
        }
        //cout<<" second count: "<<scount<<endl;
        return scount;
    }
    else if(count > 1) return (count % 2);
    else return 0;
}
template <class T> void rotate_r(const VECTOR2<T>& center, VECTOR2<T>& rotated, double angle)
{
    //cout<<" rotating vector"<<rotated<<" on "<<center<<" by "<<angle<<" degrees\n";
    T dist = (const_cast<VECTOR2<T>&>(center) - rotated).getmag();
    double deg = angle;
    double rad = torad(deg);
    double rdeg = angle_bn(center, rotated);
    double rrad = torad(rdeg);
    double xadd = (double)dist * cos(rrad + rad);
    double yadd = (double)dist * sin(rrad + rad);
    //cout<<" xadd = "<<(double)dist<<" * "<<cos(rrad)<<" = "<<xadd<<endl;
    //cout<<" yadd = "<<(double)dist<<" * "<<sin(rrad)<<" = "<<yadd<<endl;
    //cout<<" sqrt(xadd * xadd + yadd * yadd) = "<<sqrt((xadd * xadd) + (yadd * yadd))<<endl;
    rotated.getx() = center.getx() + (T)xadd;
    rotated.gety() = center.gety() - (T)yadd;
}
template <class T> VECTOR2<T> ret_rotate_r(const VECTOR2<T>& center, const VECTOR2<T>& rotated, double angle)
{
    VECTOR2<T> to_rotate = rotated;
    rotate_r(center, to_rotate, angle);
    return to_rotate;
}
template <class T> void rotate_rC(VECTOR2<T>* vecs, double angle, int size, VECTOR2<T>* point = NULL)
{
    bool p_alive = point;
    point = (point ? point : new VECTOR2<T>);
    *point = (p_alive ? *point : C_x_y_find(vecs, size));
    for(int i = 0; i < size; i++)
    {
        rotate_r(*point, vecs[i], angle);
    }
}
template <class T> void rotate_rC(vector<VECTOR2<T>>& vecs, double angle, VECTOR2<T>* point = NULL)
{
    bool p_alive = point;
    point = (point ? point : new VECTOR2<T>);
    *point = (p_alive ? *point : C_x_y_find(vecs));
    for(int i = 0; i < vecs.size();i++)
    {
        rotate_r(*point, vecs[i], angle);
    }
}
template <class T> int INTERSECT(VECTOR2<T>* vecs1, VECTOR2<T>* vecs2, int size1, int size2)
{
    int count = 0;
    for(int i = 0; i < size1; i++)
    {
        for(int j = 0; j < size2; j++)
        count += (int)intersector_B(vecs1[i], vecs1[i != size1 - 1 ? i + 1 : 0], vecs2[j], vecs2[j != size2 - 1 ? j + 1 : 0]);
    }
    return count;
}
template <class T> void printout(VECTOR2<T>* vecs, int size)
{
    for(int i = 0; i < size; i++)cout<<vecs[i]<<endl;
}
template <class T> int most_close_vertex(VECTOR2<T>* vecs, float angle, int size)
{
    float* mags = new float[size];
    for(int i = 0; i < size; i++)mags[i] = p_l_mag<T>(vecs[i], VECTOR2<T>(2000 * cos(torad(angle)), 2000 * sin(torad(angle))), angle + 90);
    int index = -1;
    float smag = numeric_limits<float>::max();
    for(int i = 0; i < size; i++){
        if(smag > mags[i]){
            index = i;
            smag = mags[i];
        }
    }
    return index;
}