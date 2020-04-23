#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int INF = 0x3f3f3f3f;
const	int N = 500, M = 40000;

struct Edge
{
	int v, cap, cost, next;
} e[M];

bool vis[N];
int n, m, s, t, sig;
int dis[N], pre[N], head[N];

inline void Emit( int u, int v,int c, int w )
{
	e[++sig].v = v, e[sig].cap = c, e[sig].cost = w;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

inline void AddEdge( int u, int v, int c, int w )
{
	Emit( u, v, c, w ), Emit( v, u, 0, -w );
	return ;
}

inline int F( int i )
{
	return ( ( i - 1 ) ^ 1 ) + 1;
}

bool SPFA()
{
	queue< int > q;
	set( vis, 0 ), set( dis, 0x3f );
	vis[s] = 1, dis[s] = 0;
	q.push( s );
	while( !q.empty() )
	{
		int u = q.front(); q.pop();
		vis[u] = 0;
		for( int i = head[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( e[i].cap && dis[v] > dis[u] + e[i].cost )
			{
				pre[v] = i;
				dis[v] = dis[u] + e[i].cost;
				if( !vis[v] )
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
	while( SPFA() )
	{
		int u = t, d = INF;
		while( u != s )
		{
			d = min( d, e[pre[u]].cap );
			u = e[F(pre[u])].v;
		}
		flow += d;
		cost += d * dis[t];
		u = t;
		while( u != s )
		{
			e[pre[u]].cap -= d;
			e[F(pre[u])].cap += d;
			u = e[F(pre[u])].v;
		}
	}
	if( flow == n )
		return cost;
	return -1;
}

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		sig = 0, set( head, 0 );
		s = n + n + 1, t = n + n + 2;
		for( int i = 1; i <= n; i ++ )
		{
			AddEdge( s, i, 1, 0 );
			AddEdge( i + n, t, 1, 0 );
		}
		for( int i = 0; i < m; i ++ )
		{
			int u, v, w;
			scanf( "%d%d%d", &u, &v, &w );
			AddEdge( u, v + n, 1, w );
		}
		int ans = MaxFlow();
		printf( "%d\n", ans );
	}
	return 0;
}
