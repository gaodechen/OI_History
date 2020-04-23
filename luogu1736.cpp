#include	<cstdio>
#include	<cstring>
#include	<iostream>

#define		rep( i, n )		for( int i = 1; i <= n; i ++ )

using	namespace	std;
const	int N = 2600;

int up[N][N], side[N][N];
int n, m, ans, a[N][N], d[N][N];

int main()
{
	scanf( "%d%d", &n, &m );
	rep( i, n ) rep( j, m )
		scanf( "%d", &a[i][j] );

	rep( i, n ) rep( j, m ) if( !a[i][j] )
		up[i][j] = up[i-1][j] + 1;
	rep( i, n ) rep( j, m ) if( !a[i][j] )
		side[i][j] = side[i][j-1] + 1;
	rep( i, n ) rep( j, m ) if( a[i][j] )
		d[i][j] = min( d[i-1][j-1], min( up[i-1][j], side[i][j-1] ) ) + 1;
	rep( i, n ) rep( j, m )
		ans = max( ans, d[i][j] );

	memset( d, 0, sizeof( d ) );
	rep( i, n ) for( int j = m; j; j -- ) if( !a[i][j] )
		side[i][j] = side[i][j+1] + 1;
	rep( i, n ) rep( j, m ) if( a[i][j] )
		d[i][j] = min( d[i-1][j+1], min( up[i-1][j], side[i][j+1] ) ) + 1;
	rep( i, n ) rep( j, m )
		ans = max( ans, d[i][j] );
	printf( "%d\n", ans );

	return 0;
}
