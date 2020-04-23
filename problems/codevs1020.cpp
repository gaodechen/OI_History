#include	<cstdio>
#include	<cstring>
#include	<iostream>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 101, INF = 0x3f3f3f3f;

int n, G[N][N];

int main()
{
	set( G, 0x3f );
	scanf( "%d", &n );
	int u, v, w;
	while( scanf( "%d%d%d", &u, &v, &w ) == 3 )
		G[u][v] = G[v][u] = min( G[u][v], w );
	for( int k = 1; k <= n; k ++ )
	{
		for( int i = 1; i <= n; i ++ )
		{
			for( int j = 1; j <= n; j ++ )
			{
				if( i == j )
					G[i][j] = 0;
				else
					G[i][j] = min( G[i][j], G[i][k] + G[k][j] );
			}
		}
	}
	int ans = INF, pos1, pos2;
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = i + 1; j <= n; j ++ )
		{
			int tmp = -INF;
			for( int k = 1; k <= n; k ++ )
				tmp = max( tmp, min( G[i][k], G[j][k] ) );
			if( tmp < ans )
				ans = tmp, pos1 = i, pos2 = j;
		}
	}
	printf( "%d %d\n", pos1, pos2 );
	return 0;
}
