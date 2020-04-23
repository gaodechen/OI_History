#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int INF = 0x3f3f3f3f;
const	int N = 1001, M = 20001;

bool vis[N];
int sig, head[N];
int dis[N], n, m, k, up;

struct Edge
{
	int u, v, w, next;
} e[M];

inline void AddEdge( int u, int v, int w )
{
	e[++sig].v = v, e[sig].w = w;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

inline int Dijkstra( int x )
{
	set( vis, 0 );
	set( dis, 0x3f );
	dis[1] = 0;
	for( int i = 1; i <= n; i ++ )
	{
		int p = -1, d = INF;
		for( int j = 1; j <= n; j ++ )
			if( dis[j] < d && !vis[j] )
				d = dis[j], p = j;
		if( p == -1 )
			break ;
		vis[p] = 1;
		for( int i = head[p]; i; i = e[i].next )
		{
			int v = e[i].v, w = e[i].w > x ? 1 : 0;
			if( dis[v] > dis[p] + w )
				dis[v] = dis[p] + w;
		}
	}
	return dis[n];
}

int main()
{
	scanf( "%d%d%d",&n, &m, &k );
	for( int i = 0; i < m; i ++ )
	{
		int u, v, w;
		scanf( "%d%d%d", &u, &v, &w );
		AddEdge( u, v, w );
		AddEdge( v, u, w );
		up = max( up, w );
	}
	int l = 0, r = up + 1;
	while( l < r )
	{
		int mid = ( l + r ) >> 1;
		if( Dijkstra( mid ) <= k )
			r = mid;
		else
			l = mid + 1;
	}
	if( l > up )
		printf( "-1\n" );
	else
		printf( "%d\n", l );
	return 0;
}
