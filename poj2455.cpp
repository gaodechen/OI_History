#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, q )		memcpy( p, q, sizeof( q ) )

using	namespace	std;
const	int INF = 0x3f3f3f3f;
const	int N = 300, M = 400000;

struct Edge
{
	int u, v, w;
	bool operator < ( const Edge &b ) const
	{
		return w < b.w;
	}
} e[M];

struct Network
{
	int sig, head[N];
	int s, t, d[N], cur[N], gap[N], pre[N];

	struct Edge
	{
		int v, cap, next;
	} e[M*2];

	inline void Init( int x, int y )
	{
		set( head, 0 );
		s = x, t = y, sig = 0;
		return ;
	}

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

int n, m, t;

bool Check( int k )
{
	g.Init( 1, n );
	for( int i = 0; i < m; i ++ )
	{
		int &u = e[i].u;
		int &v = e[i].v;
		if( e[i].w <= k )
		{
			g.AddEdge( u, v, 1 );
			g.AddEdge( v, u, 1 );
		}
	}
	int flow = g.MaxFlow();
	return flow >= t;
}

int main()
{
	while( scanf( "%d%d%d", &n, &m, &t ) == 3 )
	{
		int l = INF, r = -INF;
		for( int i = 0; i < m; i ++ )
		{
			scanf( "%d%d%d", &e[i].u, &e[i].v, &e[i].w );
			l = min( l, e[i].w );
			r = max( r, e[i].w );
		}
		while( l < r )
		{
			int mid = ( l + r ) >> 1;
			if( Check( mid ) )
				r = mid;
			else
				l = mid + 1;
		}
		printf( "%d\n", l );
	}
	return 0;
}

