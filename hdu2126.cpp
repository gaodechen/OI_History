#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int M = 501, N = 31;

int t, n, m, ans, cost[N], d[M][N];

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		ans = 0;
		memset( d, 0, sizeof( d ) );
		scanf( "%d%d", &n, &m );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d", &cost[i] );
		for( int j = 0; j <= m; j ++ )
			d[j][0] = 1;
		for( int i = 1; i <= n; i ++ )
		{
			for( int j = m; j >= cost[i]; j -- )
			{
				for( int k = 1; k <= i; k ++ )
				{
					d[j][k] += d[j-cost[i]][k-1];
					if( d[j][k] )
						ans = max( ans, k );
				}
			}
		}
		if( ans )
			printf( "You have %d selection(s) to buy with %d kind(s) of souvenirs.\n", d[m][ans], ans );
		else
			printf( "Sorry, you can't buy anything.\n" );
	}
	return 0;
}
