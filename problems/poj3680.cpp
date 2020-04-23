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
const	int N = 500, M = 1500;

struct Network
{
	bool vis[N];
	int dis[N], pre[N];
	int s, t, sig, head[N];

	struct Edge
	{
		int v, next, cap, cost;
	} e[M];

	inline void Init()
	{
		sig = 0;
		set( head, 0 );
		return ;
	}

	inline void Emit( var u, var v, var w, var c )
	{
		e[++sig].v = v, e[sig].cap = w, e[sig].cost = c;
		e[sig].next = head[u], head[u] = sig;
	}

	inline void AddEdge( var u, var v, var w, var c )
	{
		Emit( u, v, w, c );
		Emit( v, u, 0, -c );
		return ;
	}

	inline int F( var i )
	{
		return ( ( i - 1 ) ^ 1 ) + 1;
	}

	bool SPFA()
	{
		queue< int > q;
		set( vis, 0 );
		set( dis, 0x3f );
		q.push( s );
		vis[s] = 1, dis[s] = 0;
		while( !q.empty() )
		{
			int u = q.front(); q.pop();
			vis[u] = 0;
			for( int i = head[u]; i; i = e[i].next )
			{
				int &v = e[i].v;
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
		return cost;
	}

} g;

struct Discretization
{
	int n, a[N];

	inline void Init()
	{
		sort( a, a + n );
		n = unique( a, a + n ) - a;
		return ;
	}

	inline void Insert( var k )
	{
		a[n++] = k;
		return ;
	}

	inline int Hash( var k )
	{
		return lower_bound( a, a + n, k ) - a + 1;
	}

} d;

int t, n, k, a[N], b[N], w[N];

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		g.Init(), d.n = 0;
		scanf( "%d%d", &n, &k );
		for( int i = 0; i < n; i ++ )
			scanf( "%d%d%d", &a[i], &b[i], &w[i] );
		for( int i = 0; i < n; i ++ )
		{
			d.Insert( a[i] );
			d.Insert( b[i] );
		}
		d.Init();
		for( int i = 0; i < n; i ++ )
		{
			a[i] = d.Hash( a[i] );
			b[i] = d.Hash( b[i] );
			g.AddEdge( a[i], b[i], 1, -w[i] );
		}
		for( int i = 1; i < d.n; i ++ )
			g.AddEdge( i, i + 1, k, 0 );
		g.s = d.n + 1, g.t = d.n + 2;
		g.AddEdge( g.s, 1, k, 0 );
		g.AddEdge( d.n, g.t, k, 0 );
		printf( "%d\n", -g.MaxFlow() );
	}
	return 0;
}

