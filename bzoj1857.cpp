#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <cmath>

using namespace std;
const double EPS = 1e-5;

struct Point
{
    double x, y;

    inline void in() {scanf("%lf%lf", &x, &y);}

    Point operator - (const Point &b) {return (Point) {b.x - x, b.y - y};}
    Point operator + (const Point &b) {return (Point) {x + b.x, y + b.y};}
    Point operator * (const double &k) {return (Point) {x * k, y * k};}
} A, B, C, D;

inline double sqr(double x) {return x * x;}

double vAB, vCD, vP;

inline double dis(Point a, Point b)
{
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

inline double f(Point p, Point l, Point v, double k)
{
    return dis(p, l + v * k) / vP + dis(l + v * k, l + v) / vCD;
}

inline double Compute(Point p, Point X, Point Y)
{
    Point v = X - Y;
    double l = 0, r = 1, prev = 1e12, next;
    while(true)
    {
        double L = l + (r - l) / 3, R = r - (r - l) / 3;
        double disL = f(p, X, v, L), disR = f(p, X, v, R);
        if(disL < disR)
            r = R, next = disL;
        else
            l = L, next = disR;
        if(fabs(prev - next) < EPS) break;
        prev = next;
    }
    return prev;
}

int main(int argc, char **argv)
{
    A.in(), B.in(), C.in(), D.in();
    scanf("%lf%lf%lf", &vAB, &vCD, &vP);
    Point v = A - B;
    double l = 0, r = 1, prev = 1e12, next;
    while(true)
    {
        double L = l + (r - l) / 3, R = r - (r - l) / 3;
        double disL = dis(A, A + v * L) / vAB + Compute(A + v * L, C, D);
        double disR = dis(A, A + v * R) / vAB + Compute(A + v * R, C, D);
        if(disL < disR)
            r = R, next = disL;
        else
            l = L, next = disR;
        if(fabs(prev - next) < EPS) break;
        prev = next;
    }
    printf("%.2lf", prev);
    return 0;
}
