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
const	int N = 300, M = 200000;

struct Network
{
	int s, t, m, sig, head[N];
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


} g;

int n, m, low[M], d[N];

int main()
{
	scanf( "%d%d", &n, &m );
	g.Init( n + 1, n + 2 );
	for( int i = 0; i < m; i ++ )
	{
		int u, v, c;
		scanf( "%d%d%d%d", &u, &v, &low[i], &c );
		g.AddEdge( u, v, c - low[i] );
		d[u] -= low[i], d[v] += low[i];
	}
	int sum = 0;
	for( int i = 1; i <= n; i ++ )
	{
		if( d[i] > 0 )
		{
			g.AddEdge( g.s, i, d[i] );
			sum += d[i];
		}
		else if( d[i] < 0 )
			g.AddEdge( i, g.t, -d[i] );
	}
	int flow = g.MaxFlow();
	if( flow == sum )
	{
		printf( "YES\n" );
		for( int i = 0; i < m; i ++ )
			printf( "%d\n", g.e[g.F(i+i+1)].cap + low[i] );
	}
	else
		printf( "NO\n" );
	return 0;
}
