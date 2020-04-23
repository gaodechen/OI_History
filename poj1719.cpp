#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<vector>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 2000;

struct BPG
{
	bool vis[N];
	int n, link[N];
	vector< int > e[N];

	inline void Init( int k )
	{
		n = k;
		for( int i = 1; i <= n; i ++ )
			e[i].clear();
		return ;
	}

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
		set( link, -1 );
		for( int i = 1; i <= n; i ++ )
		{
			set( vis, 0 );
			if( Augment( i ) )
				sum ++;
		}
		return sum;
	}
} g;

int main()
{
	bool G[N][N];
	int t, n, m, a, b;
	scanf( "%d", &t );
	while( t -- )
	{
		set( G, 0 );
		scanf( "%d%d", &n, &m );
		g.Init( n );
		for( int j = 1; j <= m; j ++ )
		{
			scanf( "%d%d", &a, &b );
			g.e[a].push_back( j );
			g.e[b].push_back( j );
			G[a][j] = G[b][j] = 1;
		}
		if( n > m )
		{
			printf( "NO\n" );
			continue ;
		}
		if( g.Hungarian() != n )
		{
			printf( "NO\n" );
			continue ;
		}
		for( int j = 1; j <= m; j ++ )
		{
			if( g.link[j] != -1 )
				printf( "%d ", g.link[j] );
			else for( int i = 1; i <= n; i ++ ) if( G[i][j] )
			{
				printf( "%d ", i );
				break ;
			}
		}
		printf( "\n" );
	}
	return 0;
}
