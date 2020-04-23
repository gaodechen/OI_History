#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 501, INF = 0x3f3f3f3f;

int G[N][N], v[N], w[N];

int StoerWagner( int n )
{
	int minCut = INF;
	for( int i = 1; i <= n; i ++ )
		v[i] = i;
	while( n > 1 )
	{
		int p = 1;
		for( int i = 2; i <= n; i ++ )
			w[v[i]] = 0;
		for( int i = 2; i <= n; i ++ )
		{
			swap( v[p], v[i-1] );
			p = i;
			for( int j = i; j <= n; j ++ )
			{
				w[v[j]] += G[v[i-1]][v[j]];
				if( w[v[p]] < w[v[j]] )
					p = j;
			}
		}
		minCut = min( minCut, w[v[p]] );
		for( int j = 1; j <= n; j ++ )
			G[v[j]][v[p-1]] = G[v[p-1]][v[j]] += G[v[j]][v[p]];
		v[p] = v[--n];
	}
	return minCut;
}

int main()
{
	int n, m;
	scanf( "%d%d", &n, &m );
	for( int i = 0; i < m; i ++ )
	{
		int u, v, w;
		scanf( "%d%d%d", &u, &v, &w );
		G[u][v] += w, G[v][u] += w;
	}
	printf( "%d\n", StoerWagner( n ) );
	return 0;
}
