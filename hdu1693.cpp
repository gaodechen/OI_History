#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef long long   data;
const   int N = 12, M = ( 1 << 12 );

bool a[N][N];
int T, c, n, m;
data d[N][N][M];

int main()
{
    scanf( "%d", &T );
    while( T -- )
    {
        scanf( "%d%d", &n, &m );
        for( int i = 1; i <= n; i ++ )
            for( int j = 1; j <= m; j ++ )
                cin >> a[i][j];
        d[0][m][0] = 1;
        for( int i = 1; i <= n; i ++ )
        {
            for( int j = 0; j < ( 1 << m ); j ++ )
                d[i][0][(j<<1)] = d[i-1][m][j];
            for( int j = 1; j <= m; j ++ )
            {
                for( int s = 0; s < ( 1 << m << 1 ); s ++ )
                {
                    int p = 1 << j, q = p >> 1;
                    bool x = s & p, y = s & q;
                    if( a[i][j] )
                    {
                        d[i][j][s] = d[i][j-1][s^p^q];
                        if( x != y )
                            d[i][j][s] += d[i][j-1][s];
                    }
                    else
                    {
                        if( !x && !y )
                            d[i][j][s] = d[i][j-1][s];
                        else
                            d[i][j][s] = 0;
                    }
                }
            }
        }
        printf( "Case %d: There are %lld ways to eat the trees.\n", ++ c, d[n][m][0] );
    }
    return 0;
}

// Note: http://www.cnblogs.com/crazyac/articles/1966135.html
