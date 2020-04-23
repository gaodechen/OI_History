#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e2 + 5;
const   int M = 5e3 + 5;
const   int INF = 0x3f3f3f3f;

bool cut[M];
int ind, n, m, sig, head[N], G[N][N];
int dfn[N], low[N], mark[N], pre[N], d[N];

struct Item
{
    int u, v, w;
} p[M];

struct Edge
{
    int v, w, k, next;
} e[M+M];

inline void AddEdge( int u, int v, int w, int k )
{
    e[++sig].v = v, e[sig].w = w, e[sig].k = k;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

int Find( int u )
{
    if( u != pre[u] )
        pre[u] = Find( pre[u] );
    return pre[u];
}

inline void Union( int u, int v )
{
    pre[Find(v)] = Find( u );
    return ;
}

void Tarjan( int u, int p )
{
    dfn[u] = low[u] = ++ ind;
    for( int i = head[u]; i; i = e[i].next )
    {
        int v = e[i].v;
        if( v == p )
            continue ;
        if( !dfn[v] )
        {
            Tarjan( v, u );
            low[u] = min( low[u], low[v] );
            if( dfn[u] < low[v] )
                cut[i] = 1;
            else
                Union( u, v );
        }
        else
            low[u] = min( low[u], dfn[v] );
    }
    return ;
}

int main()
{
    freopen( "in", "r", stdin );
    scanf( "%d%d", &n, &m );
    for( int i = 1; i <= n; i ++ )
        pre[i] = i;
    memset( G, INF, sizeof( G ) );
    for( int i = 0; i < m; i ++ )
    {
        int u, v, w;
        scanf( "%d%d%d", &u, &v, &w );
        p[i].u = u, p[i].v = v, p[i].w = w;
        G[u][v] = G[v][u] = min( G[u][v], w );
    }
    for( int k = 1; k <= n; k ++ )
        for( int i = 1; i <= n; i ++ )
            for( int j = 1; j <= n; j ++ )
                G[i][j] = min( G[i][j], G[i][k] + G[k][j] );
    for( int i = 0; i < m; i ++ )
    {
        int u = p[i].u, v = p[i].v, w = p[i].w;
        if( G[1][u] + w + G[v][n] == G[1][n] )
            AddEdge( u, v, w, i );
        else if( G[1][v] + w + G[u][n] == G[1][n] )
            AddEdge( v, u, w, i );
    }
    for( int i = 1; i <= n; i ++ )
        if( !dfn[i] )
            Tarjan( i, 0 );
    for( int i = 1; i <= n; i ++ )
        Find( i );
    if( pre[1] == pre[n] )
    {
        printf( "0\n" );
        return 0;
    }
    int tmp = G[1][n], t = -1, s;
    for( int u = 1; u <= n; u ++ )
    {
        if( !( pre[u] == pre[1] || pre[u] == pre[n] ) )
            continue ;
        for( int i = head[u]; i; i = e[i].next )
        {
            int v = e[i].v;
            if( pre[v] != pre[u] && ( pre[v] == pre[1] || pre[v] == pre[n] ) )
                if( cut[i] && e[i].w > t )
                    t = e[i].w, s = e[i].k;
        }
    }
    memset( G, INF, sizeof( G ) );
    for( int i = 0; i < m; i ++ )
    {
        int u = p[i].u, v = p[i].v, w = p[i].w;
        if( i == s )
            w += w;
        G[u][v] = min( G[u][v], w );
    }
    for( int k = 1; k <= n; k ++ )
        for( int i = 1; i <= n; i ++ )
            for( int j = 1; j <= n; j ++ )
                G[i][j] = min( G[i][j], G[i][k] + G[k][j] );
    printf( "%d\n", G[1][n] - tmp );
    return 0;
}
