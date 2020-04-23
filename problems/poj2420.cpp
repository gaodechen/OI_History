#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
const int N = 1001;
const double EPS = 1e-6;
const double delta = 0.98;
const double T = 100;
const double INF = 1e20;

int nextX[] = {0, 0, -1, 1};
int nextY[] = {-1, 1, 0, 0};

struct Point
{
    double x, y;

    Point(double x, double y): x(x), y(y) {}
    Point() {}
} p[N];

int n;

inline double D(Point a, Point b)
{
    double p = a.x - b.x, q = a.y - b.y;
    return sqrt(p * p + q * q);
}

inline double S(Point a)
{
    double r = 0;
    for(int i = 0; i < n; i ++)
        r += D(p[i], a);
    return r;
}

inline double SA()
{
    Point s = p[0];
    double t = T, ans = INF;
    while(t > EPS)
    {
        bool flag = true;
        while(flag)
        {
            flag = 0;
            // Or generate a random point
            for(int i = 0; i < 4; i ++)
            {
                Point z(s.x + nextX[i] * t, s.y + nextY[i] * t);
                double d = S(z);
                if(ans > d)
                    ans = d, s = z, flag = 1;
            }
        }
        t *= delta;
    }
    return ans;
}

int main(int argc, char **argv)
{
    while(scanf("%d", &n) == 1)
    {
        for(int i = 0; i < n; i ++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        printf("%.0lf\n", SA());
    }
    return 0;
}
