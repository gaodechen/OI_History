#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, q )		memcpy( p, q, sizeof( q ) )

using	namespace	std;
const	int N = 300, M = 1000;
const	int INF = 0x3f3f3f3f;

struct Network
{
	int sig, head[N];
	int n, s, t, d[N], cur[N], gap[N], pre[N];

	struct Edge
	{
		int v, cap, next;
	} e[M];

	inline void Emit( int u, int v, int w )
	{
		e[++sig].v = v, e[sig].cap = w;
		e[sig].next = head[u], head[u] = sig;
		return ;
	}

	inline void AddEdge( int u, int v, int w )
	{
		Emit( u, v, w ), Emit( v, u, 0 );
		return ;
	}

	inline int F( int i )
	{
		return ( ( i - 1 ) ^ 1 ) + 1;
	}

	inline void BFS()
	{
		queue< int > q;
		q.push( t );
		set( d, -1 ), set( gap, 0 );
		d[t] = 0;
		while( !q.empty() )
		{
			int u = q.front(); q.pop();
			gap[d[u]] ++;
			for( int i = head[u]; i; i = e[i].next )
			{
				int v = e[i].v;
				if( d[v] == -1 && e[F(i)].cap > 0 )
				{
					d[v] = d[u] + 1;
					q.push( v );
				}
			}
		}
		return ;
	}

	inline int Augment()
	{
		int sur = INF, u = t;
		while( u != s )
		{
			sur = min( sur, e[pre[u]].cap );
			u = e[F(pre[u])].v;
		}
		u = t;
		while( u != s )
		{
			e[pre[u]].cap -= sur;
			e[F(pre[u])].cap += sur;
			u = e[F(pre[u])].v;
		}
		return sur;
	}

	inline bool Advance( int &u )
	{
		bool flag = false;
		for( int &i = cur[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( e[i].cap > 0 && d[u] == d[v] + 1 )
			{
				u = v, pre[v] = i;
				flag = true;
				break ;
			}
		}
		return flag;
	}

	inline void Retreat( int &u )
	{
		int k = n - 1;
		for( int i = head[u]; i; i = e[i].next )
			if( e[i].cap > 0 )
				k = min( k, d[e[i].v] );
		d[u] = k + 1;
		gap[d[u]] ++;
		cur[u] = head[u];
		if( u != s )
			u = e[F(pre[u])].v;
		return ;
	}

	int MaxFlow()
	{
		BFS();
		int u = s, flow = 0;
		cpy( cur, head );
		while( d[s] < n )
		{
			if( u == t )
			{
				flow += Augment();
				u = s;
			}
			if( !Advance( u ) )
			{
				if( -- gap[d[u]] == 0 )
					break ;
				Retreat( u );
			}
		}
		return flow;
	}

	void DFS( int u )
	{
		d[u] = 1;
		for( int i = head[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( !d[v] && e[i].cap > 0 )
				DFS( v );
		}
		return ;
	}

} g;

int main()
{
	int n, m, sum = 0;
	scanf( "%d%d", &n, &m );
	g.sig = 0, set( g.head, 0 );
	g.s = n + m + 1;
	g.n = g.t = n + m + 2;
	for( int i = 1, w, u, c; i <= n; i ++ )
	{
		scanf( "%d ", &w );
		sum += w;
		w = w * M + 1;
		g.AddEdge( g.s, i, w );
		while( true )
		{
			while( ( c = getchar() ) == ' ' );
			ungetc( c, stdin );
			if( c == 10 || c == 13 )
				break ;
			scanf( "%d", &u );
			g.AddEdge( i, u + n, INF );
		}
	}
	for( int i = 1, c; i <= m; i ++ )
	{
		scanf( "%d", &c );
		c = c * M;
		g.AddEdge( i + n, g.t, c );
	}
	int flow = g.MaxFlow();
	flow /= M;
	set( g.d, 0 );
	g.DFS( g.s );
	for( int i = 1; i <= n; i ++ )
		if( g.d[i] )
			printf( "%d ", i );
	printf( "\n" );
	for( int i = n + 1; i <= n + m; i ++ )
		if( g.d[i] )
			printf( "%d ", i - n );
	printf( "\n%d\n", sum - flow );
	return 0;
}
