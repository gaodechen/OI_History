#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
typedef long long   data;
const   int N = 3e3 + 5;
const   int M = 3e5 + 5;
const   int MOD = 1e9 + 7;

struct Point
{
    data x, y;

    bool operator < (const Point &b) const
    {
        return x < b.x || (x == b.x && y < b.y);
    }
} e[N];

int n;
data h, w, fac[M], inv[M], d[N];

data Pow(data a, int k)
{
    data r = 1;
    while(k)
    {
        if(k & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        k >>= 1;
    }
    return r;
}

int main()
{
    cin >> h >> w >> n;
    fac[0] = inv[0] = 1;
    for(data i = 1; i <= h + w; i ++)
        fac[i] = (fac[i - 1] * i) % MOD;
    int tmp = max(h, w);
    inv[tmp] = Pow(fac[tmp], MOD - 2);
    for(data i = tmp - 1; i; i --)
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    for(int i = 0; i < n; i ++)
        cin >> e[i].x >> e[i].y;
    e[n].x = h, e[n++].y = w;
    sort(e, e + n);
    for(int i = 0; i < n; i ++)
    {
        int x = e[i].x - 1, y = e[i].y - 1;
        d[i] = fac[x+y] * inv[x] % MOD * inv[y] % MOD;
        for(int j = 0; j < i; j ++)
        {
            if(e[i].x <= e[j].x && e[i].y <= e[j].y)
            {
                int a = x - e[j].x + 1;
                int b = y - e[j].y + 1;
                d[i] = (d[i] - fac[a+b] * inv[a] % MOD * inv[b] % MOD * d[j] % MOD + MOD) % MOD;
            }
        }
    }
    cout << d[n-1] << endl;
    return 0;
}
