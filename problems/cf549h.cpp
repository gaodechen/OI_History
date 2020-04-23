#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<cmath>

using	namespace	std;

inline double GetMax( double x, double y, double d )
{
	double r = ( x - d ) * ( y + d );
	r = max( ( x - d ) * ( y - d ), r );
	r = max( ( x + d ) * ( y - d ), r );
	r = max( ( x + d ) * ( y + d ), r );
	return r;
}

inline double GetMin( double x, double y, double d )
{
	double r = ( x - d ) * ( y + d );
	r = min( ( x - d ) * ( y - d ), r );
	r = min( ( x + d ) * ( y - d ), r );
	r = min( ( x + d ) * ( y + d ), r );
	return r;
}

int a, b, c, d;

inline bool Check( double x )
{
	double l1 = GetMin( a, d, x );
	double r1 = GetMax( a, d, x );
	double l2 = GetMin( b, c, x );
	double r2 = GetMax( b, c, x );
	if( l1 <= r2 && r1 >= l2 )
		return true;
	return false;
}

int main()
{
	cin >> a >> b >> c >> d;
	double l = 0;
	double r = max( max( abs( a ), abs( b ) ), max( abs( c ), abs( d ) ) );
	int time = 1000;
	while( time -- )
	{
		double mid = ( l + r ) / 2;
		if( Check( mid ) )
			r = mid;
		else
			l = mid;
	}
	printf( "%.10lf\n", l );
	return 0;
}
