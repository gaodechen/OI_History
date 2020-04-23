#include	<cstdio>
#include	<cstring>
#include	<iostream> 
using	namespace	std;
const	int K = 11, N = 110, M = 1e4 + 5;

int n, m, p, q, num[K], son[K][N], val[N], cost[N], d[K][M];

int main()
{
	while( scanf( "%d%d%d", &n, &m, &q ) == 3 )
	{
		memset( d, 128, sizeof( d ) );
		memset( d[0], 0, sizeof( d[0] ) );
		memset( num, 0, sizeof( num ) );
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%d%d%d", &p, &cost[i], &val[i] );
			son[p][num[p]++] = i;
		}
		for( int k = 1; k <= q; k ++ )
		{
			for( int i = 0; i < num[k]; i ++ )
			{
				int &p = son[k][i];
				for( int j = m; j >= cost[p]; j -- )
				{
					if( d[k][j-cost[p]] >= 0 )
						d[k][j] = max( d[k][j], d[k][j-cost[p]] + val[p] );
					if( d[k-1][j-cost[p]] >= 0 )
						d[k][j] = max( d[k][j], d[k-1][j-cost[p]] + val[p] );
				}
			}
		}
		if( d[q][m] < 0 )
			printf( "Impossible\n" );
		else
			printf( "%d\n", d[q][m] );
	}
	return 0;
}
