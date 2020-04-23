#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int INF = 0x3f3f3f3f;
const	int N = 105, M = 1200;

int t, n, m, b, p, d[N][M];

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d", &n );
		memset(d, 0x3f, sizeof(d));
		for(int k = 1; k <= n; k ++)
		{
			scanf("%d", &m);
			for(int i = 1; i <= m; i ++)
			{
				scanf("%d%d", &b, &p);
				if( k == 1 )
					d[1][b] = min(d[1][b], p);
				else
				{
					for( int j = M; j; j -- )
					{
						int t = min(b, j);
						d[k][t] = min(d[k][t], d[k-1][j] + p);
					}
				}
			}
		}
		double ans = 0;
		for( int j = 0; j <= M; j ++ )
			if( d[n][j] < INF && d[n][j] )
				ans = max( ans, 1.0 * j / d[n][j] );
		printf( "%.3f\n", ans );
	}
	return 0;
}
