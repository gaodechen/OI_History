#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 3e3 + 10;
const	int INF = 0x3f3f3f3f;

struct Edge
{
	int v, w, next;
} e[N*2];

int head[N], d[N][N], n, m, k, a, c, tick;

void AddEdge( int u, int v, int w )
{
	e[++tick].v = v, e[tick].w = w;
	e[tick].next = head[u], head[u] = tick;
	return ;
}

int DFS( int u, int pre )
{
	int sum = ( u > n - m );
	for( int k = head[u]; k; k = e[k].next )
	{
		int v = e[k].v;
		if( v == pre )
			continue ;
		sum += DFS( v, u );
		for( int j = sum; j >= 1; j -- )
			for( int i = 0; i <= j; i ++ )
				d[u][j] = max( d[u][j], d[u][j-i] + d[v][i] - e[k].w );
	}
	return sum;
}

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= m; j ++ )
			d[i][j] = -INF;
	for( int i = 1; i <= n - m; i ++ )
	{
		scanf( "%d", &k );
		for( int j = 0; j < k; j ++ )
		{
			scanf( "%d%d", &a, &c );
			AddEdge( i, a, c );
			AddEdge( a, i, c );
		}
	}
	for( int i = n - m + 1; i <= n; i ++ )
		scanf( "%d", &d[i][1] );
	DFS( 1, 1 );
	for( int i = m; i >= 0; i -- )
	{
		if( d[1][i] >= 0 )
		{
			printf( "%d\n", i );
			break ;
		}
	}
	return 0;
}
