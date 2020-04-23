#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int INF = 0x3f3f3f3f;
const	int N = 15000, M = 15000;

struct SSP
{
    bool vis[N];
    int sig, dis[4][N], head[N];

    struct Edge
    {
        int v, cost, next;
    } e[M];

    inline void Init()
    {
		sig = 0;
        set( head, 0 );
        return ;
    }

    inline void AddEdge( int u, int v, int w )
    {
        e[++sig].v = v, e[sig].cost = w;
        e[sig].next = head[u], head[u] = sig;
        return ;
    }

    void SPFA( int s, int inx )
    {
        queue< int > q;
        q.push( s );
        set( vis, 0 );
		set( dis[inx], 0x3f );
        vis[s] = 1, dis[inx][s] = 0;
        while( !q.empty() ) {
            int u = q.front(); q.pop();
            vis[u] = 0;
            for( int i = head[u]; i; i = e[i].next )
            {
                int &v = e[i].v;
                if( dis[inx][v] > dis[inx][u] + e[i].cost )
                {
                    dis[inx][v] = dis[inx][u] + e[i].cost;
                    if( !vis[v] )
                    {
                        vis[v] = 1;
                        q.push( v );
                    }
                }
            }
        }
		return ;
    }
} g;

int c, n, m, k, q, source[N];

int main()
{
	while( scanf( "%d%d%d", &n, &m, &k ) == 3 )
	{
		g.Init();
		for( int i = 1; i <= n; i ++ )
			scanf( "%d", &source[i] );
		for( int i = 1; i <= k; i ++ )
		{
			int a, b, w;
			scanf( "%d%d%d", &a, &b, &w );
			g.AddEdge( a, b, w );
			g.AddEdge( b, a, w );
		}
		scanf( "%d", &q );
		printf( "Case #%d\n", ++ c );
		for( int i = 1; i <= q; i ++ )
		{
			int a, b, c;
			scanf( "%d%d%d", &a, &b, &c );
			g.SPFA( source[a], 0 );
			g.SPFA( source[b], 1 );
			g.SPFA( source[c], 2 );
			int ans = INF;
			for( int u = 1; u <= m; u ++ )
				ans = min( ans, g.dis[0][u] + g.dis[1][u] + g.dis[2][u] );
			if( ans < INF )
				printf( "Line %d: The minimum cost for this line is %d.\n", i, ans );
			else
				printf( "Line %d: Impossible to connect!\n", i );
		}
	}
	return 0;
}
