#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 1e4 + 5;
const	int INF = 0x3f3f3f3f;

bool vis[N];
int head[N], dis[N], size[N];
int n, n_, k, sig, num, ans, tick, root;

struct Edge
{
	int v, w, next;
} e[N*2];

inline void AddEdge( int u, int v, int w )
{
	e[++sig].v = v, e[sig].w = w;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

void GetRoot( int u, int p )
{
	int tmp = 0;
	size[u] = 1;
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if( v != p && !vis[v] )
		{
			GetRoot( v, u );
			size[u] += size[v];
			tmp = max( size[v], tmp );
		}
	}
	tmp = max( tmp, n_ - size[u] );
	if( tmp < num )
		num = tmp, root = u;
	return ;
}

void GetDist( int u, int p, int d )
{
	dis[tick++] = d;
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if( v != p && !vis[v] )
			GetDist( v, u, d + e[i].w );
	}
	return ;
}

int Count( int u, int d )
{
	tick = 0;
	GetDist( u, -1, d );
	int res = 0, l = 0, r = tick - 1;
	sort( dis, dis + tick );
	while( l < r )
	{
		if( dis[l] + dis[r] <= k )
			res += r - l, l ++;
		else
			r --;
	}
	return res;
}

void Interface( int u )
{
	vis[u] = 1;
	ans += Count( u, 0 );
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if( !vis[v] )
		{
			ans -= Count( v, e[i].w );
			root = 0, num = INF, n_ = size[v];
			GetRoot( v, u );
			Interface( root );
		}
	}
	return ;
}

int main(int argc, char **argv)
{
	while( scanf( "%d%d", &n, &k ) == 2 && n )
	{
		ans = sig = 0;
		set( head, 0 ), set( vis, 0 );
		for( int i = 1; i < n; i ++ )
		{
			int u, v, w;
			scanf( "%d%d%d", &u, &v, &w );
			AddEdge( u, v, w );
			AddEdge( v, u, w );
		}
		root = 0, num = INF, n_ = n;
		GetRoot( 1, 0 );
		Interface( root );
		printf( "%d\n", ans );
	}
	return 0;
}
