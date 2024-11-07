template <class T> VECTOR2<T> intersection(const VECTOR2<T>& vec11, const VECTOR2<T>& vec12, const VECTOR2<T>& vec21, const VECTOR2<T>& vec22, bool yi = true)
{
    double m1 = (double)((double)((yi ? -1 : 1) * dy(vec11, vec12)) / (double)dx(vec11, vec12));
    double m2 = (double)((double)((yi ? -1 : 1) * dy(vec21, vec22)) / (double)dx(vec21, vec22));
    int x1 = vec11.getx(), x2 = vec21.getx(), y1 = vec11.gety(), y2 = vec21.gety();
    int x, y;
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
        x = ((yi ? -1 : 1) * (m1 * x1 - m2 * x2) + y2 - y1)/(m1 - m2);
        y = (yi ? -1 : 1) * m1 * (x - x1) + y1;
    }
    return VECTOR2<T>(x, y);
}
template <class T> double angle_bn(const VECTOR2<T>& v1, const VECTOR2<T>& v2, bool yi = true)
{
    T y = dy(v1, v2);
    T x = dx(v1, v2);
    double rang = (x ? (180 / PI) * atan((float)((yi ? -y : y)/x)) : (y > 0 ? (yi ? -90 : 90) : (yi ? 90 : -90)));
    bool xl = (x < 0);
    bool yl = (y < 0);
    if(xl && yl){rang += 180;return rang;}
    else if(xl){rang = 180 - (-1 * (rang)); return rang;}
    else if(yl){rang += 360; return rang;}
    else return rang;
}