#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using   namespace   std;
const   int N = 1e2 + 5;

int T, n, a[N], d[N][N];

int main()
{
    scanf("%d", &T);
    for(int c = 1;  c <= T; c ++)
    {
        scanf("%d", &n);
        for(int i = 1; i <= n; i ++)
            scanf("%d", &a[i]);
        for(int i = 1; i <= n; i ++)
            for(int j = i; j <= n; j ++)
                d[i][j] = j - i + 1;
        for(int i = n - 1; i; i --)
        {
            for(int j = i + 1; j <= n; j ++)
            {
                d[i][j] = d[i + 1][j] + 1;
                // k <= j though d[k + 1][j] = 0!
                // There maybe a match from i to j = d[i + 1][k]
                for(int k = i + 1; k <= j; k ++)
                    if(a[i] == a[k])
                        d[i][j] = min(d[i][j], d[i + 1][k] + d[k + 1][j]);
            }
        }
        printf("Case %d: %d\n", c, d[1][n]);
    }
    return 0;
}
