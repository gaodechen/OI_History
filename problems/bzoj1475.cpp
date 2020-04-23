#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, q )		memcpy( p, q, sizeof( q ) )

using	namespace	std;
typedef	const int & var;
const	int INF = 0x3f3f3f3f;
const	int N = 3000, M = 100000;

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

int n, m, sum, G[51][51];
int dir[][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

inline int H( var x, var y )
{
	return ( x - 1 ) * m + y;
}

int main()
{
	scanf( "%d", &n );
	m = n, sum = 0;
	g.Init( n * m + 1, n * m + 2 );
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= m; j ++ )
			scanf( "%d", &G[i][j] );
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = 1; j <= m; j ++ )
		{
			if( ( i + j ) & 1 )
				g.AddEdge( g.s, H( i, j ), G[i][j] );
			else 
				g.AddEdge( H( i, j ), g.t, G[i][j] );
			sum += G[i][j];
		}
	}
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = 1; j <= m; j ++ )
		{
			if( ( i + j ) & 1 )
			{
				for( int d = 0; d < 4; d ++ )
				{
					int x = i + dir[d][0];
					int y = j + dir[d][1];
					if( x >= 1 && y >= 1 && x <= n && y <= m )
						g.AddEdge( H( i, j ), H( x, y ), INF );
				}
			}
		}
	}
	printf( "%d\n", sum - g.MaxFlow() );
	return 0;
}
