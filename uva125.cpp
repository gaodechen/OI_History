#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 110;

int n, m, tick, G[N][N];

int main()
{
	while( scanf( "%d", &n ) == 1 )
	{
		m = 0;
		memset( G, 0, sizeof( G ) );
		for( int i = 1; i <= n; i ++ )
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			G[u][v] = 1;
			m = max( m, max( u, v ) );
		}
		for( int k = 0; k <= m; k ++ )
			for( int i = 0; i <= m; i ++ )
				for( int j = 0; j <= m; j ++ )
					G[i][j] += G[i][k] * G[k][j];
		for( int k = 0; k <= m; k ++ )
		{
			if( G[k][k] )
			{
				G[k][k] = -1;
				for( int i = 0; i <= m; i ++ )
					for( int j = 0; j <= m; j ++ )
						if( G[i][k] && G[k][j] )
							G[i][j] = -1;
			}
		}
		printf( "matrix for city %d\n", tick ++ );
		for( int i = 0; i <= m; i ++ )
		{
			printf( "%d", G[i][0] );
			for( int j = 1; j <= m; j ++ )
				printf( " %d", G[i][j] );
			printf( "\n" );
		}
	}
	return 0;
}
