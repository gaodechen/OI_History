#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 101;

int n, m;
double G[N][N], cnt[N][N], ans[N];

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= n; j ++ )
			if( i != j )
				G[i][j] = 1e15;
	for( int i = 1; i <= m; i ++ )
	{
		int u, v, w;
		scanf( "%d%d%d", &u, &v, &w );
		G[u][v] = G[v][u] = w;
		cnt[u][v] = cnt[v][u] = 1;
	}
	for( int k = 1; k <= n; k ++ )
	{
		for( int i = 1; i <= n; i ++ )
		{
			for( int j = 1; j <= n; j ++ )
			{
				if( G[i][j] == G[i][k] + G[k][j] )
					cnt[i][j] += cnt[i][k] * cnt[k][j];
				else if( G[i][j] > G[i][k] + G[k][j])
				{
					G[i][j] = G[i][k] + G[k][j];
					cnt[i][j] = cnt[i][k] * cnt[k][j];
				}
			}
		}
	}
	// (i, j)'s SP may not pass k
	// Though given a undirected connected graph
	for( int k = 1; k <= n; k ++ )
		for( int i = 1; i <= n; i ++ )
			for( int j = 1; j <= n; j ++ )
				if( cnt[i][j] > 0 && G[i][k] + G[k][j] == G[i][j] )
					ans[k] += ( cnt[i][k] * cnt[k][j] ) / cnt[i][j];
	for( int i = 1; i <= n; i ++ )
		printf( "%.3lf\n", ans[i] );
	return 0;
}

