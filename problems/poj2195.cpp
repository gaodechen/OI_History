#include	<cstdio>
#include	<cstring>
#include	<iostream>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 101, INF = 0x7fffffff;

inline int ABS( int x )
{
	return x > 0 ? x : -x;
}

struct BPG
{
	int nx, ny, w[N][N];
	bool visx[N], visy[N];
	int slack[N], link[N];
	int markx[N], marky[N];

	inline void Init( int n1, int n2 )
	{
		nx = n1, ny = n2;
		set( link, -1 );
		set( markx, 128 );
		set( marky, 0 );
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
		return -res;
	}

} g;

int n, m, k1, k2, man[N][2], house[N][2];

int main()
{
	while( scanf( "%d%d", &n, &m ) && n )
	{
		k1 = k2 = 0;
		for( int i = 1; i <= n; i ++ )
		{
			char buf[N];
			scanf( "%s", buf + 1 );
			for( int j = 1; j <= m; j ++ )
			{
				if( buf[j] == 'H' )
					house[++k1][0] = i, house[k1][1] = j;
				else if( buf[j] == 'm' )
					man[++k2][0] = i, man[k2][1] = j;
			}
		}
		g.Init( k1, k2 );
		for( int i = 1; i <= k1; i ++ )
			for( int j = 1; j <= k2; j ++ )
				g.w[i][j] = - ( ABS( house[i][0] - man[j][0] ) + ABS( house[i][1] - man[j][1] ) );
		printf( "%d\n", g.KM() );
	}
	return 0;
}
