#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 1e3 + 5;
const   int M = 5e1 + 5;

int t, n, m, ind, d[N][M];

int main()
{
    scanf( "%d", &t );
    while( t -- )
    {
        memset( d, 0, sizeof( d ) );
        scanf( "%d%d%d", &ind, &m, &n );
        for( int i = 1; i <= n; i ++ )
            d[i][1] = i;
        for( int j = 2; j <= m; j ++ )
        {
            for( int i = 1; i <= n; i ++ )
            {
                d[i][j] = 0x3f3f3f3f;
                for( int k = 1; k <= i; k ++ )
                    d[i][j] = min( d[i][j], max( d[k-1][j-1], d[i-k][j] ) + 1 );
            }
        }
        printf( "%d %d\n", ind, d[n][m] );
    }
    return 0;
}
