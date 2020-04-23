#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 6e2 + 5;
const   int M = 2e5 + 5;
const   int S = 1e7 + 5;
const   int INF = 0x3f3f3f3f;

char buf[S], *s;

inline int in()
{
    int k = 0;
    while( *s > '9' || *s < '0' )
        s ++;
    while( *s <= '9' && *s >= '0' )
    {
        k = k * 10 + *s - '0';
        s ++;
    }
    return k;
}

struct Edge
{
    int v, w, next;
} e[M];

bool ins[N];
int n, m1, m2, sig, ind, cnt, top, head[N];
int dfn[N], low[N], d[N][N], stack[N], mark[N], tmp[N];

inline int ABS( int x )
{
    if( x < 0 )
        return -x;
    return x;
}

inline void AddEdge( int u, int v, int w )
{
    e[++sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

bool cmp( const int &a, const int &b )
{
    return mark[a] < mark[b];
}

void Tarjan( int u )
{
    dfn[u] = low[u] = ++ ind;
    stack[++top] = u, ins[u] = 1;
    for( int i = head[u]; i; i = e[i].next )
    {
        int v = e[i].v;
        if( !dfn[v] )
        {
            Tarjan( v );
            low[u] = min( low[u], low[v] );
        }
        else if( ins[v] )
            low[u] = min( low[u], dfn[v] );
    }
    if( dfn[u] == low[u] )
    {
        int v;
        cnt ++;
        do
        {
            v = stack[top--];
            mark[v] = cnt;
            ins[v] = 0;
        }
        while( u != v );
    }
    return ;
}

int main()
{
    int len = fread( buf, 1, S, stdin );
    buf[len] = '\0', s = buf;
    n = in(), m1 = in(), m2 = in();
    memset( d, INF, sizeof( d ) );
    for( int i = 1; i <= m1; i ++ )
    {
        int u = in(), v = in();
        AddEdge( u, v, 1 );
        AddEdge( v, u, -1 );
        d[u][v] = min( d[u][v], 1 );
        d[v][u] = min( d[v][u], -1 );
    }
    for( int i = 1; i <= m2; i ++ )
    {
        int u = in(), v = in();
        AddEdge( v, u, 0 );
        d[v][u] = min( d[v][u], 0 );
    }
    for( int i = 1; i <= n; i ++ )
        d[i][i] = 0;
    for( int i = 1; i <= n; i ++ )
        if( !dfn[i] )
            Tarjan( i );
    for( int k = 1; k <= n; k ++ )
        for( int i = 1; i <= n; i ++ )
            if( d[i][k] != INF && mark[i] == mark[k] )
                for( int j = 1; j <= n; j ++ )
                    if( d[k][j] != INF && mark[j] == mark[k] )
                        d[i][j] = min( d[i][j], d[i][k] + d[k][j] );
    for( int i = 1; i <= n; i ++ )
    {
        if( d[i][i] < 0 )
        {
            printf( "NIE\n" );
            return 0;
        }
    }
    for( int i = 1; i <= n; i ++ )
        tmp[i] = i;
    sort( tmp + 1, tmp + n + 1, cmp );
    int ans = 0;
    for( int i = 1; i <= n; )
    {
        int j = i;
        while( j <= n && mark[tmp[i]] == mark[tmp[j]] )
            j ++;
        int del = 0;
        for( int a = i; a < j; a ++ )
            for( int b = i; b < j; b ++ )
                del = max( del, ABS( d[tmp[a]][tmp[b]] ) );
        ans += del + 1;
        i = j;
    }
    printf( "%d\n", ans );
    return 0;
}
