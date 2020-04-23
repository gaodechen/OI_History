#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, q )		memcpy( p, q, sizeof( q ) )

using	namespace	std;
typedef long long	data;
const	int N = 20, M = ( 1 << 20 );

data d[M];
int t, n, G[N][N];

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d", &n );
		for( int i = 0; i < n; i ++ )
			for( int j = 0; j < n; j ++ )
				scanf( "%d", &G[i][j] );
		memset( d, 0, sizeof( d ) );
		d[0] = 1;
		for( int mask = 0; mask < ( 1 << n ); mask ++ )
		{
			int k = __builtin_popcount( mask );
			for( int i = 0; i < n; i ++ )
				if( G[k][i] && ( ( mask & ( 1 << i ) ) == 0 ) )
					d[mask|(1<<i)] += d[mask];
		}
		printf( "%lld\n", d[(1<<n)-1] );
	}
	return 0;
}
