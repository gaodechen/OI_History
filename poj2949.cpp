#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 7e2 + 5;
const   int M = 1e5 + 5;
const   double eps = 1e-4;

struct Edge
{
    int v, w, next;
} e[M];

bool cyl, vis[N];
double dis[N], avg;
int mark[N], head[N];
int n, up, tot, sig;

inline void AddEdge( int u, int v, int w )
{
    e[++sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

void DFS( int u )
{
    vis[u] = 1;
    for( int i = head[u]; i; i = e[i].next )
    {
        int v = e[i].v;
        double w = dis[u] + e[i].w - avg;
        if( dis[v] < w )
        {
            dis[v] = w;
            if( vis[v] )
            {
                cyl = 1;
                return ;
            }
            DFS( v );
            if( cyl )
                return ;
        }
    }
    vis[u] = 0;
    return ;
}

inline bool SPFA( double k )
{
    cyl = false, avg = k;
    memset( dis, 0, sizeof( dis ) );
    memset( vis, 0, sizeof( vis ) );
    for( int i = 1; i <= tot; i ++ )
    {
        DFS( i );
        if( cyl )
            return 1;
    }
    return 0;
}

int main()
{
    while( scanf( "%d", &n ) && n )
    {
        up = sig = tot = 0;
        memset( mark, 0, sizeof( mark ) );
        memset( head, 0, sizeof( head ) );
        for( int i = 0; i < n; i ++ )
        {
            char s[N];
            scanf( "%s", s );
            int len = strlen( s );
            if( len > up )
                up = len;
            int a = ( s[0] - 'a' ) * 26 + s[1] - 'a';
            int b = ( s[len-2] - 'a' ) * 26 + s[len-1] - 'a';
            if( !mark[a] )
                mark[a] = ++ tot;
            if( !mark[b] )
                mark[b] = ++ tot;
            a = mark[a], b = mark[b];
            AddEdge( a, b, len );
        }
        bool flag = false;
        double l = 0, r = 1e3;
        while( r - l > eps )
        {
            double mid = ( l + r ) / 2;
            if( SPFA( mid ) )
                l = mid, flag = true;
            else
                r = mid;
        }
        if( flag )
            printf( "%.2lf\n", l );
        else
            printf( "No solution.\n" );
    }
    return 0;
}
