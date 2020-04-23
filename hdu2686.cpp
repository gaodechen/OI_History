#include    <cstdio>
#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>

#define        set( p, k )        memset( p, k, sizeof( p ) )
#define        cpy( p, k )        memcpy( p, k, sizeof( k ) )

using    namespace    std;
const    int INF = 0x3f3f3f3f;
const    int N = 800000, M = 5000000;

struct Network
{
    bool vis[N];
    int dis[N], pre[N];
    int s, t, sig, head[N];

    struct Edge
    {
        int v, cap, cost, next;
    } e[M];

    inline void Init( int x, int y )
    {
        set( head, 0 );
        s = x, t = y, sig = 0;
        return ;
    }

    inline void Emit( int u, int v, int w, int c )
    {
        e[++sig].v = v, e[sig].cap = w, e[sig].cost = c;
        e[sig].next = head[u], head[u] = sig;
    }

    inline void AddEdge( int u, int v, int w, int c )
    {
        Emit( u, v, w, c );
        Emit( v, u, 0, -c );
        return ;
    }

    inline int F( int i )
    {
        return ( ( i - 1 ) ^ 1 ) + 1;
    }

    bool SPFA()
    {
        queue< int > q;
        q.push(s);
        set(vis, 0), set(dis, 0x3f);
        vis[s] = 1, dis[s] = 0;
        while( !q.empty() )
        {
            int u = q.front(); q.pop();
            vis[u] = 0;
            for(int i = head[u]; i; i = e[i].next)
            {
                int &v = e[i].v;
                if(e[i].cap && dis[v] > dis[u] + e[i].cost)
                {
                    pre[v] = i;
                    dis[v] = dis[u] + e[i].cost;
                    if(!vis[v])
                    {
                        vis[v] = 1;
                        q.push( v );
                    }
                }
            }
        }
        return dis[t] < INF;
    }

    int MaxFlow()
    {
        int flow = 0, cost = 0;
        while(SPFA())
        {
            int u = t, d = INF;
            while(u != s)
            {
                d = min( d, e[pre[u]].cap );
                u = e[F(pre[u])].v;
            }
            flow += d;
            cost += d * dis[t];
            u = t;
            while(u != s)
            {
                e[pre[u]].cap -= d;
                e[F(pre[u])].cap += d;
                u = e[F(pre[u])].v;
            }
        }
        return cost;
    }
} g;

int n, G[601][601];

inline int H( const int &x, const int &y )
{
    return ( x - 1 ) * n + y;
}

inline int Q( const int &x, const int &y )
{
    return n * n + ( x - 1 ) * n + y;
}

int main()
{
    while( scanf( "%d", &n ) == 1 )
    {
        g.Init( H( 1, 1 ), Q( n, n ) );
        for( int i = 1; i <= n; i ++ )
            for( int j = 1; j <= n; j ++ )
                scanf( "%d", &G[i][j] );
        for( int i = 1; i <= n; i ++ )
        {
            for( int j = 1; j <= n; j ++ )
            {
                g.AddEdge( H( i, j ), Q( i, j ), 1, -G[i][j] );
                if( i < n )
                    g.AddEdge( Q( i, j ), H( i + 1, j ), 1, 0 );
                if( j < n )
                    g.AddEdge( Q( i, j ), H( i, j + 1 ), 1, 0 );
            }
        }
        g.AddEdge( H( 1, 1 ), Q( 1, 1 ), 2, 0 );
        g.AddEdge( H( n, n ), Q( n, n ), 2, 0 );
        printf( "%d\n", -g.MaxFlow() );
    }
    return 0;
}
