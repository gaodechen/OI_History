#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <cmath>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
const   int N = 110;
const   double eps = 1e-6;
const	double INF = 0x3f3f3f3f;

struct BPG
{
    int n, link[N];
    bool visx[N], visy[N];
    double w[N][N], slack[N];
    double markx[N], marky[N];

    bool Augment( int u )
    {
        visx[u] = 1;
        for( int v = 1; v <= n; v ++ )
        {
            if( visy[v] )
                continue ;
            double t = markx[u] + marky[v] - w[u][v];
            // Be carefule here... You should use abs()
            if( fabs( t ) < eps )
            {
                visy[v] = 1;
                if( link[v] == -1 || Augment( link[v] ) )
                {
                    link[v] = u;
                    return true;
                }
            }
            else if( slack[v] > t )
                slack[v] = t;
        }
        return false;
    }

    inline void Interface()
    {
        scanf( "%d", &n );
        double x[N][2], y[N][2];
        for( int i = 1; i <= n; i ++ )
            scanf( "%lf%lf", &x[i][0], &x[i][1] );
        for( int i = 1; i <= n; i ++ )
            scanf( "%lf%lf", &y[i][0], &y[i][1] );
        for( int i = 1; i <= n; i ++ )
        {
            for( int j = 1; j <= n; j ++ )
            {
                double d1 = x[i][0] - y[j][0];
                double d2 = x[i][1] - y[j][1];
                w[j][i] = -sqrt( d1 * d1 + d2 * d2 );
            }
        }
        set( link, -1 );
        for( int i = 1; i <= n; i ++ )
            markx[i] = -INF, marky[i] = 0;
        for( int i = 1; i <= n; i ++ )
            for( int j = 1; j <= n; j ++ )
                if( markx[i] < w[i][j] )
                    markx[i] = w[i][j];
        for( int u = 1; u <= n; u ++ )
        {
            for( int i = 1; i <= n; i ++ )
                slack[i] = INF;
            while( true )
            {
                set( visx, 0 );
                set( visy, 0 );
                if( Augment( u ) )
                    break ;
                double d = INF;
                for( int i = 1; i <= n; i ++ )
                    if( !visy[i] && d > slack[i] )
                        d = slack[i];
                for( int i = 1; i <= n; i ++ )
                    if( visx[i] )
                        markx[i] -= d;
                for( int i = 1; i <= n; i ++ )
                {
                    if( visy[i] )
                        marky[i] += d;
                    else
                        slack[i] -= d;
                }
            }
        }
        for( int i = 1; i <= n; i ++ )
            printf( "%d\n", link[i] );
        return ;
    }
} g;

int main()
{
    g.Interface();
    return 0;
}
