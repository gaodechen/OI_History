#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<cmath>

using	namespace	std;
const	int INF = 0x3f3f3f3f;
const	int N = 17, M = ( 1 << 16 );

struct Point
{
	int x, y;
} e[N];

inline int Distance( Point &a, Point &b )
{
	int d1 = a.x - b.x;
	int d2 = a.y - b.y;
	return ceil( sqrt( d1 * d1 + d2 * d2 ) );
}

bool mark[M];
int n, m, tik, f[M], c[N];
int state[M], cost[M], G[N][N], d[M][N];

inline bool Check( int s )
{
	int sum = 0;
	for( int i = 0; i < n; i ++ )
		if( s & ( 1 << i ) )
			sum += c[i];
	return sum <= m;
}

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		memset( f, INF, sizeof( f ) );
		memset( d, INF, sizeof( d ) );
		memset( mark, 0, sizeof( mark ) );
		memset( cost, INF, sizeof( cost ) );
		for( int i = 0; i < n; i ++ )
			scanf( "%d%d", &e[i].x, &e[i].y );
		for( int i = 0; i < n; i ++ )
			scanf( "%d", &c[i] );
		for( int i = 0; i < n; i ++ )
			for( int j = 0; j < n; j ++ )
				G[i][j] = Distance( e[i], e[j] );
		tik = f[0] = 0;
		for( int s = 0; s < ( 1 << n ); s ++ )
			if( Check( s ) )
				mark[s] = 1, state[tik++] = s;
		for( int s = 0; s < ( 1 << n ); s ++ )
			for( int i = 0; i < tik; i ++ )
				f[s|state[i]] = min( f[s|state[i]], f[s] + 1 );
		int num = f[(1<<n)-1];
		if( num >= INF )
		{
			printf( "-1 -1\n" );
			continue ;
		}
		d[1][0] = 0;
		for( int s = 0; s < ( 1 << n ); s ++ ) if( mark[s] )
		{
			for( int i = 0; i < n; i ++ ) if( s & ( 1 << i ) )
			{
				cost[s] = min( cost[s], d[s][i] + G[i][0] );
				for( int j = 0; j < n; j ++ ) if( !( s & ( 1 << j ) ) )
					d[s|(1<<j)][j] = min( d[s|(1<<j)][j], d[s][i] + G[i][j] );
			}
		}
		for( int s = 0; s < ( 1 << n ); s ++ ) if( s & 1 )
			for( int q = ( s - 1 ) & s; q; q = s & ( q - 1 ) )
				cost[s] = min( cost[s], cost[q|1] + cost[(s^q)|1] );
		printf( "%d %d\n", num, cost[(1<<n)-1] );
	}
	return 0;
}
