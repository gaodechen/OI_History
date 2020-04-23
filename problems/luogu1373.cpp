#include    <cstdio>
#include    <iostream>

using   namespace   std;
const   int N = 8e2 + 5;
const   int M = 1e9 + 7;

int n, m, q;
int a[N][N], d[N][N][17][2];

int main()
{
    scanf( "%d%d%d", &n, &m, &q );
    for( int i = 1; i <= n; i ++ )
        for( int j = 1; j <= m; j ++ )
            scanf( "%d", &a[i][j] );
    for( int i = 1; i <= n; i ++ )
        for( int j = 1; j <= m; j ++ )
            d[i][j][a[i][j]][0] = 1;
    q ++;
    int ans = 0;
    for( int i = 1; i <= n; i ++ )
    {
        for( int j = 1; j <= m; j ++ )
        {
            for( int k = 0; k < q; k ++ )
            {
                d[i][j][k][0] += d[i][j-1][(k-a[i][j]+q)%q][1];
                d[i][j][k][0] += d[i-1][j][(k-a[i][j]+q)%q][1];
                d[i][j][k][1] += d[i][j-1][(k+a[i][j])%q][0];
                d[i][j][k][1] += d[i-1][j][(k+a[i][j])%q][0];
                if(d[i][j][k][0] >= M)
                    d[i][j][k][0] %= M;
                if(d[i][j][k][1] >= M)
                    d[i][j][k][1] %= M;
            }
            ans += d[i][j][0][1];
            if(ans >= M)
                ans %= M;
        }
    }  
    printf( "%d\n", ans );
    return 0;
}
