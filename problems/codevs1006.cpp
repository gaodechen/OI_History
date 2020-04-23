#include	<cstdio>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e2 + 5;

int n, max_, ans, a[N], d[N][N];

int main()
{
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
	{
		scanf( "%d", &a[i] );
		max_ = max( max_, a[i] );
	}
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= i; j ++ )
			d[i][j] = 1 + ( i != j );
	sort( a + 1, a + n + 1 );
	if( a[1] == a[n] )
	{
		printf( "%d\n", n );
		return 0;
	}
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = 1; j < i; j ++ )
		{
			for( int k = j; k >= 1; k -- )
			{
				if( a[i] - a[j] == a[j] - a[k] )
				{
					d[i][j] += d[j][k] - 1;
					break ;
				}
			}
			ans = max( ans, d[i][j] );
		}
	}
	printf( "%d\n", ans );
	return 0;
}
