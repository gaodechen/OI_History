#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int INF = 100000000;
const	int N = 210, M = 1010;

int n, m;
int z[M], d[M][N];
int dl[N][N], ds[N][N];

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 && n )
	{
		for( int i = 0; i < n; i ++ )
		{
			for( int j = 0; j < n; j ++ )
			{
				if( i == j )
					dl[i][j] = ds[i][j] = 0;
				else
					dl[i][j] = ds[i][j] = INF;
			}
		}
		for( int i = 0; i < m; i ++ )
		{
			char s[2];
			int u, v, t;
			scanf( "%d%d%d%s", &u, &v, &t, s );
			u --, v --;
			if( s[0] == 'L' )
			{
				dl[u][v] = min( dl[u][v], t );
				dl[v][u] = dl[u][v];
			}
			else
			{
				ds[u][v] = min( ds[u][v], t );
				ds[v][u] = ds[u][v];
			}
		}
		int r;
		scanf( "%d", &r );
		for( int i = 0; i < r; i ++ )
		{
			scanf( "%d", &z[i] );
			z[i] --;
		}
		for( int k = 0; k < n; k ++ )
		{
			for( int i = 0; i < n; i ++ )
			{
				for( int j = 0; j < n; j ++ )
				{
					dl[i][j] = min( dl[i][j], dl[i][k] + dl[k][j] );
					ds[i][j] = min( ds[i][j], ds[i][k] + ds[k][j] );
				}
			}
		}
		for( int i = 0; i < r; i ++ )
			for( int j = 0; j < N; j ++ )
				d[i][j] = INF;
		for( int i = 0; i < n; i ++ )
			d[0][i] = ds[z[0]][i] + dl[i][z[0]];
		for( int i = 1; i < r; i ++ )
		{
			for( int j = 0; j < n; j ++ )
			{
				for( int k = 0; k < n; k ++ )
				{
					if( j != k )
						d[i][j] = min( d[i][j], d[i-1][k] + dl[z[i-1]][k] + ds[k][j] + dl[j][z[i]] );
					else
						d[i][j] = min( d[i][j], d[i-1][j] + dl[z[i-1]][z[i]] );
				}
			}
		}
		int ans = INF;
		for( int i = 0; i < n; i ++ )
			ans = min( ans, d[r-1][i] );
		printf( "%d\n", ans );
	}
	return 0;
}
