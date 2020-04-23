#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<queue> 
#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int INF = 0x3f3f3f3f;
const	int N = 1000, M = 20000;

struct Network
{
	int sig, head[N];
	int s, t, cur[N], level[N];

	struct Edge
	{
		int v, cap, next;
	} e[M];

	inline int F( int i )
	{
		return ( ( i - 1 ) ^ 1 ) + 1;
	}

	inline void AddEdge( int u, int v, int w )
	{
		e[++sig].v = v, e[sig].cap = w;
		e[sig].next = head[u], head[u] = sig;
		return ;
	}

	inline void Init( int s_, int t_ )
	{
		set( head, 0 );
		s = s_, t = t_, sig = 0;
		return ;
	}

	inline bool BFS()
	{
		queue< int > q;
		set( level, -1 );
		q.push( s );
		level[s] = 0;
		while( !q.empty() )
		{
			int u = q.front(); q.pop();
			for( int i = head[u]; i; i = e[i].next )
			{
				int &v = e[i].v;
				if( level[v] == -1 && e[i].cap )
				{
					level[v] = level[u] + 1;
					q.push( v );
				}
			}
		}
		return level[t] != -1;
	}

	int Augment( int u, int sur )
	{
		if( u == t || sur == 0 )
			return sur;
		int flow = 0;
		for( int i = cur[u]; i; i = e[i].next )
		{
			int &v = e[i].v;
			if( level[v] == level[u] + 1 && e[i].cap >= flow )
			{
				int d = min( sur, e[i].cap - flow );
				d = Augment( v, d );
				flow += d, sur -= d;
				e[i].cap -= d, e[F(i)].cap += d;
			}
			cur[u] = e[i].next;
			if( sur == 0 )
				break ;
		}
		if( sur == 0 )
			level[u] = -1;
		return flow;
	}

	int MaxFlow()
	{
		int flow = 0;
		while( BFS() )
		{
			for( int i = 1; i <= t; i ++ )
				cur[i] = head[i];
			flow += Augment( s, INF );
		}
		return flow;
	}

} net, net_;

int k, c, m, G[N][N];

inline bool Check( int p )
{
	for( int i = k + 1; i <= k + c; i ++ )
	{
		for( int j = 1; j <= k; j ++ )
		{
			if( G[i][j] <= p )
			{
				net_.AddEdge( i, j, 1 );
				net_.AddEdge( j, i, 0 );
			}
		}
	}
	int flow = net_.MaxFlow();
	return flow == c;
}

int main()
{
	scanf( "%d%d%d", &k, &c, &m );
	for( int i = 1; i <= k + c; i ++ )
	{
		for( int j = 1; j <= k + c; j ++ )
		{
			scanf( "%d", &G[i][j] );
			if( G[i][j] == 0 && i != j )
				G[i][j] = INF;
		}
	}
	for( int p = 1; p <= k + c; p ++ )
		for( int i = 1; i <= k + c; i ++ )
			for( int j = 1; j <= k + c; j ++ )
				if( G[i][p] < INF && G[p][j] < INF )
					G[i][j] = min( G[i][j], G[i][p] + G[p][j] );
	net.Init( k + c + 1, k + c + 2 );
	for( int i = 1; i <= k; i ++ )
	{
		net.AddEdge( i, net.t, m );
		net.AddEdge( net.t, i, 0 );
	}
	for( int i = k + 1; i <= k + c; i ++ )
	{
		net.AddEdge( net.s, i, 1 );
		net.AddEdge( i, net.s, 0 );
	}
	int l = 0, r = 20000;
	while( l < r )
	{
		net_ = net;
		int mid = ( l + r ) >> 1;
		if( Check( mid ) )
			r = mid;
		else
			l = mid + 1;
	}
	printf( "%d\n", l );
	return 0;
}

