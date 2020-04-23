#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<vector>

using	namespace	std;
const	int N = 1e3 + 5;

vector< int > e[N], node[N];
int t, n, s, k, ans, pre[N], mark[N];

void DFS( int u, int f, int d )
{
	pre[u] = f;
	int q = ( int )e[u].size();
	if( q == 1 && d > k )
		node[d].push_back( u );
	for( int i = 0; i < q; i ++ )
		if( e[u][i] != f )
			DFS( e[u][i], u, d + 1 );
	return ;
}

void DFS_( int u, int f, int d )
{
	if( d > k )
		return ;
	mark[u] = 1;
	for( int i = 0; i < ( int )e[u].size(); i ++ )
		if( e[u][i] != f )
			DFS_( e[u][i], u, d + 1 );
	return ;
}

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		ans = 0;
		memset( mark, 0, sizeof( mark ) );
		scanf( "%d%d%d", &n, &s, &k );
		for( int i = 1; i <= n; i ++ )
			e[i].clear(), node[i].clear();
		for( int i = 1; i < n; i ++ )
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			e[u].push_back( v );
			e[v].push_back( u );
		}
		DFS( s, -1, 0 );
		for( int dep = n - 1; dep > k; dep -- )
		{
			for( int i = 0; i < ( int )node[dep].size(); i ++ )
			{
				int u = node[dep][i];
				if( !mark[u] )
				{
					for( int i = 0; i < k; i ++ )
						u = pre[u];
					DFS_( u, -1, 0 );
					ans ++;
				}
			}
		}
		printf( "%d\n", ans );
	}
	return 0;
}
