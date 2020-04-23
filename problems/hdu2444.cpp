#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<vector>

using	namespace	std;
const	int N = 2000;

vector< int > e[N];
int n, m, vis[N], link[N], col[N];

bool Color( int u )
{
	for( int i = 0; i < ( int )e[u].size(); i ++ )
	{
		int &v = e[u][i];
		if( col[v] == -1 )
		{
			col[v] = !col[u];
			if( !Color( v ) )
				return false;
		}
		else if( col[v] == col[u] )
			return false;
	}
	return true;
}

bool Augment( int u )
{
	for( int i = 0; i < ( int )e[u].size(); i ++ )
	{
		int &v = e[u][i];
		if(!vis[v])
		{
			vis[v] = 1;
			if(link[v] == -1 || Augment(link[v]))
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
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		memset( col, -1, sizeof( col ) );
		for( int i = 1; i <= n; i ++ )
			e[i].clear();
		for( int i = 1; i <= m; i ++ )
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			e[u].push_back( v );
			e[v].push_back( u );
		}
		// n != 1 in Bipartite
		col[1] = 1;
		if( n == 1 || !Color( 1 ) )
		{
			printf( "No\n" );
			continue ;
		}
		printf( "%d\n", Hungarian() / 2 );
	}
	return 0;
}
