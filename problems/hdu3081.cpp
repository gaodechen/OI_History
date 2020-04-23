#include    <cstdio>
#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <queue>

#define     set( p, k )     memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using   namespace   std;
const   int INF = 0x3f3f3f3f;
const   int N = 500, M = N * N;

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
	{ return ( ( i - 1 ) ^ 1 ) + 1;
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

} net, net_;

bool G[N][N];
int t, n, m, f;

bool Check( int k )
{
	net = net_;
	for( int i = 1; i <= n; i ++ )
	{
		net.AddEdge( net.s, i, k );
		net.AddEdge( i, net.s, 0 );
	}
	for( int i = n + 1; i <= n + n; i ++ )
	{
		net.AddEdge( i, net.t, k );
		net.AddEdge( net.t, i, 0 );
	}
	int flow = net.MaxFlow();
	return flow == k * n;
}

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		memset( G, 0, sizeof( G ) );
		scanf( "%d%d%d", &n, &m, &f );
		for( int i = 0; i < m; i ++ )
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			v += n;
			G[u][v] = G[v][u] = 1;
		}
		for( int i = 0; i < f; i ++ )
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			G[u][v] = G[v][u] = 1;
		}
		for( int k = 1; k <= n; k ++ )
			for( int i = 1; i <= n + n; i ++ )
				for( int j = 1; j <= n + n; j ++ )
					G[i][j] = G[i][j] || ( G[i][k] && G[k][j] );
		net_.Init( n + n + 1, n + n + 2 );
		for( int i = 1; i <= n; i ++ )
		{
			for( int j = n + 1; j <= n + n; j ++ )
			{
				if( G[i][j] )
				{
					net_.AddEdge( i, j, 1 );
					net_.AddEdge( j, i, 0 );
				}
			}
		}
		int l = 0, r = n;
		while( l < r )
		{
			int mid = ( l + r + 1 ) >> 1;
			if( Check( mid ) )
				l = mid;
			else
				r = mid - 1;
		}
		printf( "%d\n", l );
	}
	return 0;
}

