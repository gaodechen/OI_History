#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<cmath>

using	namespace	std;
const	int N = 110;
const	double g = 10.0;

double e[N];
int n, r, h, T, C;

inline double Compute( int x )
{
	if( x < 0 )
		return h;
	double d, t = sqrt( ( h + h ) / g );
	int k = x / t;
	if( k & 1 )
		d = k * t + t - x;
	else
		d = x - k * t;
	return h - 0.5 * g * d * d;
}

int main()
{
	scanf( "%d", &C );
	while( C -- )
	{
		cin >> n >> h >> r >> T;
		for( int i = 0; i < n; i ++ )
			e[i] = Compute( T - i );
		sort( e, e + n );
		for( int i = 0; i < n; i ++ )
			printf( "%.2f ", e[i] + 2 * r * i / 100.0 );
		printf( "\n" );
	}
	return 0;
}
