#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 1e3 + 5, M = 1e5 + 5;

int t, n, m;
bool G[N][N];

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		int ans = 1;
		scanf( "%d%d", &n, &m );
		memset( G, 0, sizeof( G ) );
		for( int i = 0; i < m; i ++ )
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			G[u][v] = 1;
		}
		for( int i = 1; i <= n; i ++ )
		{
			for( int j = 1; j <= n; j ++ )
			{
				if( G[i][j] ) for( int k = 1; k <= n; k ++ )
				{
					if( G[j][k] && !G[i][k] )
					{
						ans = 0;
						break ;
					}
				}
			}
		}
		printf( "%s\n", ans ? "Yes" : "No" );
	}
	return 0;
}
