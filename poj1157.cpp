#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int INF = 0x3f3f3f3f, N = 101;

int n, m, a[N][N], d[N][N];

int main()
{
	set( d, 128 );
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= m; j ++ )
			scanf( "%d", &a[i][j] );
	for( int j = 1; j <= m; j ++ )
		d[1][j] = a[1][j];
	for( int i = 2; i <= n; i ++ )
		for( int j = i; j <= m; j ++ )
			for( int k = i - 1; k < j; k ++ )
				d[i][j] = max( d[i][j], d[i-1][k] + a[i][j] );
	int ans = 0;
	for( int j = 1; j <= m; j ++ )
		ans = max( ans, d[n][j] );
	printf( "%d\n", ans );
	return 0;
}
