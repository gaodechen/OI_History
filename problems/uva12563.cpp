#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 55, M = 180;

int c, n, T, t[N], d[N*M], ans;

int main()
{
	scanf( "%d", &c );
	for( int tick = 1; tick <= c; tick ++ )
	{
		ans = 0;
		memset( d, 0x8f, sizeof( d ) );
		scanf( "%d%d", &n, &T );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d", &t[i] );
		d[0] = 0;
		for( int i = 1; i <= n; i ++ )
			for( int j = T - 1; j >= t[i]; j -- )
				d[j] = max( d[j], d[j-t[i]] + 1 );
		for( int k = T - 1; k >= 0; k -- )
			if( d[k] > d[ans] )
				ans = k;
		printf( "Case %d: %d %d\n", tick, d[ans] + 1, ans + 678 );
	}
	return 0;
}
