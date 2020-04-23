#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 201, INF = 0x3f3f3f3f;

int n, g, a[N], d[N][N], p[N][N], sum[N];

int main()
{
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &a[i] );
	for( int i = n + 1; i < n + n; i ++ )
		a[i] = a[i-n];
	g = n, n += n - 1;
	{
		memset( d, INF, sizeof( d ) );
		for( int i = 1; i <= n; i ++ )
			sum[i] = a[i] + sum[i-1];
		for( int i = 1; i <= n; i ++ )
			d[i][i] = 0, p[i][i] = i;
		for( int k = 2; k <= g; k ++ )
		{
			for( int i = 1; i + k - 1 <= n; i ++ )
			{
				int tmp = INF, pos, q = i + k - 1;
				int w = sum[q] - sum[i-1];
				for( int j = p[i][q-1]; j <= p[i+1][q]; j ++ )
					if( d[i][j] + d[j+1][q] + w < tmp )
						tmp = d[i][j] + d[j+1][q] + w, pos = j;
				d[i][q] = tmp, p[i][q] = pos;
			}
		}
		int ans = INF;
		for( int i = 1; i + g - 1 <= n; i ++ )
			ans = min( d[i][i+g-1], ans );
		printf( "%d\n", ans );
	}
	{
		memset( d, 128, sizeof( d ) );
		for( int i = 1; i <= n; i ++ )
			d[i][i] = 0;
		for( int k = 2; k <= g; k ++ )
		{
			for( int i = 1; i + k - 1 <= n; i ++ )
			{
				int j = i + k - 1;
				for( int k = i; k <= j; k ++ )
					d[i][j] = max( d[i][j], d[i][k] + d[k+1][j] + sum[j] - sum[i-1] );
			}
		}
		int ans = -INF;
		for( int i = 1; i + g - 1 <= n; i ++ )
			ans = max( d[i][i+g-1], ans );
		printf( "%d\n", ans );
	}
	return 0;
}
