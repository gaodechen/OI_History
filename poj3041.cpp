#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<vector>

using	namespace	std;
const	int N = 501;

vector< int > e[N];
int n, k, vis[N], link[N];

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
	for( int i = 1; i <= n; i ++ )
	{
		memset( vis, 0, sizeof( vis ) );
		if( Augment( i ) )
			sum ++;
	}
	return sum;
}

int main()
{
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= k; i ++ )
	{
		int a, b;
		scanf( "%d%d", &a, &b );
		e[a].push_back( b );
	}
	printf( "%d\n", Hungarian() );
	return 0;
}
