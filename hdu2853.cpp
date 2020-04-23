#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 100, INF = 0x3f3f3f3f;

bool visx[N], visy[N];
int slack[N], link[N];
int markx[N], marky[N];
int w[N][N], nx, ny, n, m;

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
			if( w[i][j] > markx[i] )
				markx[i] = w[i][j];
	for( int u = 1; u <= nx; u ++ )
	{
		set( slack, 127 );
		while( true )
		{
			set( visx, 0 ), set( visy, 0 );
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
		res += w[link[i]][i];
	return res;
}

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		int Q = 100, sum = 0;
		nx = n, ny = m, set( link, -1 );
		set( markx, 128 ), set( marky, 0 );
		for( int i = 1; i <= n; i ++ )
			for( int j = 1; j <= m; j ++ )
				scanf( "%d", &w[i][j] );
		for( int i = 1; i <= n; i ++ )
			for( int j = 1; j <= m; j ++ )
				w[i][j] *= Q;
		for( int i = 1, j; i <= n; i ++ )
		{
			scanf( "%d", &j );
			sum += w[i][j];
			w[i][j] ++;
		}
		int k = KM();
		printf( "%d %d\n", n - k % Q, k / Q - sum / Q );
	}
	return 0;
}
