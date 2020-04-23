#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

using	namespace	std;
typedef	const int &	var;
const	int	N = 10;

struct Point
{
	int x, y, w;

	Point( int x = 0, int y = 0, int w = 0 ): x( x ), y( y ), w( w )
	{
	}

	bool operator < ( const Point &b ) const
	{
		return w < b.w;
	}
};

bool vis[N][N];
int n = 9, ans, row[N], col[N], sud[N];
int g[N][N], ind[N][N], w[N][N], state[N][N];
priority_queue< Point > q;

int val[N][N] =
{
	{ 0, 0, 0, 0,  0, 0, 0, 0, 0, 0 },
	{ 0, 6, 6, 6, 6,  6, 6, 6, 6, 6 },
	{ 0, 6, 7, 7, 7,  7, 7, 7, 7, 6 },
	{ 0, 6, 7, 8, 8,  8, 8, 8, 7, 6 },
	{ 0, 6, 7, 8, 9,  9, 9, 8, 7, 6 },
	{ 0, 6, 7, 8, 9, 10, 9, 8, 7, 6 },
	{ 0, 6, 7, 8, 9,  9, 9, 8, 7, 6 },
	{ 0, 6, 7, 8, 8,  8, 8, 8, 7, 6 },
	{ 0, 6, 7, 7, 7,  7, 7, 7, 7, 6 },
	{ 0, 6, 6, 6, 6,  6, 6, 6, 6, 6 },
} ;

inline int GetMask( var x, var y )
{
	return row[x] | col[y] | sud[ind[x][y]];
}

inline int GetNum( var x, var y )
{
	int sum = 0, t = GetMask( x, y );
	while( t )
		sum ++, t &= ( t - 1 );
	return sum;
}

inline int GetIndex( var x, var y )
{
	int i = ( x - 1 ) / 3;
	int j = ( y - 1 ) / 3;
	return i + i + i + j + 1;
}

inline Point GetPos()
{
	Point t;
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= n; j ++ )
			if( w[i][j] > t.w && w[i][j] > -1 )
				t = Point( i, j, w[i][j] );
	return t;
}

void Search( int x, int y, int sum, int lim )
{
	int mask = GetMask( x, y );
	if( lim == 0 )
	{
		int t = mask >> 1, i = 1;
		while( t & 1 )
			i ++, t >>= 1;
		int tmp = sum + i * val[x][y];
		ans = max( ans, tmp );
		return ;
	}
	for( int i = 1; i <= n; i ++ )
	{
		int t = ( 1 << i );
		if( mask & t )
			continue ;
		int h[N][N];
		Point p = GetPos();
		int a = sud[ind[x][y]], b = row[x], c = col[y], d = w[p.x][p.y];
		sud[ind[x][y]] |= t, row[x] |= t, col[y] |= t, w[p.x][p.y] = -1;
		memcpy( h, w, sizeof( w ) );
		for( int j = 1; j <= n; j ++ )
			for( int k = 1; k <= n; k ++ )
				if( w[j][k] != -1 )
					w[j][k] = GetNum( j, k );

		Search( p.x, p.y, sum + val[x][y] * i, lim - 1 );

		memcpy( w, h, sizeof( h ) );
		sud[ind[x][y]] = a, row[x] = b, col[y] = c, w[p.x][p.y] = d;
	}
	return ;
}

int main()
{
	memset( w, -1, sizeof( w ) );
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= n; j ++ )
			scanf( "%d", &g[i][j] );
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= n; j ++ )
			ind[i][j] = GetIndex( i, j );
	int sum = 0, ept = 0;
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = 1; j <= n; j ++ )
		{
			if( g[i][j] )
			{
				int t = ( 1 << g[i][j] );
				sum += val[i][j] * g[i][j];
				row[i] += t, col[j] += t;
				sud[ind[i][j]] += t;
			}
		}
	}
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= n; j ++ )
			if( g[i][j] == 0 )
				w[i][j] = GetNum( i, j ), ept ++;
	Point s = GetPos();
	w[s.x][s.y] = -1;
	Search( s.x, s.y, sum, ept );
	printf( "%d\n", ans == 0 ? -1 : ans );
	return 0;
}
