#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<vector>

using	namespace	std;
const	int N = 500;

bool G[N][N];
vector< int > e[N];
int n, m, q, c, vis[N], link[N];

bool Augment( int u )
{
	for( int i = 0; i < ( int )e[u].size(); i ++ )
	{
		int &v = e[u][i];
		if( !vis[v] )
		{
			vis[v] = 1;
			if( link[v] == -1 || Augment( link[v] ) )
			{
				link[v] = u;
				return true;
			}
		}
	}
	return false;
}

int Hungarian()
{
	int sum = 0;
	memset( link, -1, sizeof( link ) );
	for( int i = 1; i <= n + m; i ++ )
	{
		memset( vis, 0, sizeof( vis ) );
		if( Augment( i ) )
			sum ++;
	}
	return sum;
}

int main()
{
	while( scanf( "%d%d%d", &n, &m, &q ) && ( n || m || q ) )
	{
		memset( G, 0, sizeof( G ) );
		for( int i = 1; i < N; i ++ )
			e[i].clear();
		while( q -- )
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			G[u][v+n] = 1;
		}
		for( int i = 1; i <= n; i ++ )
			for( int j = n + 1; j <= n + m; j ++ )
				if( !G[i][j] )
					e[i].push_back( j );
		printf( "Case %d: %d\n", ++ c, n + m - Hungarian() );
	}
	return 0;
}
