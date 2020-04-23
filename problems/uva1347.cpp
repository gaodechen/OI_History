#include	<cmath>
#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int			N = 51;
const	double		INF = 0x3f3f3f3f3f3f3f3f;

int n, x[N], y[N];
double dis[N][N], d[N][N];

int main()
{
	while( scanf( "%d", &n ) == 1 )
	{
		memset( d, 0, sizeof( d ) );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d%d", &x[i], &y[i] );
		for( int i = 1; i <= n; i ++ )
		{
			for( int j = 1; j <= n; j ++ )
			{
				double d1 = x[i] - x[j], d2 = y[i] - y[j];
				dis[i][j] = sqrt( d1 * d1 + d2 * d2 );
			}
		}
		d[2][1] = dis[2][1];
		for( int i = 3; i <= n; i ++ )
		{
			d[i][i-1] = INF;
			for( int j = 1; j < i - 1; j ++ )
			{
				d[i][i-1] = min( d[i][i-1], d[i-1][j] + dis[i][j] );
				d[i][j] = d[i-1][j] + dis[i-1][i];
			}
		}
		double ans = INF;
		for( int i = 1; i < n; i ++ )
			ans = min( ans, d[n][i] + dis[n][i] );
		printf( "%.2lf\n", ans );
	}
	return 0;
}
