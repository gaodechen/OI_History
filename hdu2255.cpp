#include	<cstdio>
#include	<cstring>
#include	<iostream>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 301, INF = 0x7fffffff;

struct BPG
{
	int w[N][N], nx, ny;
	bool visx[N], visy[N];
	int slack[N], link[N];
	int markx[N], marky[N];

	inline void Init( int x, int y )
	{
		nx = x, ny = y;
		set( link, -1 );
		set( marky, 0 );
		set( markx, 128 );
	}

	bool Augment( int u )
	{
		visx[u] = 1;
		for( int v = 1; v <= ny; v ++ )
		{
			if( visy[v] )
				continue ;
			int t = markx[u] + marky[v] - w[u][v];
			if( t == 0 )
			{
				visy[v] = 1;
				if( link[v] == -1 || Augment( link[v] ) )
				{
					link[v] = u;
					return true;
				}
			}
			else if( slack[v] > t )
				slack[v] = t;
		}
		return false;
	}

	int KM()
	{
		for( int i = 1; i <= nx; i ++ )
			for( int j = 1; j <= ny; j ++ )
				if( markx[i] < w[i][j] )
					markx[i] = w[i][j];
		for( int u = 1; u <= nx; u ++ )
		{
			set( slack, 127 );
			while( true )
			{
				set( visx, 0 );
				set( visy, 0 );
				if( Augment( u ) )
					break ;
				int d = INF;
				for( int i = 1; i <= ny; i ++ )
					if( !visy[i] && d > slack[i] )
						d = slack[i];
				for( int i = 1; i <= nx; i ++ )
					if( visx[i] )
						markx[i] -= d;
				for( int i = 1; i <= ny; i ++ )
				{
					if( visy[i] )
						marky[i] += d;
					else
						slack[i] -= d;
				}
			}
		}
		int res = 0;
		for( int i = 1; i <= ny; i ++ )
			if( link[i] > -1 )
				res += w[link[i]][i];
		return res;
	}
} g;


int main()
{
	int n;
	while( scanf( "%d", &n ) == 1 )
	{
		g.Init( n, n );
		for( int i = 1; i <= n; i ++ )
			for( int j = 1; j <= n; j ++ )
				scanf( "%d", &g.w[i][j] );
		printf( "%d\n", g.KM() );
	}
	return 0;
}
