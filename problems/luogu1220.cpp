#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 51, INF = 0x3f3f3f3f;

int n, v, p[N], s[N], d[N][N][2];

int DP(int l, int r, int x)
{
    if(d[l][r][x] < INF)
        return d[l][r][x];
    int a = INF, b = INF;
    if(x == 0 && l + 1 <= n)
    {
        a = DP(l + 1, r, 0) + (s[n] - s[r] + s[l]) * (p[l+1] - p[l]);
        b = DP(l + 1, r, 1) + (s[n] - s[r] + s[l]) * (p[r] - p[l]);
    }
    else if(r > 1)
    {
        a = DP(l, r - 1, 0) + (s[n] - s[r-1] + s[l-1]) * (p[r] - p[l]);
        b = DP(l, r - 1, 1) + (s[n] - s[r-1] + s[l-1]) * (p[r] - p[r-1]);
    }
    return (d[l][r][x] = min(a, b));
}

int main()
{
    scanf("%d%d", &n, &v);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d%d", &p[i], &s[i]);
        s[i] += s[i-1];
    }
    memset(d, INF, sizeof(d));
    d[v][v][0] = d[v][v][1] = 0;
    int ans = min(DP(1, n, 0), DP(1, n, 1));
    printf("%d\n", ans);
    return 0;
}
