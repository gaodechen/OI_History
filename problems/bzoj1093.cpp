#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>

using   namespace   std;
const   int N = 1e5 + 5;
const   int M = 1e6 + 5;
const   int S = 3e7 + 5;
 
char buf[S], *s;

inline int read()
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
    int v, next;
} e[M], e_[M];

bool ins[N];
int n, m, MOD, sig, cnt, ind, top;
int dfn[N], low[N], mark[N], d[N], w[N], in[N];
int stack[N], head[N], head_[N], sum[N], vis[N];

inline void AddEdge( int u, int v )
{
    e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
    return ;
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
            w[cnt] ++;
            ins[v] = 0;
        }
        while( u != v );
    }
    return ;
}

inline void TopoSort()
{
    queue< int > q;
    for( int i = 1; i <= cnt; i ++ )
    {
        if( !in[i] )
        {
            q.push( i );
            d[i] = w[i];
            sum[i] = 1;
        }
    }
    while( !q.empty() )
    {
        int u = q.front(); q.pop();
        for( int i = head[u]; i; i = e[i].next )
        {
            int v = e[i].v;
            if( -- in[v] == 0 )
                q.push( v );
            if( u == vis[v] )
                continue ;
            if( d[v] < d[u] + w[v] )
            {
                d[v] = d[u] + w[v];
                sum[v] = sum[u];
            }
            else if( d[v] == d[u] + w[v] )
            {
                sum[v] += sum[u];
                if( sum[v] >= MOD )
                    sum[v] %= MOD;
            }
            vis[v] = u;
        }
    }
    return ;
}

int main()
{
    int len = fread( buf, 1, S, stdin );
    buf[len] = '\0', s = buf;
    n = read(), m = read(), MOD = read();
    for( int i = 0; i < m; i ++ )
    {
        int u, v;
        u = read(), v = read();
        AddEdge( u, v );
    }
    for( int i = 1; i <= n; i ++ )
        if( !dfn[i] )
            Tarjan( i );
    memcpy( e_, e, sizeof( e ) );
    memcpy( head_, head, sizeof( head ) );
    memset( head, 0, sizeof( head ) );
    sig = 0;
    for( int u = 1; u <= n; u ++ )
    {
        for( int i = head_[u]; i; i = e_[i].next )
        {
            int v = e_[i].v;
            if( mark[u] != mark[v] )
            {
                AddEdge( mark[u], mark[v] );
                in[mark[v]] ++;
            }
        }
    }
    TopoSort();
    int ans1 = 0, ans2 = 0;
    for( int i = 1; i <= cnt; i ++ )
        ans1 = max( ans1, d[i] );
    for( int i = 1; i <= cnt; i ++ )
    {
        if( d[i] == ans1 )
        {
            ans2 += sum[i];
            if( ans2 >= MOD )
                ans2 %= MOD;
        }
    }
    printf( "%d\n%d", ans1, ans2 );
    return 0;
}
