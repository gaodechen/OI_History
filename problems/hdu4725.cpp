#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<deque>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 2e5 + 5, M = N;

struct SP
{
	bool vis[N];
	int sig, dis[N], head[N];

	struct Edge
	{
		int v, w, next;
	} e[M*20];

	inline void Init()
	{
		sig = 0, set( head, 0 );
		set( vis, 0 ), set( dis, -1 );
		return ;
	}

	inline void Emit( int u, int v, int w )
	{
		e[++sig].v = v, e[sig].w = w;
		e[sig].next = head[u], head[u] = sig;
		return ;
	}

	inline void AddEdge( int u, int v, int w )
	{
		Emit( u, v, w ), Emit( v, u, w );
		return ;
	}

	int SPFA( int s, int t )
	{
		deque< int > q;
		q.push_back( s );
		dis[s] = 0, vis[s] = 1;
		while( !q.empty() )
		{
			int u = q.front();
			q.pop_front();
			vis[u] = 0;
			for( int i = head[u]; i; i = e[i].next )
			{
				int &v = e[i].v;
				if( dis[v] == -1 || dis[v] > dis[u] + e[i].w )
				{
					dis[v] = dis[u] + e[i].w;
					if( !vis[v] )
					{
						vis[v] = 1;
						if( !q.empty() && dis[v] < dis[q.front()] )
							q.push_front( v );
						else
							q.push_back( v );
					}
				}
			}
		}
		return dis[t];
	}
} g;

int lay[N], mark[N];
int t, n, m, c, u, v, w;

int main()
{
	scanf( "%d", &t );
	for( int k = 1; k <= t; k ++ )
	{
		g.Init();
		set( mark, 0 );
		scanf( "%d%d%d", &n, &m, &c );
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%d", &lay[i] );
			mark[lay[i]] = 1;
		}
		for( int i = 1; i < n; i ++ )
			if( mark[i] && mark[i+1] )
				g.AddEdge( n + i, n + i + 1, c );
		for( int i = 1; i <= n; i ++ )
		{
			g.Emit( n + lay[i], i, 0 );
			if( lay[i] > 1 )
				g.Emit( i, lay[i] + n - 1, c );
			if( lay[i] < n )
				g.Emit( i, lay[i] + n + 1, c );
		}
		for( int i = 1; i <= m; i ++ )
		{
			scanf( "%d%d%d", &u, &v, &w );
			g.Emit( u, v, w );
			g.Emit( v, u, w );
		}
		int ans = g.SPFA( 1, n );
		printf( "Case #%d: %d\n", k, ans );
	}
	return 0;
}
