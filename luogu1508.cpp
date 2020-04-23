#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 201;

int n, m, a[N][N], d[N][N];

int main()
{
	memset( d, 128, sizeof( d ) );
	scanf( "%d%d", &n, &m );
	for( int i = n; i > 0; i -- )
		for( int j = 1; j <= m; j ++ )
			scanf( "%d", &a[i][j] );
	d[0][(m+1)/2] = 0;
	for( int i = 0; i <= n; i ++ )
	{
		for( int j = 1; j <= m; j ++ )
		{
			if( j > 1 )
				d[i+1][j-1] = max( d[i+1][j-1], d[i][j] + a[i+1][j-1] );
			if( j < m )
				d[i+1][j+1] = max( d[i+1][j+1], d[i][j] + a[i+1][j+1] );
			d[i+1][j] = max( d[i+1][j], d[i][j] + a[i+1][j] );
		}
	}
	int ans = -0x3f3f3f3f;
	for( int j = 1; j <= m; j ++ )
		ans = max( ans, d[n][j] );
	printf( "%d\n", ans );
	return 0;
}
