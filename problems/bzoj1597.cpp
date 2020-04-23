#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
typedef long long   data;
const   int N = 5e4 + 5;

struct Item
{
    int x, y;

    bool operator < (const Item &b) const
    {
        return x < b.x || (x == b.x && y < b.y);
    }
} e[N];

data x[N], y[N], f[N];
int m, n, head, tail, q[N];

inline data slope(int a, int b)
{
    return (f[a] - f[b]) / (y[b+1] - y[a+1]);
}

int main()
{
    scanf("%d", &m);
    for(int i = 1; i <= m; i ++)
        scanf("%d%d", &e[i].x, &e[i].y);
    sort(e + 1, e + m + 1);
    for(int i = 1; i <= m; i ++)
    {
        while(n && y[n] <= e[i].y)
            n --;
        x[++ n] = e[i].x;
        y[n] = e[i].y;
    }
    for(int i = 1; i <= n; i ++)
    {
        while(head < tail && slope(q[head+1], q[head]) < x[i])
            head ++;
        int h = q[head];
        f[i] = f[h] + x[i] * y[h+1];
        while(head < tail && slope(i, q[tail]) < slope(q[tail-1], q[tail]))
            tail --;
        q[++tail] = i;
    }
    printf("%lld\n", f[n]);
    return 0;
}
