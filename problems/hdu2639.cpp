#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 1e3 + 5, K = 31;

int t, n, v, q, val[N], cost[N], d[N][K], a[K], b[K];

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		memset( d, 0, sizeof( d ) );
		scanf( "%d%d%d", &n, &v, &q );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d", &val[i] );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d", &cost[i] );
		for( int i = 1; i <= n; i ++ )
		{
			for( int j = v; j >= cost[i]; j -- )
			{
				for( int k = 1; k <= q; k ++ )
				{
					a[k] = d[j-cost[i]][k] + val[i];
					b[k] = d[j][k];
				}
				a[q+1] = b[q+1] = -1;
				int x = 1, y = 1, z = 1;
				while( z <= q && ( a[x] != -1 || b[y] != -1 ) )
				{
					if( a[x] > b[y] )
						d[j][z] = a[x], x ++;
					else
						d[j][z] = b[y], y ++;
					if( d[j][z] != d[j][z-1] )
						z ++;
				}
			}
		}
		cout << d[v][q] << endl;
	}
	return 0;
}
