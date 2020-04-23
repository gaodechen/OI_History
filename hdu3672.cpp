#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 6e2;

struct Edge
{
	int v, w, next;
} e[N*2];

int n, q, tick, count, head[N], d[N][N][2];

void AddEdge( int u, int v, int d )
{
	e[++tick].v = v, e[tick].w = d;
	e[tick].next = head[u], head[u] = tick;
	return ;
}

int DFS( int u, int pre )
{
	int sum = 1;
	d[u][1][0] = d[u][1][1] = 0;
	for( int i = head[u]; i; i = e[i].next )
	{
		int &v = e[i].v, &w = e[i].w;
		if( v == pre )
			continue ;
		sum += DFS( v, u );
		for( int j = sum; j + 1; j -- )
		{
			for( int i = 0; i <= j; i ++ )
			{
				d[u][j][0] = min( d[u][j][0], d[u][j-i][0] + d[v][i][0] + 2 * w );
				d[u][j][1] = min( d[u][j][1], d[u][j-i][0] + d[v][i][1] + w );
				d[u][j][1] = min( d[u][j][1], d[u][j-i][1] + d[v][i][0] + 2 * w );
			}
		}
	}
	return sum;
}

int main()
{
	while( scanf( "%d", &n ) && n )
	{
		tick = 0;
		memset( d, 0x3f, sizeof( d ) );
		memset( head, 0, sizeof( head ) );
		for( int i = 1; i < n; i ++ )
		{
			int u, v, w;
			scanf( "%d%d%d", &u, &v, &w );
			AddEdge( ++ u, ++ v, w );
			AddEdge( v, u, w );
		}
		DFS( 1, 1 );
		scanf( "%d", &q );
		printf( "Case %d:\n", ++ count );
		while( q -- )
		{
			int a, ans = 0;
			scanf( "%d", &a );
			for( int j = 1; j <= n; j ++ )
			{
				if( d[1][j][1] <= a )
					ans = j;
				else
					break ;
			}
			printf( "%d\n", ans );
		}
	}
	return 0;
}
