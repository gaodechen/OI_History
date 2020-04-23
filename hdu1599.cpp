#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 110, INF = 0xfffffff;

int n, m, G[N][N], d[N][N];

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		for( int i = 1; i <= n; i ++ )
			for( int j = 1; j <= n; j ++ )
				G[i][j] = INF;
		while( m -- )
		{
			int u, v, w;
			scanf( "%d%d%d", &u, &v, &w );
			if( w < G[u][v] )
				G[u][v] = G[v][u] = w;
		}
		for( int i = 1; i <= n; i ++ )
			for( int j = 1; j <= n; j ++ )
				d[i][j] = G[i][j];
		int ans = INF;
		for( int k = 1; k <= n; k ++ )
		{
			for( int i = 1; i < k; i ++ )
				for( int j = 1; j < i; j ++ )
					ans = min( ans, d[i][j] + G[k][i] + G[k][j] );
			for( int i = 1; i <= n; i ++ )
				for( int j = 1; j <= n; j ++ )
					d[i][j] = min( d[i][j], d[i][k] + d[k][j] );
		}
		if( ans == INF )
			printf( "It's impossible.\n" );
		else
			printf( "%d\n", ans );
	}
	return 0;
}
