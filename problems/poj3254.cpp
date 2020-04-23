#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int MOD = 100000000;
const	int N = 12, M = ( 1 << 12 );

int n, m, k, map[N], state[N], d[N][M];

inline bool Check1( int x )
{
	return ( x & ( x << 1 ) );
}

inline bool Check2( int i, int j )
{
	return !( map[i] & state[j] );
}

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = 1, x; j <= m; j ++ )
		{
			scanf( "%d", &x );
			if( x == 0 )
				map[i] += ( 1 << ( j - 1 ) );
		}
	}
	int k = 0;
	for( int i = 0; i < ( 1 << m ); i ++ )
		if( !Check1( i ) )
			state[k++] = i;
	for( int i = 0; i < k; i ++ )
		if( Check2( 1, i ) )
			d[1][i] = 1;
	for( int i = 2; i <= n; i ++ )
	{
		for( int j = 0; j < k; j ++ )
		{
			if( !Check2( i, j ) )
				continue ;
			for( int f = 0; f < k; f ++ )
				if( Check2( i - 1, f ) && !( state[j] & state[f] ) )
					d[i][j] += d[i-1][f];
		}
	}
	int res = 0;
	for( int i = 0; i < k; i ++ )
	{
		res += d[n][i];
		res %= MOD;
	}
	printf( "%d\n", res );
	return 0;
}
