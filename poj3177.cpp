#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 5e3 + 5;
const	int M = 1e4 + 5;

struct Edge
{
	int v, next;
} e[M+M];

bool G[N][N], cut[M], vis[N];
int ind, n, m, sig, head[N];
int dfn[N], low[N], mark[N], d[N];

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

void DFS( int u, int p )
{
	dfn[u] = low[u] = ++ ind;
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if( v == p ) continue ;
		if( !dfn[v] )
		{
			DFS( v, u );
			low[u] = min( low[u], low[v] );
			if( dfn[u] < low[v] )
				cut[i] = cut[((i - 1) ^ 1) + 1] = 1;
			// Here we can use UFS to shrink vertexes
			// Or just DFS after Tarjan()
		}
		else
			low[u] = min( low[u], dfn[v] );
	}
	return ;
}

void Mark( int u, int k )
{
	mark[u] = k, vis[u] = 1;
	for( int i = head[u]; i; i = e[i].next )
		if( !cut[i] && !vis[e[i].v] )
			Mark( e[i].v, k );
	return ;
}

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 0, u, v; i < m; i ++ )
	{
		scanf( "%d%d", &u, &v );
		if( !G[u][v] )
		{
			AddEdge( u, v );
			AddEdge( v, u );
			G[u][v] = G[v][u] = 1;
		}
	}
	DFS( 1, 0 );
	for( int i = 1, t = 0; i <= n; i ++ )
		if( !mark[i] )
			Mark( i, ++ t );
	for( int u = 1; u <= n; u ++ )
		for( int i = head[u]; i; i = e[i].next )
			if( mark[u] != mark[e[i].v] )
				d[mark[u]] ++;
	int cnt = 0;
	for( int i = 1; i <= n; i ++ )
		if( d[i] == 1 )
			cnt ++;
	printf( "%d\n", ( cnt + 1 ) / 2 );
	return 0;
}
