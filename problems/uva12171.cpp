#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

using	namespace	std;
const	int M = 1001, N = 55, K = 110;

int t, n;
int x0[N], y0[N], z0[N];
int x1[N], y1[N], z1[N];
int x[K], y[K], z[K], a, b, c;
int color[K][K][K], v, s;

int nextX[] = { 1, -1, 0, 0, 0, 0 };
int nextY[] = { 0, 0, 1, -1, 0, 0 };
int nextZ[] = { 0, 0, 0, 0, 1, -1 };

struct Unit
{
	int x_, y_, z_;
	Unit( int x_ = 0, int y_ = 0, int z_ = 0 ): x_( x_ ), y_( y_ ), z_( z_ )
	{
	}
	bool CheckPos()
	{
		return x_ >= 0 && x_ < a - 1 && y_ >= 0 && y_ < b - 1 && z_ >= 0 && z_ < c - 1;
	}
	bool isSolid()
	{
		return color[x_][y_][z_] == 1;
	}
	Unit GetNext( int d )
	{
		return Unit( x_ + nextX[d], y_ + nextY[d], z_ + nextZ[d] );
	}
	int GetVolume()
	{
		return ( x[x_+1] - x[x_] ) * ( y[y_+1] - y[y_] ) * ( z[z_+1] - z[z_] );
	}
	int GetArea( int d )
	{
		if( nextX[d] != 0 )
			return ( y[y_+1] - y_[y] ) * ( z[z_+1] - z[z_] );
		if( nextY[d] != 0 )
			return ( x[x_+1] - x[x_] ) * ( z[z_+1] - z[z_] );
		return ( x[x_+1] - x[x_] ) * ( y[y_+1] - y_[y] );
	}
	void MarkVis()
	{
		color[x_][y_][z_] = 2;
		return ;
	}
	bool CheckMark()
	{
		return color[x_][y_][z_] == 2;
	}
};

void Discretize( int *arr, int &len )
{
	sort( arr, arr + len );
	len = unique( arr, arr + len ) - arr;
	return ;
}

int GetIndex( int *arr, int len, int key )
{
	return lower_bound( arr, arr + len, key ) - arr;
}

void FloodFill()
{
	v = s = 0;
	queue< Unit > q;
	Unit tmp = Unit();
	tmp.MarkVis();
	q.push( tmp );
	while( !q.empty() )
	{
		Unit u = q.front(); q.pop();
		v += u.GetVolume();
		for( int i = 0; i < 6; i ++ )
		{
			Unit p = u.GetNext( i );
			if( !p.CheckPos() )
				continue ;
			if( p.isSolid() )
				s += p.GetArea( i );
			else if( !p.CheckMark() )
			{
				p.MarkVis();
				q.push( p );
			}
		}
	}
	v = M * M * M - v;
	return ;
}

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		a = b = c = 0;
		memset( color, 0, sizeof( color ) );
		scanf( "%d", &n );
		x[a++] = y[b++] = z[c++] = 0;
		x[a++] = y[b++] = z[c++] = M;
		for( int i = 0; i < n; i ++ )
		{
			scanf( "%d%d%d", &x0[i], &y0[i], &z0[i] );
			scanf( "%d%d%d", &x1[i], &y1[i], &z1[i] );
			x1[i] += x0[i], y1[i] += y0[i], z1[i] += z0[i];
			x[a++] = x0[i], x[a++] = x1[i];
			y[b++] = y0[i], y[b++] = y1[i];
			z[c++] = z0[i], z[c++] = z1[i];
		}
		Discretize( x, a );
		Discretize( y, b );
		Discretize( z, c );
		for( int i = 0; i < n; i ++ )
		{
			int X1 = GetIndex( x, a, x0[i] );
			int X2 = GetIndex( x, a, x1[i] );
			int Y1 = GetIndex( y, b, y0[i] );
			int Y2 = GetIndex( y, b, y1[i] );
			int Z1 = GetIndex( z, c, z0[i] );
			int Z2 = GetIndex( z, c, z1[i] );
			for( int X = X1; X < X2; X ++ )
				for( int Y = Y1; Y < Y2; Y ++ )
					for( int Z = Z1; Z < Z2; Z ++ )
						color[X][Y][Z] = 1;
		}
		FloodFill();
		printf( "%d %d\n", s, v );
	}
	return 0;
}
