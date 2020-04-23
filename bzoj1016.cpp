#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
 
using   namespace   std;
const   int N = 1e2 + 5;
const   int M = 1e3 + 5;
const   int MOD = 31011;
 
struct Edge
{
    int u, v, w;
     
    bool operator < ( const Edge &b ) const
    {
        return w < b.w;
    }
     
} e[M], g[M];
 
int n, m, pre[N];
 
inline int Find( int u )
{
    while( u != pre[u] )
        u = pre[u];
    return u;
}
 
int DFS( int c, int p, int k )
{
    if( p == g[c].w )
        return 1;
    int sum = 0;
    for( int i = k; i <= g[c].v; i ++ )
    {
        int u = Find( e[i].u );
        int v = Find( e[i].v );
        if( u != v )
        {
            pre[v] = u;
            sum += DFS( c, p + 1, i + 1 );
            pre[u] = u, pre[v] = v;
        }
    }
    return sum;
}
 
int main()
{
    scanf( "%d%d", &n, &m );
    for( int i = 1; i <= m; i ++ )
        scanf( "%d%d%d", &e[i].u, &e[i].v, &e[i].w );
    sort( e + 1, e + m + 1 );
    for( int i = 1; i <= n; i ++ )
        pre[i] = i;
    e[0].w = -1;
    int c = 0, cnt = 0;
    for( int i = 1; i <= m; i ++ )
    {
        int u = e[i].u, v = e[i].v;
        if( e[i].w == e[i-1].w )
            g[c].v = i;
        else
        {
            g[++c].u = g[c].v = i;
            g[c].w = 0;
        }
        u = Find(u), v = Find(v);
        if(u != v)
        {
            pre[v] = u, g[c].w ++;
            cnt ++;
        }
    }
    if(cnt != n - 1)
    {
        printf("%d\n", 0);
        return 0;
    }
    for(int i = 1; i <= n; i ++)
        pre[i] = i;
    int ans = 1;
    for(int i = 1; i <= c; i ++)
    {
        int t = DFS(i, 0, g[i].u);
        if(t) ans *= t;
        if(ans >= MOD) ans %= MOD;
        for(int j = g[i].u; j <= g[i].v; j ++)
            pre[Find(e[j].v)] = Find(e[j].u);
    }
    printf("%d\n", ans);
    return 0;
}
