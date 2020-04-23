#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>

using   namespace   std;
const   int N = 1e4 + 5;
const   int M = 5e4 + 5;
const   int INF = 0x3f3f3f3f;

struct Edge
{
    int v, w, next;
} e[M+M];

bool vis[N];
int n, m, b, s, sig;
int cost[N], d[N], head[N];

inline void AddEdge( int u, int v, int w )
{
    e[++sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

inline bool Check( int k )
{
    for( int i = 1; i <= n; i ++ )
        d[i] = INF, vis[i] = 0;
    queue< int > q;
    q.push( 1 ), d[1] = 0;
    while( !q.empty() )
    {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for( int i = head[u]; i; i = e[i].next )
        {
            int v = e[i].v;
            if( d[v] > d[u] + e[i].w && cost[v] <= k )
            {
                d[v] = d[u] + e[i].w;
                if( !vis[v] )
                {
                    vis[v] = 1;
                    q.push( v );
                }
            }
        }
    }
    return d[n] <= b;
}

int main()
{
    cin >> n >> m >> b;
    for( int i = 1; i <= n; i ++ )
    {
        cin >> cost[i];
        s = max( s, cost[i] );
    }
    for( int i = 0; i < m; i ++ )
    {
        int u, v; int w;
        cin >> u >> v >> w;
        AddEdge( u, v, w );
        AddEdge( v, u, w );
    }
    int l = cost[1], r = s + 1;
    while( l < r )
    {
        int mid = ( l + r ) >> 1;
        if( Check( mid ) )
            r = mid;
        else
            l = mid + 1;
    }
    if( l <= s )
        cout << l << endl;
    else
        cout << "AFK" << endl;
    return 0;
}
