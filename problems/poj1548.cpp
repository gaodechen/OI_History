#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<vector>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 625;

struct BPG
{
	bool vis[N];
	int n, link[N];
	vector< int > e[N];

	inline void Init( int n_ )
	{
		n = n_;
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

struct Point
{
	int x, y;
} e[N];

int main()
{
	while( 1 )
	{
		int flag = 1, t = 0;
		while( scanf( "%d%d", &e[t].x, &e[t].y ) == 2 )
		{
			if( e[t].x == -1 )
			{
				flag = 0;
				break ;
			}
			if( e[t].x == 0 )
				break ;
			t ++;
		}
		if( !flag )
			break ;
		g.Init( t );
		for( int i = 0; i < t; i ++ )
			for( int j = i + 1; j < t; j ++ )
				if( e[i].x <= e[j].x && e[i].y <= e[j].y )
					g.AddEdge( i + 1, j + 1 );
		printf( "%d\n", t - g.Hungarian() );
	}
	return 0;
}
