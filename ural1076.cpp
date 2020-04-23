#include	<cstdio>
#include	<cstring>
#include	<iostream>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 151, INF = 0x7fffffff;

struct BPG
{
	int w[N][N], nX, nY;
	int visX[N], visY[N];
	int slack[N], link[N];
	int markX[N], markY[N];

	inline void Init( int x, int y )
	{
		nX = x, nY = y;
		set( link, -1 );
		set( markY, 0 );
		set( markX, 128 );
		return ;
	}

	bool Augment( int u )
	{
		visX[u] = 1;
		for( int v = 1; v <= nY; v ++ )
		{
			if( visY[v] )
				continue ;
			int t = markX[u] + markY[v] - w[u][v];
			if( t == 0 )
			{
				visY[v] = 1;
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
		for( int i = 1; i <= nX; i ++ )
			for( int j = 1; j <= nY; j ++ )
				if( w[i][j] > markX[i] )
					markX[i] = w[i][j];
		for( int u = 1; u <= nX; u ++ )
		{
			set( slack, 127 );
			while( true )
			{
				set( visX, 0 );
				set( visY, 0 );
				if( Augment( u ) )
					break ;
				int d = INF;
				for( int i = 1; i <= nY; i ++ )
					if( !visY[i] && d > slack[i] )
						d = slack[i];
				for( int i = 1; i <= nX; i ++ )
					if( visX[i] )
						markX[i] -= d;
				for( int i = 1; i <= nY; i ++ )
				{
					if( visY[i] )
						markY[i] += d;
					else
						slack[i] -= d;
				}
			}
		}
		int res = 0;
		for( int i = 1; i <= nY; i ++ )
			if( link[i] > 0 )
				res += w[link[i]][i];
		return res ;
	}
} g;

int n, m[N][N], sum[N];

int main()
{
	scanf( "%d", &n );
	g.Init( n, n );
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = 1; j <= n; j ++ )
		{
			scanf( "%d", &m[i][j] );
			sum[j] += m[i][j];
		}
	}
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= n; j ++ )
			g.w[i][j] = -( sum[j] - m[i][j] );
	printf( "%d\n", -g.KM() );
	return 0;
}

