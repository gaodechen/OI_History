#include    <cstdio>
#include    <cstring>
#include    <iostream>

#define     set( p, k )     memset( p, k, sizeof( p ) )

using   namespace   std;
const   int N = 30000;
const   int M = 60000;

struct SCC
{
    struct Edge
    {
        int v, next;
    } e[M];

    bool vis[N];
    int top, sig, ont, index, head[N];
    int mark[N], dfn[N], stack[N], low[N];

    inline void Init()
    {
        set( dfn, 0 ), set( low, 0 );
        set( vis, 0 ), set( head, 0 );
		set( mark, 0 ), set( stack, 0 );
        ont = sig = top = index = 0;
        return ;
    }

    inline void AddEdge( int u, int v )
    {
        e[++sig].v = v;
        e[sig].next = head[u];
        head[u] = sig;
        return ;
    }

    void Tarjan( int u )
    {
        dfn[u] = low[u] = ++ index;
        stack[++top] = u, vis[u] = 1;
        for( int i = head[u]; i; i = e[i].next )
        {
            int &v = e[i].v;
            if( !dfn[v] )
            {
                Tarjan( v );
                low[u] = min( low[u], low[v] );
            }
            else if( vis[v] )
                low[u] = min( low[u], dfn[v] );
        }
        if( dfn[u] == low[u] )
        {
            int v;
            ont ++;
            do
            {
                v = stack[top--];
                mark[v] = ont;
                vis[v] = 0;
            }
            while( u != v && top );
        }
        return ;
    }
} g;

int n, m, out[N];

int main()
{
    while( scanf( "%d%d", &n, &m ) == 2 )
    {
        g.Init();
        set( out, 0 );
        for( int i = 0; i < m; i ++ )
        {
            int u, v;
            scanf( "%d%d", &u, &v );
            g.AddEdge( u, v );
        }
        for( int i = 1; i <= n; i ++ )
            if( !g.dfn[i] )
                g.Tarjan( i );
        for( int u = 1; u <= n; u ++ )
            for( int i = g.head[u]; i; i = g.e[i].next )
                if( g.mark[u] != g.mark[g.e[i].v] )
                    out[g.mark[u]] ++;
        int sum = 0, p;
        for( int i = 1; i <= g.ont; i ++ )
            if( !out[i] )
                sum ++, p = i;
        if( sum == 1 )
        {
            sum = 0;
            for( int i = 1; i <= n; i ++ )
                if( g.mark[i] == p )
                    sum ++;
            printf( "%d\n", sum );
        }
        else
            printf( "0\n" );
    }
    return 0;
}
