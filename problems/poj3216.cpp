#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<vector>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 300, INF = 0x3f3f3f3f;

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

	inline void AddEdge( int u, int v )
	{
		e[u].push_back( v );
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

int n, m, G[21][21], p[N], s[N], e[N];

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 && n )
	{
		for( int i = 1; i <= n; i ++ )
		{
			for( int j = 1; j <= n; j ++ )
			{
				scanf( "%d", &G[i][j] );
				if( G[i][j] == -1 )
					G[i][j] = INF;
			}
		}
		for( int i = 1; i <= m; i ++ )
		{
			int a, b, c;
			scanf( "%d%d%d", &a, &b, &c );
			p[i] = a, s[i] = b, e[i] = b + c;
		}
		g.Init( m );
		for( int k = 1; k <= n; k ++ )
			for( int i = 1; i <= n; i ++ )
				for( int j = 1; j <= n; j ++ )
					G[i][j] = min( G[i][j], G[k][i] + G[k][j] );
		for( int i = 1; i <= m; i ++ )
			for( int j = 1; j <= m; j ++ )
				if( e[i] + G[p[i]][p[j]] <= s[j] )
					g.AddEdge( i, j );
		printf( "%d\n", m - g.Hungarian() );
	}
	return 0;
}
