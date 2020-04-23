#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

struct Vector
{
    double x, y;

    Vector(double x, double y): x(x), y(y) {}
    Vector() {}

    inline void in() {scanf("%lf%lf", &x, &y);}

    Vector operator + (const Vector &b) const
    {
        return Vector(x + b.x, y + b.y);
    }

    Vector operator - (const Vector &b) const
    {
        return Vector(x - b.x, y - b.y);
    }

    Vector operator * (const double &t) const
    {
        return Vector(x * t, y * t);
    }

    double operator * (const Vector &b) const
    {
        return x * b.x + y * b.y;
    }

    double operator ^ (const Vector &b) const
    {
        return x * b.y - y * b.x;
    }

    inline double l()
    {
        return sqrt(x * x + y * y);
    }
};

inline double Angle(Vector a, Vector b)
{
    return acos(a * b / a.l() / b.l());
}

inline Vector Rotate(Vector a, double rad)
{
    double x = a.x * cos(rad) - a.y * sin(rad);
    double y = a.x * sin(rad) + a.y * cos(rad);
    return Vector(x, y);
}

typedef Vector Point;

inline Point Intersect(Point p, Vector v, Point q, Vector w)
{
    Vector u = p - q;
    double t = (w ^ u) / (v ^ w);
    return p + v * t;
}

inline Vector f(Point A, Point B, Point C)
{
    Vector v1 = C - B, v2 = B - C;
    double rad = Angle(v1, A - B);
    v1 = Rotate(v1, rad / 3);
    rad = Angle(v2, A - C);
    v2 = Rotate(v2, -rad / 3);
    return Intersect(B, v1, C, v2);
}

int main(int argc, char **argv)
{
    int T;
    scanf("%d", &T);
    while(T --)
    {
        Point A, B, C, D, E, F;
        A.in(), B.in(), C.in();
        D = f(A, B, C), E = f(B, C, A), F = f(C, A, B);
        printf("%lf %lf %lf %lf %lf %lf\n", D.x, D.y, E.x, E.y, F.x, F.y);  
    }
    return 0;
}
