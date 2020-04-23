#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
const	int INF = 0x3f3f3f3f;
const	int N = 11, M = ( 1 << 11 );

int x[N], y[N], cnt, d[M][N], G[N][N];

inline int ABS( var x )
{
	return x < 0 ? -x : x;
}

int main()
{
	int n, m;
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		cnt = 1;
		x[0] = y[0] = 1;
		for( int i = 1; i <= n; i ++ )
		{
			for( int j = 1, t; j <= m; j ++ )
			{
				scanf( "%d", &t );
				if( i == 1 && j == 1 )
					continue ;
				if( t )
					x[cnt] = i, y[cnt++] = j;
			}
		}
		set( G, 0x3f ), set( d, 0x3f );
		for( int i = 0; i < cnt; i ++ )
			for( int j = 0; j < cnt; j ++ )
				G[i][j] = ABS( x[i] - x[j] ) + ABS( y[i] - y[j] );
		n = cnt;
		d[(1<<n)-1][0] = 0;
		for( int s = ( 1 << n ) - 2; s >= 0; s -- )
			for( int i = 0; i < n; i ++ )
				for( int j = 0; j < n; j ++ )
					if( !( s & ( 1 << j ) ) )
						d[s][i] = min( d[s][i], d[s|(1<<j)][j] + G[i][j] );
		printf( "%d\n", d[0][0] == INF ? 0 : d[0][0] );
	}
	return 0;
}
