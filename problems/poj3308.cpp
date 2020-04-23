#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<cmath>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
const	double INF = 1e2;
const	double eps = 1e-8;
const	int N = 200, M = 2000;

struct Network
{
	int sig, head[N];
	int s, t, level[N], cur[N];

	struct Edge
	{
		double cap;
		int v, next;
	} e[M];

	inline void Init( int x, int y )
	{
		set( head, 0 );
		s = x, t = y, sig = 0;
		return ;
	}

	inline void Emit( int u, int v, double w )
	{
		e[++sig].v = v, e[sig].cap = w;
		e[sig].next = head[u], head[u] = sig;
		return ;
	}

	inline void AddEdge( int u, int v, double w )
	{
		Emit( u, v, w ), Emit( v, u, 0.0 );
		return ;
	}

	inline int F( int i )
	{
		return ( ( i - 1 ) ^ 1 ) + 1;
	}

	inline bool BFS()
	{
		queue< int > q;
		q.push( s );
		set( level, -1 );
		level[s] = 0;
		while( !q.empty() )
		{
			int u = q.front(); q.pop();
			for( int i = head[u]; i; i = e[i].next )
			{
				int &v = e[i].v;
				if( level[v] == -1 && e[i].cap > eps )
				{
					level[v] = level[u] + 1;
					q.push( v );
				}
			}
		}
		return level[t] != -1;
	}

	double Augment( int u, double sur )
	{
		if( u == t || sur < eps )
			return sur;
		double flow = 0.0;
		for( int i = cur[u]; i; i = e[i].next )
		{
			int &v = e[i].v;
			if( e[i].cap >= flow && level[v] == level[u] + 1 )
			{
				double d = min( sur, e[i].cap - flow );
				d = Augment( v, d );
				flow += d, sur -= d;
				e[i].cap -= d, e[F(i)].cap += d;
			}
			cur[u] = e[i].next;
			if( sur < eps )
				break ;
		}
		if( sur < eps )
			level[u] = -1;
		return flow;
	}

	double MaxFlow()
	{
		double flow = 0.0;
		while( BFS() )
		{
			cpy( cur, head );
			flow += Augment( s, INF );
		}
		return flow;
	}
} g;

double q;
int t, n, m, a, b, k;

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d%d%d", &n, &m, &k );
		g.Init( n + m + 1, n + m + 2 );
		for( int i = 1; i <= n; i ++ )
		{
			cin >> q;
			g.AddEdge( g.s, i, log( q ) );
		}
		for( int i = 1; i <= m; i ++ )
		{
			cin >> q;
			g.AddEdge( i + n, g.t, log( q ) );
		}
		for( int i = 1; i <= k; i ++ )
		{
			scanf( "%d%d", &a, &b );
			g.AddEdge( a, b + n, INF );
		}
		double flow = g.MaxFlow();
		printf( "%.4f\n", exp( flow ) );
	}
	return 0;
}
