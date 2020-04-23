#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <cmath>

#define     rep( i, l, r )      for( int i = l; i <= r; i ++ )

using	namespace	std;
const   int N = 11;
const   double INF = 1e18;

int n, m, K;
double d[N][N][N][N][N], g[N][N], avg;

double Search( int x, int y, int a, int b, int p )
{
    double &q = d[x][y][a][b][p];
    if( q != -1 )
        return q;
    if( p == 1 )
    {
        double tmp = g[a][b] - g[x-1][b] - g[a][y-1] + g[x-1][y-1] - avg;
        return (q = tmp * tmp);
    }
    double ans = INF;
    rep( i, x, a - 1 ) rep( k, 1, p - 1 )
    {
        double tmp = Search( x, y, i, b, k );
        tmp += Search( i + 1, y, a, b, p - k );
        ans = min(ans, tmp);
    }
    rep( j, y, b - 1 ) rep( k, 1, p - 1 )
    {
        double tmp = Search( x, y, a, j, k );
        tmp += Search( x, j + 1, a, b, p - k );
        ans = min( ans, tmp );
    }
    return ( q = ans );
}

int main()
{
    scanf( "%d%d%d", &n, &m, &K );
    rep( i, 1, n ) rep( j, 1, m )
        scanf( "%lf", &g[i][j] );
    rep( i, 1, n ) rep( j, 1, m )
        g[i][j] += g[i][j-1];
    rep( j, 1, m ) rep( i, 1, n )
        g[i][j] += g[i-1][j];
    avg = ( double ) g[n][m] / K;
    rep( x, 1, n ) rep( y, 1, m )
        rep( a, 1, n ) rep( b, 1, m )
            rep( k, 1, K )
                d[x][y][a][b][k] = -1;
    double ans = Search( 1, 1, n, m, K );
    printf( "%.2lf\n", sqrt( ans / K ) );
    return 0;
}
