#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 101;

int n, m, ans, a[N][N], sum[N][N];

inline bool Check( int a, int b, int x, int y )
{
	int d = x - a + 1, q = d * d;
	int s = sum[x][y] - sum[x][b-1] - sum[a-1][y] + sum[a-1][b-1];
	return s == q;
}

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= m; j ++ )
			scanf( "%d", &a[i][j] );
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= m; j ++ )
			sum[i][j] = sum[i][j-1] + a[i][j];
	for( int j = 1; j <= m; j ++ )
		for( int i = 1; i <= n; i ++ )
			sum[i][j] += sum[i-1][j];
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = 1; j <= m; j ++ )
		{
			if( a[i][j] == 0 )
				continue ;
			for( int k = 0; i + k <= n && j + k <= m; k ++ )
			{
				if( Check( i, j, i + k, j + k ) )
					ans = max( ans, k + 1 );
				else
					break ;
			}
		}
	}
	printf( "%d\n", ans );
	return 0;
}
