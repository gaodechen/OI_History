#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>
#include	<vector>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
const	int INF = 0x3f3f3f3f;
const	int N = 1000, M = 100000;

struct Network
{
	bool vis[N];
	int sig, head[N];
	int s, t, n, d[N], cur[N], gap[N], pre[N];

	struct Edge
	{
		int v, cap, next;
	} e[M*2];

	inline void AddEdge( int u, int v, int w )
	{
		e[++sig].v = v, e[sig].cap = w;
		e[sig].next = head[u], head[u] = sig;
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
		set( d, -1 );
		set( gap, 0 );
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
			int &v = e[i].v;
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

	void SourceDFS( int u )
	{
		vis[u] = 1;
		for( int i = head[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( !vis[v] && e[i].cap > 0 )
				SourceDFS( v );
		}
		return ;
	}

	void SinkDFS( int u )
	{
		vis[u] = 1;
		for( int i = head[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( !vis[v] && e[F(i)].cap > 0 )
				SinkDFS( v );
		}
	}

	inline void Interface()
	{
		MaxFlow();
		set( vis, 0 );
		SourceDFS( s );
		SinkDFS( t );
		int sum = 0;
		for( int i = 1; i <= n; i ++ )
			sum += vis[i];
		if( sum < n )
			printf( "AMBIGUOUS\n" );
		else
			printf( "UNIQUE\n" );
		return ;
	}

} g;

int main()
{
	int n, m;
	while( scanf( "%d%d\n", &n, &m ) == 2 && n )
	{
		g.n = n, g.sig = 0;
		set( g.head, 0 );
		scanf( "%d%d", &g.s, &g.t );
		for( int i = 0; i < m; i ++ )
		{
			int u, v, w;
			scanf( "%d%d%d", &u, &v, &w );
			g.AddEdge( u, v, w );
			g.AddEdge( v, u, w );
		}
		g.Interface();
	}
	return 0;
}
