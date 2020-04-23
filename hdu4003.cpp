#include	<cstdio>
#include	<cstdlib>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e4 + 5;

struct Edge
{
	int v, w, next;
} e[N*2];

int sig, head[N];

inline void AddEdge( int u, int v, int w )
{
	e[++sig].v = v, e[sig].w = w;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

int n, s, k, d[11][N];

void DFS( int u, int p )
{
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v, w = e[i].w;
		if( v == p )
			continue ;
		DFS( v, u );
		for( int j = k; j >= 0; j -- )
		{
			// Put d[v][0] in, as at least one res has to be selected in this subtree
			// And d[v][0] may be replaced then
			d[j][u] += d[0][v] + w + w;
			// Of course, q could be euqal to j! As u may have the only son, v
			for( int q = 1; q <= j; q ++ )
				d[j][u] = min( d[j][u], d[j-q][u] + d[q][v] + q * w );
		}
	}
	return ;
}

int main()
{
	while( scanf( "%d%d%d", &n, &s, &k ) == 3 )
	{
		sig = 0;
		memset( d, 0, sizeof( d ) );
		memset( head, 0, sizeof( head ) );
		for( int i = 1; i < n; i ++ )
		{
			int u, v, w;
			scanf( "%d%d%d", &u, &v, &w );
			AddEdge( u, v, w );
			AddEdge( v, u, w );
		}
		DFS( s, 0 );
		printf( "%d\n", d[k][s] );
	}
	return 0;
}
