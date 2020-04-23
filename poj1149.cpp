#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <queue>

#define     set( p, k )     memset( p, k, sizeof( p ) )

using   namespace   std;
const   int INF = 0x3f3f3f3f;
const   int M = 1010, N = 110;

struct Network
{
    struct Edge
    {
        int v, cap, next;
    } e[M];
    int tick, head[N];
    int s, t, cur[N], level[N];

    void Init()
    {
        tick = 0;
        set( head, 0 );
        return ;
    }
    inline void AddEdge( int u, int v, int w )
    {
        e[++tick].v = v, e[tick].cap = w;
        e[tick].next = head[u], head[u] = tick;
        return ;
    }
    inline int D( int i )
    {
        return ( ( i + 1 ) ^ 1 ) - 1;
    }
    inline bool BFS()
    {
        queue< int > q;
        set( level, -1 );
        q.push( s );
        level[s] = 0;
        while( !q.empty() )
        {
            int u = q.front(); q.pop();
            for( int i = head[u]; i; i = e[i].next )
            {
                int &v = e[i].v;
                if( e[i].cap && level[v] == -1 )
                {
                    level[v] = level[u] + 1;
                    q.push( v );
                }
            }
        }
        return level[t] != -1;
    }
    int Augment( int u, int sur )
    {
        if( u == t || sur == 0 )
            return sur;
        int flow = 0;
        for( int i = cur[u]; i; i = e[i].next )
        {
            int &v = e[i].v, d;
            if( e[i].cap && level[v] == level[u] + 1 )
            {
                d = min( sur, e[i].cap - flow );
                d = Augment( v, d );
                e[i].cap -= d, e[D(i)].cap += d;
                flow += d, sur -= d;
            }
            cur[u] = e[i].next;
            if( sur == 0 )
                break ;
        }
        return flow;
    }
    int MaxFlow()
    {
        int flow = 0;
        while( BFS() )
        {
            for( int i = 1; i <= t; i ++ )
                cur[i] = head[i];
            flow += Augment( s, INF );
        }
        return flow;
    }
} net;

bool mark[M];
int n, m, num[M];
int G[N][N], pre[M];

int main()
{
    scanf( "%d%d", &m, &n );
    for( int i = 1; i <= m; i ++ )
        scanf( "%d", &num[i] );
    net.Init();
    net.s = n + 1;
    net.t = n + 2;
    for( int i = 1; i <= n; i ++ )
    {
        int k, a, b;
        scanf( "%d", &k );
        for( int j = 1; j <= k; j ++ )
        {
            scanf( "%d", &a );
            if( mark[a] == 0 )
            {
                G[net.s][i] += num[a];
                mark[a] = 1;
            }
            else
                G[pre[a]][i] = INF;
            pre[a] = i;
        }
        scanf( "%d", &b );
        G[i][net.t] = b;
    }
    for( int i = 1; i <= net.t; i ++ )
    {
        for( int j = 1; j <= net.t; j ++ )
        {
            if( G[i][j] )
            {
                net.AddEdge( i, j, G[i][j] );
                net.AddEdge( j, i, 0 );
            }
        }
    }
    printf( "%d\n", net.MaxFlow() );
    return 0;
}
