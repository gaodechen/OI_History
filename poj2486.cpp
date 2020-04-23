#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<vector>

using	namespace	std;
const	int N = 2e2 + 5;

vector< int > e[N];
int n, k, d[N][N][2];

void DFS( int u, int pre )
{
	for( int i = 0; i < ( int )e[u].size(); i ++ )
	{
		int &v = e[u][i];
		if( v == pre )
			continue ;
		DFS( v, u );
		for( int j = k; j >= 0; j -- )
		{
			for( int i = 0; i <= j; i ++ )
			{
				d[u][j][0] = max(d[u][j][0], d[u][j - i][0] + d[v][i - 2][0]);
				d[u][j][1] = max(d[u][j][1], d[u][j - i][1] + d[v][i - 2][0]);
				d[u][j][1] = max(d[u][j][1], d[u][j - i][0] + d[v][i - 1][1]);
			}
		}
	}
	return ;
}

int main()
{
	while( scanf( "%d%d", &n, &k ) == 2 )
	{
		memset( d, 0, sizeof( d ) );
		for( int i = 1; i <= n; i ++ )
		{
			int val;
			e[i].clear();
			scanf( "%d", &val );
			for( int j = 0; j <= k; j ++ )
				d[i][j][0] = d[i][j][1] = val;
		}
		for( int i = 1; i < n; i ++ )
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			e[u].push_back( v );
			e[v].push_back( u );
		}
		DFS( 1, 1 );
		printf( "%d\n", d[1][k][1] );
	}
	return 0;
}
