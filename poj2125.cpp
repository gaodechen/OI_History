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
const	int N = 250, M = 15000;

struct Network
{
	int s, t, sig, head[N];
	int d[N], pre[N], gap[N], cur[N];

	struct Edge
	{
		int v, next, cap;
	} e[M];

	inline void Init( var x, var y )
	{
		s = x, t = y;
		set( head, 0 ), sig = 0;
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
		Emit( u, v, w ), Emit( v, u, 0 );
		return ;
	}

	inline int F( var i )
	{
		return ( ( i - 1 ) ^ 1 ) + 1;
	}

	inline void BFS()
	{
		queue< int > q;
		set( d, -1 );
		set( gap, 0 );
		q.push( t );
		d[t] = 0;
		while( !q.empty() )
		{
			int u = q.front(); q.pop();
			gap[d[u]] ++;
			for( int i = head[u]; i; i = e[i].next )
			{
				int v = e[i].v;
				if( e[F(i)].cap > 0 && d[v] == -1 )
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
			e[F(pre[u])].cap  += sur;
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
		int k = t - 1;
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
		while( d[s] < t )
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
		d[u] = 1;
		for( int i = head[u]; i; i = e[i].next )
			if( !d[e[i].v] && e[i].cap > 0 )
				DFS( e[i].v );
		return ;
	}

	inline void Interface()
	{
		int flow = MaxFlow(), k = 0, n = ( t - 2 ) / 2;
		set( d, 0 ), set( pre, 0 ), DFS( s );
		for( int i = 1; i <= n; i ++ )
		{
			if( d[i+i] == 0 )
				pre[i+i] = 1, k ++;
			if( d[i+i+1] == 1 )
				pre[i+i+1] = 1, k ++;
		}
		printf( "%d\n%d\n", flow, k );
		for( int i = 1; i <= n; i ++ )
		{
			if( pre[i+i+1] )
				printf( "%d -\n", i );
			if( pre[i+i] )
				printf( "%d +\n", i );
		}
		return ;
	}

} g;

int n, m, sum, a[N], b[N];

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &a[i] );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &b[i] );
	for( int i = 1; i <= n; i ++ )
		sum += a[i], sum += b[i];
	g.Init( 1, n + n + 2 );
	for( int i = 1; i <= n; i ++ )
	{
		g.AddEdge( g.s, i + i, a[i] );
		g.AddEdge( i + i + 1, g.t, b[i] );
	}
	for( int i = 0, u, v; i < m; i ++ )
	{
		scanf( "%d%d", &u, &v );
		g.AddEdge( v + v, u + u + 1, INF );
	}
	g.Interface();
	return 0;
}
