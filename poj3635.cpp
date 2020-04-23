#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>

using   namespace   std;
const   int N = 1e3 + 5;
const   int M = 2e4 + 5;
const   int INF = 0x3f3f3f3f;

struct Edge
{
    int v, w, next;
} e[M];

bool vis[N];
int n, m, q, c, s, t, sig;
int cost[N], head[N], d[N][101];

inline void AddEdge( int u, int v, int w )
{
    e[++sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

inline int SPFA()
{
    queue< int > q;
    memset( d, INF, sizeof( d ) );
    memset( vis, 0, sizeof( vis ) );
    q.push( s );
    for( int i = 0; i <= c; i ++ )
        d[s][i] = cost[s] * i;
    while( !q.empty() )
    {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for( int i = head[u]; i; i = e[i].next )
        {
            bool flag = false;
            int v = e[i].v, w = e[i].w;
            for( int j = w; j <= c; j ++ )
                if( d[v][j-w] > d[u][j] )
                    d[v][j-w] = d[u][j], flag = true;
            if( !flag )
                continue ;
            for( int j = 1; j <= c; j ++ )
                d[v][j] = min( d[v][j], d[v][j-1] + cost[v] );
            if( !vis[v] )
            {
                vis[v] = 1;
                q.push( v );
            }
        }
    }
    int ans = INF;
    for( int i = 0; i <= c; i ++ )
        ans = min( d[t][i], ans );
    return ans;
}

int main()
{
    scanf( "%d%d", &n, &m );
    for( int i = 1; i <= n; i ++ )
        scanf( "%d", &cost[i] );
    for( int i = 0; i < m; i ++ )
    {
        int u, v, w;
        scanf( "%d%d%d", &u, &v, &w );
        u ++, v ++;
        AddEdge( u, v, w );
        AddEdge( v, u, w );
    }
    scanf( "%d", &q );
    for( int i = 0; i < q; i ++ )
    {
        scanf( "%d%d%d", &c, &s, &t );
        s ++, t ++;
        int ans = SPFA();
        if( ans == INF )
            printf( "impossible\n" );
        else
            printf( "%d\n", ans );
    }
    return 0;
}
