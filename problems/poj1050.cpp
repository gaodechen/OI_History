#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 101;

int n, ans, a[N][N], sum[N][N];

int main()
{
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = 1; j <= n; j ++ )
		{
			scanf( "%d", &a[i][j] );
			sum[i][j] = sum[i-1][j] + a[i][j];
		}
	}
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = i + 1; j <= n; j ++ )
		{
			int tmp = 0;
			for( int k = 1; k <= n; k ++ )
			{
				int t = sum[j][k] - sum[i-1][k];
				tmp = max( t, tmp + t );
				ans = max( ans, tmp );
			}
		}
	}
	printf( "%d\n", ans );
	return 0;
}
