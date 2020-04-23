#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
const int N = 30;
const double EPS = 1e-7;
const double delta = 0.9993;
const double T = 0.1;
const double INF = 1e20;

int nextX[] = {0, 0, -1, 1};
int nextY[] = {-1, 1, 0, 0};

struct Point
{
    double x, y, z;
} p[N];

int n;

inline double D(Point a, Point b)
{
    double X = a.x - b.x, Y = a.y - b.y, Z = a.z - b.z;
    return sqrt(X * X + Y * Y + Z * Z);
}

inline double SA()
{
    Point s = p[0];
    // Or: T = 100, delta = 0.9, s.x += (p[k].x - s.y) / maxD * t
    double t = T, ans = INF;
    while(t > EPS)
    {
        int k; double maxD = -INF;
        for(int i = 0; i < n; i ++)
            if(D(s, p[i]) > maxD)
                maxD = D(s, p[k = i]);
        ans = min(ans, maxD);
        s.x += (p[k].x - s.x) * t;
        s.y += (p[k].y - s.y) * t;
        s.z += (p[k].z - s.z) * t;
        t *= delta;
    }
    return ans;
}

int main(int argc, char **argv)
{
    while(scanf("%d", &n) && n)
    {
        for(int i = 0; i < n; i ++)
            scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
        printf("%.5lf\n", SA());
    }
    return 0;
}
