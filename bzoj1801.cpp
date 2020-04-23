#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

#define     rep(i, l, r)    for(int i = l; i <= r; i ++)

using   namespace   std;
const   int N = 1e2 + 5;
const   int MOD = 9999973;
typedef long long   data;

int n, m;
data d[N][N][N];

inline data C(int x)
{
    return x * (x - 1) >> 1;
}

int main()
{
    scanf("%d%d", &n, &m);
    d[0][0][0] = 1LL;
    rep(i, 1, n) rep(j, 0, m) rep(k, 0, m - j)
    {
        data &q = d[i][j][k];
        q = d[i-1][j][k];
        if(j > 0) q += d[i-1][j-1][k] * (m - j - k + 1);
        if(k > 0) q += d[i-1][j+1][k-1] * (j + 1);
        if(j > 1) q += d[i-1][j-2][k] * C(m - j - k + 2);
        if(k > 0) q += d[i-1][j][k-1] * (m - j - k + 1) * j;
        if(k > 1) q += d[i-1][j+2][k-2] * C(j + 2);
        if(q >= MOD)
            q %= MOD;
    }
    data ans = 0;
    rep(j, 0, m) rep(k, 0, m - j)
    {
        ans += d[n][j][k];
        if(ans >= MOD)
            ans %= MOD;
    }
    printf("%lld\n", ans);
    return 0;
}
