#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 301, M = 25001;
const	int INF = 0x3f3f3f3f;

int G[N][N], n, m, t;

int main()
{
	scanf( "%d%d%d", &n, &m, &t );
	memset( G, 0x3f, sizeof( G ) );
	for( int i = 1; i <= m; i ++ )
	{
		int u, v, h;
		scanf( "%d%d%d", &u, &v, &h );
		G[u][v] = h;
	}
	for( int k = 1; k <= n; k ++ )
		for( int i = 1; i <= n; i ++ )
			for( int j = 1; j <= n; j ++ )
				G[i][j] = min( G[i][j], max( G[i][k], G[k][j] ) );
	for( int i = 1; i <= t; i ++ )
	{
		int u, v;
		scanf( "%d%d", &u, &v );
		printf( "%d\n", G[u][v] >= INF ? -1 : G[u][v] );
	}
	return 0;
}
