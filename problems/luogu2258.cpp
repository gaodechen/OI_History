#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<bitset>

using	namespace	std;
const	int N = 30, INF = 0x3f3f3f3f;

bitset< N > mask;
int n, m, r, c;
int f[N][N], a[N][N], w[N][N];

inline int ABS( int x )
{
	return x < 0 ? -x : x;
}

inline int Compute( int x )
{
	int r = 0, k = INF;
	for( int i = 0; i < m; i ++ )
	{
		if( !mask[i] )
			continue ;
		if( k != INF )
			r += ABS( a[x][i+1] - k );
		k = a[x][i+1];
	}
	return r;
}

inline int Compute( int x, int y )
{
	int r = 0;
	if( y == 0 )
		return 0;
	for( int i = 0; i < m; i ++ )
		if( mask[i] )
			r += ABS( a[x][i+1] - a[y][i+1] );
	return r;
}

inline void Init()
{
	for( int i = 1; i <= n; i ++ )
	{
		int tmp = Compute( i );
		for( int j = 0; j < i; j ++ )
			w[i][j] = tmp + Compute( i, j );
	}
	return ;
}

int main()
{
	scanf( "%d%d%d%d", &n, &m, &r, &c );
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= m; j ++ )
			scanf( "%d", &a[i][j] );
	int ans = INF;
	for( int s = 0; s < ( 1 << m ); s ++ )
	{
		mask = s;
		if( ( int ) mask.count() != c )
			continue ;
		memset( f, INF, sizeof( f ) );
		Init(), f[0][0] = 0;
		for( int i = 1; i <= n; i ++ )
		{
			for( int j = 1; j <= r; j ++ )
				for( int k = 0; k < i; k ++ )
					f[i][j] = min( f[k][j-1] + w[i][k], f[i][j] );
			ans = min( ans, f[i][r] );
		}
	}
	printf( "%d\n", ans );
	return 0;
}
