#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <queue>
 
using   namespace   std;
const   int T = 1e2 + 3;
const   int N = 2e1 + 3;
const   int M = 2e4 + 5;
const   int INF = 0x3f3f3f3f;
 
inline int in()
{
    int k = 0, c = '\0';
    for( ; c > '9' || c < '0'; )
        c = getchar();
    for( ; c >= '0' && c <= '9'; )
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return k;
}

bool mark[N][T], judge[N];
int head[N], cost[T][T], d[T];
int sig, t, n, m, k, c, dis[N];
 
struct Edge
{
    int v, w, next;
} e[M];
 
struct Item
{
    int u, d;
 
    Item(int u, int d): u(u), d(d)
    {
    }
 
    bool operator < (const Item &b) const
    {
        return d > b.d;
    }
 
};
 
inline void AddEdge(int u, int v, int w)
{
    e[++sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
    return ;
}
 
inline int Dijkstra()
{
    memset( dis, INF, sizeof( dis ) );
    priority_queue< Item > q;
    q.push( Item( 1, 0 ) );
    while( dis[n] == INF && !q.empty() )
    {
        Item t = q.top(); q.pop();
        int u = t.u;
        if( dis[u] != INF )
            continue ;
        dis[u] = t.d;
        for( int i = head[u]; i; i = e[i].next )
        {
            int v = e[i].v;
            if( !judge[v] && dis[v] == INF )
                q.push( Item( v, dis[u] + e[i].w ) );
        }
    }
    return dis[n];
}
 
int main()
{
    t = in(), n = in(), k = in(), m = in();
    for( int i = 0; i < m; i ++ )
    {
        int u, v, w;
        u = in(), v = in(), w = in();
        AddEdge( u, v, w );
        AddEdge( v, u, w );
    }
    c = in();
    for(int i = 0; i < c; i ++)
    {
        int p = in(), a = in(), b = in();
        for(int j = a; j <= b; j ++)
            mark[p][j] = 1;
    }
    for(int l = 1; l <= t; l ++)
    {
        for(int r = l; r <= t; r ++)
        {
            memset(judge, 0, sizeof(judge));
            for(int i = l; i <= r; i ++)
                for(int p = 1; p <= n; p ++)
                    if(mark[p][i])
                        judge[p] = 1;
            cost[l][r] = Dijkstra();
            if(cost[l][r] < INF)
                cost[l][r] *= (r - l + 1);
        }
    }
    memset(d, INF, sizeof(d));
    d[0] = 0;
    for(int i = 1; i <= t; i ++)
        for(int j = 0; j < i; j ++)
            if(d[j] < INF && cost[j + 1][i] < INF)
                d[i] = min(d[i], d[j] + cost[j + 1][i] + k);
    printf("%d\n", d[t] - k);
    return 0;
}
