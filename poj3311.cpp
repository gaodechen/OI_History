#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
const	int INF = 0x3f3f3f3f;
const	int N = 15, M = ( 1 << 11 );

int n, G[N][N], d[M][N];

int main()
{
	while( scanf( "%d", &n ) == 1 && n )
	{
		n ++;
		for( int i = 0; i < n; i ++ )
			for( int j = 0; j < n; j ++ )
				scanf( "%d", &G[i][j] );
		for( int k = 0; k < n; k ++ )
			for( int i = 0; i < n; i ++ )
				for( int j = 0; j < n; j ++ )
					G[i][j] = min( G[i][j], G[i][k] + G[k][j] );
		set( d, 0x3f );
		d[(1<<n)-1][0] = 0;
		for( int s = ( 1 << n ) - 2; s >= 0; s -- )
			for( int u = 0; u < n; u ++ )
				for( int v = 0; v < n; v ++ )
					d[s][u] = min( d[s][u], d[s|(1<<v)][v] + G[u][v] );
		printf( "%d\n", d[0][0] );
	}
	return 0;
}
