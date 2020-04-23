#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
const	int INF = 0x3f3f3f3f;
const	int N = 101, M = 1001;

struct Network
{
	int s, t, n, m, sig, head[N];
	int d[N], pre[N], gap[N], cur[N];

	struct Edge
	{
		int v, next, cap;
	} e[M];

	inline void Init( var x, var y, var z )
	{
		set( head, 0 );
		s = x, t = y;
		n = z, sig = 0;
		return ;
	}

	inline void Emit( var u, var v, var w )
	{
		e[++sig].v = v, e[sig].cap = w;
		e[sig].next = head[u], head[u] = sig;
		return ;
	}

	inline void AddEdge( var u, var v, var w )
	{
		Emit( u, v, w ), Emit( v, u, w );
		return ;
	}

	inline int F( var i )
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
		bool res = false;
		for( int &i = cur[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( d[u] == d[v] + 1 && e[i].cap > 0 )
			{
				u = v, pre[u] = i;
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

	void DFS( var u )
	{
		gap[u] = 1;
		for( int i = head[u]; i; i = e[i].next )
			if( !gap[e[i].v] && e[i].cap > 0 )
				DFS( e[i].v );
		return ;
	}

	inline void Interface()
	{
		set( gap, 0 );
		DFS( 1 );
		for( int i = 1; i < m + m; i += 2 )
		{
			int u = e[F(i)].v, v = e[i].v;
			if( ( !e[i].cap || !e[F(i)].cap ) && gap[u] != gap[v] )
				printf( "%d %d\n", u, v );
		}
		printf( "\n" );
		return ;
	}

} g;

int n, m;

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 && n )
	{
		g.Init( 1, 2, n ), g.m = m;
		for( int i = 1; i <= m; i ++ )
		{
			int u, v, w;
			scanf( "%d%d%d", &u, &v, &w );
			g.AddEdge( u, v, w );
		}
		g.MaxFlow();
		g.Interface();
	}
	return 0;
}
