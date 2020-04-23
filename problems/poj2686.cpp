#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>

using   namespace   std;
const   double INF = 1e18;
const   int N = 32, M = 300;

bool vis[M];
int n, m, p, s, t;
double G[N][N], d[N][M], h[N];

int main()
{
    while( scanf( "%d%d%d%d%d", &n, &m, &p, &s, &t ) && n )
    {
        memset( vis, 0, sizeof( vis ) );
        for( int i = 1; i <= m; i ++ )
            for( int j = 1; j <= m; j ++ )
                G[i][j] = 0;
        for( int i = 1; i <= m; i ++ )
            for( int k = 0; k < ( 1 << n ); k ++ )
                d[i][k] = INF;
        for( int i = 1; i <= n; i ++ )
            scanf( "%lf", &h[i] );
        for( int i = 0; i < p; i ++ )
        {
            int u, v, w;
            scanf( "%d%d%d", &u, &v, &w );
            G[u][v] = G[v][u] = w;
        }
        queue< int > q; q.push( s );
        for( int i = 0; i < ( 1 << n ); i ++ )
            d[s][i] = 0;
        while( !q.empty() )
        {
            int u = q.front(); q.pop();
            vis[u] = 0;
            for( int v = 1; v <= m; v ++ )
            {
                if( !G[u][v] )
                    continue ;
                for( int mask = 0; mask < ( 1 << n ); mask ++ )
                {
                    if( d[u][mask] >= INF )
                        continue ;
                    for( int j = 1; j <= n; j ++ )
                    {
                        if( mask & ( 1 << ( j - 1 ) ) )
                            continue ;
                        if( d[v][mask|(1<<(j-1))] > d[u][mask] + G[u][v] / h[j] )
                        {
                            d[v][mask|(1<<(j-1))] = d[u][mask] + G[u][v] / h[j];
                            if( !vis[v] )
                            {
                                q.push( v );
                                vis[v] = 1;
                            }
                        }
                    }
                }
            }
        }
        double ans = INF;
        for( int i = 0; i < ( 1 << n ); i ++ )
            ans = min( ans, d[t][i] );
        if( ans < INF )
            printf( "%.3lf\n", ans );
        else
            printf( "Impossible\n" );
    }
    return 0;
}
