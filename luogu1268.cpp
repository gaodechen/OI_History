#include    <cstdio>
#include    <iostream>

using   namespace   std;
const   int N = 31, INF = 0x3f3f3f3f;

int n, G[N][N];

int main()
{
    while( scanf( "%d", &n ) && n )
    {
        for( int i = 1; i <= n; i ++ )
            for( int j = i + 1; j <= n; j ++ )
                scanf( "%d", &G[i][j] );
        int ans = G[1][2];
        for( int k = 3; k <= n; k ++ )
        {
            int tmp = INF;
            for( int i = 1; i < k; i ++ )
                for( int j = i + 1; j < k; j ++ )
                    tmp = min( tmp, ( G[i][k] + G[j][k] - G[i][j] ) / 2 );
            ans += tmp;
        }
        printf( "%d\n", ans );
    }
    return 0;
}
