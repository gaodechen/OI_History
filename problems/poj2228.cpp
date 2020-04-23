#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 3831;
const   int INF = 0x3f3f3f3f;

int n, m, ans, u[N], d[2][N][2];

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &u[i]);

    memset(d, 128, sizeof(d));
    d[1][1][1] = d[1][0][0] = 0;
    for(int i = 2; i <= n; i ++)
    {
        int p = i & 1, q = p ^ 1;
        d[p][0][0] = 0;
        for(int j = 1; j <= min(n, m); j ++)
        {
            d[p][j][0] = max(d[q][j][1], d[q][j][0]);
            d[p][j][1] = max(d[q][j-1][0], d[q][j-1][1] + u[i]);
        }
    }
    ans = max(d[n&1][m][0], d[n&1][m][1]);

    memset(d, 128, sizeof(d));
    d[1][1][1] = u[1];
    for(int i = 2; i <= n; i ++)
    {
        int p = i & 1, q = p ^ 1;
        d[p][0][0] = 0;
        for(int j = 1; j <= min(n, m); j ++)
        {
            d[p][j][0] = max(d[q][j][1], d[q][j][0]);
            d[p][j][1] = max(d[q][j-1][0], d[q][j-1][1] + u[i]);
        }
    }
    ans = max(ans, d[n&1][m][1]);

    printf("%d\n", ans);
    return 0;
}

