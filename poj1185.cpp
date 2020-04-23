#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 101, M = 150;

int n, m, tick, map[N], cnt[M], state[M], d[N][N][M];

inline bool Check( int x )
{
	if( x & ( x << 1 ) )
		return 0;
	if( x & ( x << 2 ) )
		return 0;
	return 1;
}

inline int Count( int i )
{
	int res = 0;
	while( i )
	{
		i &= ( i - 1 );
		res ++;
	}
	return res;
}

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ )
	{
		char buf[11];
		scanf( "%s", buf );
		for( int j = 0; j < m; j ++ )
			if( buf[j] == 'H' )
				map[i] += ( 1 << j );
	}
	for( int i = 0; i < ( 1 << m ); i ++ )
	{
		if( Check( i ) )
		{
			state[tick] = i;
			cnt[tick++] = Count( i );
		}
	}
	for( int j = 0; j < tick; j ++ )
		if( !( map[1] & state[j] ) )
			d[1][j][0] = cnt[j];
	for( int k = 2; k <= n; k ++ )
	{
		for( int i = 0; i < tick; i ++ )
		{
			if( map[k] & state[i] )
				continue ;
			for( int j = 0; j < tick; j ++ )
			{
				if( map[k-1] & state[j] || state[i] & state[j] )
					continue ;
				for( int t = 0; t < tick; t ++ )
				{
					if( map[k-2] & state[t] || state[t] & state[j] || state[t] & state[i] )
						continue ;
					d[k][i][j] = max( d[k][i][j], d[k-1][j][t] + cnt[i] );
				}
			}
		}
	}
	int res = 0;
	for( int j = 0; j < tick; j ++ )
		for( int k = 0; k < tick; k ++ )
			res = max( res, d[n][j][k] );
	printf( "%d\n", res );
	return 0;
}
