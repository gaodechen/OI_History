#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
const	int N = 2e3 + 5;
const	int INF = 0x3f3f3f3f;

int d[N][N];
int n, a[N], t[N];

inline int ABS( int x )
{
	return x > 0 ? x : -x;
}

int main()
{
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &a[i] );
	memcpy( t, a, sizeof( a ) );
	memset( d, INF, sizeof( INF ) );
	sort( t + 1, t + n + 1 );
	int p, q = unique( t + 1, t + n + 1 ) - t - 1;
	for( int i = 1; i <= q; i ++ )
		if( t[i] == a[1] )
			p = i;
	d[1][p] = 0;
	for( int i = 2; i <= n; i ++ )
	{
		int tmp = INF;
		for( int j = 1; j <= q; j ++ )
		{
			tmp = min( tmp, d[i-1][j] );
			d[i][j] = tmp + ABS( a[i] - t[j] );
		}
	}
	int ans = INF;
	for( int i = 1; i <= q; i ++ )
		ans = min( ans, d[n][i] );
	printf( "%d\n", ans );
	return 0;
}
