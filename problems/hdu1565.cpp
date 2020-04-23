#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
const	int N = 21, M = 20000;
const	int INF = 0x3f3f3f3f;

int n, m, tick, state[M], G[N][N], cnt[N][M], d[N][M];

inline int Count( int r, int k )
{
	int res = 0;
	for( int i = 0; i < m; i ++ )
		if( k & ( 1 << i ) )
			res += G[r][i];
	return res;
}

int main()
{
	while( scanf( "%d", &n ) == 1 )
	{
		tick = 0;
		for( int i = 0; i < ( 1 << n ); i ++ )
			if( !( i & ( i << 1 ) ) )
				state[tick++] = i;
		set( d, 0 );
		m = n;
		for( int i = 1; i <= n; i ++ )
			for( int j = 0; j < m; j ++ )
				scanf( "%d", &G[i][j] );
		for( int i = 1; i <= n; i ++ )
			for( int j = 0; j < tick; j ++ )
				cnt[i][j] = Count( i, state[j] );
		for( int i = 1; i <= n; i ++ )
			for( int j = 0; j < tick; j ++ )
				for( int k = 0; k < tick; k ++ )
					if( !( state[j] & state[k] ) )
						d[i][j] = max( d[i][j], d[i-1][k] + cnt[i][j] );
		int res = 0;
		for( int j = 0; j < tick; j ++ )
			res = max( d[n][j], res );
		printf( "%d\n", res );
	}
	return 0;
}

