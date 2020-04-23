#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<vector>

using	namespace	std;
const	int N = 1501;

vector< int > e[N];
int link[N], used[N], n;

bool DFS( int u )
{
	for( int i = 0; i < ( int )e[u].size(); i ++ )
	{
		int &v = e[u][i];
		if( !used[v] )
		{
			used[v] = 1;
			if( link[v] == -1 || DFS( link[v] ) )
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
	for( int u = 0; u < n; u ++ )
	{
		memset( used, 0, sizeof( used ) );
		if( DFS( u ) )
			sum ++;
	}
	return sum;
}

int main()
{
	while( scanf( "%d", &n ) == 1 )
	{
		int u, v, k;
		for( int i = 0; i < n; i ++ )
			e[i].clear();
		for( int i = 0; i < n; i ++ )
		{
			scanf( "%d:(%d)", &u, &k );
			while( k -- )
			{
				scanf( "%d", &v );
				e[u].push_back( v );
				e[v].push_back( u );
			}
		}
		printf( "%d\n", Hungarian() / 2 );
	}
	return 0;
}
