#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<cmath>

using	namespace	std;
typedef long long	data;

void ExGCD( data a, data b, data &d, data &x, data &y )
{
	if( b == 0 )
		x = 1, y = 0, d = a;
	else
	{
		ExGCD( b, a % b, d, y, x );
		y -= x * ( a / b );
	}
	return ;
}

int main()
{
	freopen( "in", "r", stdin );
	data n, a, b, d, x0, y0;
	scanf( "%lld%lld%lld", &a, &b, &n );
	ExGCD( a, b, d, x0, y0 );
	data k1 = ceil( x0 * d / b ), k2 = floor( y0 * d / a );
	data x1 = x0 + b * k1 / d, x2 = x0 + b * k2 / d;
	data y1 = y0 - a * k1 / d, y2 = y0 - a * k2 / d;
	if( x1 * a + y1 * b > x2 * a + y2 * b )
		printf( "%lld %lld\n", x1, y1 );
	else
		printf( "%lld %lld\n", x2, y2 );
	return 0;
}
