#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, q )		memcpy( p, q, sizeof( q ) )

using	namespace	std;
typedef	const int &	var;
const	int INF = 0x3f3f3f3f;
const	int N = 200, M = 11000;

struct Network
{
	int sig, head[N];
	int n, s, t, d[N], cur[N], gap[N], pre[N];

	struct Edge
	{
		int v, cap, next;
	} e[M*2];

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
				int &v = e[i].v;
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
		bool res = false;
		for( int &i = cur[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( e[i].cap > 0 && d[u] == d[v] + 1 )
			{
				u = v, pre[v] = i;
				res = true;
				break ;
			}
		}
		return res;
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

	inline void Recover()
	{
		for( int i = 1; i <= sig; i += 2 )
		{
			e[i].cap += e[F(i)].cap;
			e[F(i)].cap = 0;
		}
		return ;
	}

} g;

int n, m;

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		if( m == 0 )
		{
			printf( "%d\n", n == 1 ? 1 : 0 );
			continue ;
		}
		g.sig = 0;
		set( g.head, 0 );
		for( int u = 1; u <= n; u ++ )
			g.AddEdge( u, u + n, 1 );
		for( int i = 0; i < m; i ++ )
		{
			int u, v;
			scanf( " (%d,%d)", &u, &v );
			u ++, v ++;
			g.AddEdge( u + n, v, N );
			g.AddEdge( v + n, u, N );
		}
		g. n = n + n;
		int res = INF, flow;
		for( int s = 1; s <= n; s ++ )
		{
			for( int t = 1; t <= n; t ++ )
			{
				if( s != t )
				{
					g.s = s + n, g.t = t;
					flow = g.MaxFlow();
					res = min( res, flow );
				}
				g.Recover();
			}
		}
		printf( "%d\n", res > n ? n : res );
	}
	return 0;
}
