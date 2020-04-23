#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

struct Vector
{
    #define Point Vector

    double x, y;

    Vector(int x, int y): x(x), y(y) {}
    Vector() {}

    double operator ^ (const Vector &b) const
    {
        return x * b.y - y * b.x;
    }

    Vector operator - (const Vector &b) const
    {
        return Vector(x - b.x, y - b.y);
    }

    bool operator < (const Point &b) const
    {
        return ((*this - Point(0, 0)) ^ (b - Point(0, 0))) > 0;
    }
} p[50];

int main(int argc, char **argv)
{
    int n = 0, x, y;
    while(cin >> p[n].x >> p[n].y)
        n ++;
    sort(p + 1, p + n);
    printf("(0,0)\n");
    for(int i = 1; i < n; i ++)
        printf("(%d,%d)\n", (int) p[i].x, (int) p[i].y);
    return 0;
}
