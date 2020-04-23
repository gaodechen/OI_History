#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const   int N = 2e2 + 5;

bool d[N][N][5];
int n, w[5], m[255];
char h[5][17][2], str[N], t[4];

int main()
{
    t[1] = 'W', t[2] = 'I', t[3] = 'N', t[4] = 'G';
    m['W'] = 1, m['I'] = 2, m['N'] = 3, m['G'] = 4;
    for( int i = 1; i <= 4; i ++ )
        scanf( "%d", &w[i] );
    for( int i = 1; i <= 4; i ++ )
        for( int j = 1; j <= w[i]; j ++ )
            scanf( "%s", h[i][j] );
    scanf( "%s", str + 1 );
    n = strlen( str + 1 );
    for( int i = 1; i <= n; i ++ )
        d[i][i][m[(int)str[i]]] = 1;
    for( int len = 2; len <= n; len ++ )
    {
        for( int i = 1; i + len - 1 <= n; i ++ )
        {
            int j = i + len - 1;
            for( int k = i; k < j; k ++ )
            {
                for( int g = 1; g <= 4; g ++ )
                {
                    for( int c = 1; c <= w[g]; c ++ )
                    {
                        int a = m[(int)h[g][c][0]], b = m[(int)h[g][c][1]];
                        d[i][j][g] |= d[i][k][a] && d[k+1][j][b];
                    }
                }
            }
        }
    }
    bool flag = false;
    for( int i = 1; i <= 4; i ++ )
    {
        if( d[1][n][i] )
        {
            flag = true;
            printf( "%c", t[i] );
        }
    }
    if( !flag )
        printf( "The name is wrong!\n" );
    return 0;
}
