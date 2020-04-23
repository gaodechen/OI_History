#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long data;
const int N = 1e5 + 5;

inline int in()
{
	int k = 0, c = '\0', f = 1;
	for(; c > '9' || c < '0';)
        if((c = getchar()) == '-')
            f = 0;
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return f ? k : -k;
}

struct Point
{
    int x, y, area;

    data operator ^ (const Point &b) const
    {
        return (data) x * b.y - (data) y * b.x;
    }

    bool operator < (const Point &b) const
    {
        if(area == b.area)
           return ((*this) ^ b) > 0;
        return area < b.area;
    }
} p[N];

int n;

int main(int argc, char **argv)
{
    if((n = in()) < 3)
        return puts("0"), 0;
    for(int i = 0; i < n; i ++)
    {
        p[i].x = in(), p[i].y = in();
        if(p[i].x >= 0)
        {
            if(p[i].y >= 0) p[i].area = 1;
            else p[i].area = 4;
        }
        else
        {
            if(p[i].y >= 0) p[i].area = 2;
            else p[i].area = 3;
        }
    }
    sort(p, p + n);
    data ans = (data) n * (n - 1) * (n - 2) / 6;
    for(int l = 0, r = 1, s = 0; l < n; l ++, s--)
    {
        while((p[l] ^ p[r]) >= 0 && (r + 1) % n != l)
            r ++, s ++, r %= n;
        ans -= (data) s * (s - 1) >> 1;
    }
    printf("%lld", ans);
    return 0;
}
