#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 2e2 + 5;
const   int Q = 5e4 + 5;
const   int INF = 0x3f3f3f3f;

struct Item
{
    int u, v, t, ans;
} e[Q];

bool mark[N];
int n, m, q, t[N], G[N][N];

int main()
{
    scanf( "%d%d", &n, &m );
    for( int i = 1; i <= n; i ++ )
        scanf( "%d", &t[i] );
    memset( G, INF, sizeof( G ) );
    for( int i = 0; i < m; i ++ )
    {
        int u, v, w;
        scanf( "%d%d%d", &u, &v, &w );
        u ++, v ++;
        G[u][v] = G[v][u] = w;
    }
    scanf( "%d", &q );
    for( int i = 1; i <= q; i ++ )
    {
        scanf( "%d%d%d", &e[i].u, &e[i].v, &e[i].t );
        e[i].u ++, e[i].v ++, e[i].ans = -1;
    }
    for( int k = 1; k <= n; k ++ )
    {
        for( int i = 1; i <= n; i ++ )
            for( int j = 1; j <= n; j ++ )
                if( G[i][k] < INF && G[k][j] < INF )
                    G[i][j] = min( G[i][j], G[i][k] + G[k][j] );
        mark[k] = 1;
        for( int i = 1; i <= q; i ++ )
        {
            int u = e[i].u, v = e[i].v, a = e[i].t;
            if( a >= t[k] && mark[u] && mark[v] )
                if( G[u][v] < INF )
                    e[i].ans = G[u][v];
        }
    }
    for( int i = 1; i <= q; i ++ )
        printf( "%d\n", e[i].ans );
    return 0;
}
