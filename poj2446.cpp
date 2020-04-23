#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<vector>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 1500;

struct BPG
{
	bool vis[N];
	int n, link[N];
	vector< int > e[N];

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

int n, m, k;
int G[N][N];
int next[][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

inline bool CheckPos( int x, int y )
{
	return x >= 1 && y >= 1 && x <= n && y <= m;
}

int main()
{
	int sig1 = 0, sig2 = 0;
	scanf( "%d%d%d", &n, &m, &k );
	for( int i = 0; i < k; i ++ )
	{
		int x, y;
		scanf( "%d%d", &y, &x );
		G[x][y] = -1;
	}
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = 1; j <= m; j ++ )
		{
			if( G[i][j] != -1 )
			{
				if( ( i + j ) & 1 )
					G[i][j] = ++ sig1;
				else
					G[i][j] = ++ sig2;
			}
		}
	}
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = 1; j <= m; j ++ )
		{
			if( ( i + j ) & 1 && G[i][j] != -1 )
			{
				for( int d = 0; d < 4; d ++ )
				{
					int i_ = i + next[d][0];
					int j_ = j + next[d][1];
					if( CheckPos( i_, j_ ) && G[i_][j_] != -1 )
						g.AddEdge( G[i][j], G[i_][j_] );
				}
			}
		}
	}
	if( k & 1 || sig1 != sig2 )
		printf( "NO\n" );
	else
	{
		g.n = sig1;
		int q = g.Hungarian();
		if( q + q == sig1 + sig2 )
			printf( "YES\n" );
		else
			printf( "NO\n" );
	}
	return 0;
}
