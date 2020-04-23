#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 1e2 + 10, M = N * 510;

int t, n, sum, a[N], d[M];

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		memset( d, 0, sizeof( d ) );
		sum = 0;
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%d", &a[i] );
			sum += a[i];
		}
		for( int i = 1; i <= n; i ++ )
			for( int j = sum / 2; j >= a[i]; j -- )
				d[j] = max( d[j], d[j-a[i]] + a[i] );
		printf( "%d\n", sum - 2 * d[sum/2] );
	}
	return 0;
}
