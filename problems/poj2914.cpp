#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, q )		memcpy( p, q, sizeof( q ) )

using	namespace	std;
const	int N = 520, INF = 0x3f3f3f3f;

bool vis[N];
int G[N][N], v[N], w[N];

int StoerWagner( int n )
{
	int minCut = INF;
	for( int i = 0; i < n; i ++ )
		v[i] = i;
	while( n > 1 )
	{
		int pre = 0;
		set( w, 0 ), set( vis, 0 );
		for( int i = 1; i < n; i ++ )
		{
			int k = -1;
			for( int j = 1; j < n; j ++ )
			{
				if( !vis[v[j]] )
				{
					w[v[j]] += G[v[pre]][v[j]];
					if( k == -1 || w[v[k]] < w[v[j]] )
						k = j;
				}
			}
			vis[v[k]] = 1;
			if( i == n - 1 )
			{
				int s = v[pre], t = v[k];
				minCut = min( minCut, w[t] );
				for( int j = 0; j < n; j ++ )
				{
					G[s][v[j]] += G[v[j]][t];
					G[v[j]][s] += G[v[j]][t];
				}
				v[k] = v[--n];
			}
			pre = k;
		}
	}
	return minCut;
}

int main()
{
	int n, m;
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		set( G, 0 );
		while( m -- )
		{
			int u, v, w;
			scanf( "%d%d%d", &u, &v, &w );
			G[u][v] += w;
			G[v][u] += w;
		}
		printf( "%d\n", StoerWagner( n ) );
	}
	return 0;
}
