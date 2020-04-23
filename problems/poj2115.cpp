#include	<cstdio>
#include	<iostream>

using	namespace	std;
typedef	long long	data;

void ExGCD( data a, data b, data &x, data &y, data &d )
{
	if( b == 0 )
		x = 1, y = 0, d = a;
	else
	{
		ExGCD( b, a % b, y, x, d );
		y -= x * ( a / b );
	}
	return ;
}

int main()
{
	data a, b, c, k;
	while( scanf( "%lld%lld%lld%lld", &a, &b, &c, &k ) && a + b + c + k )
	{
		data t = b - a;
		data x, y, d, n = ( 1LL << k );
		ExGCD( c, n, x, y, d );
		if( t % d )
			printf( "FOREVER\n" );
		else
		{
			x = x * ( t / d ) % n;
			t = n / d, x = ( x % t + t ) % t;
			printf( "%lld\n", x );
		}
	}
	return 0;
}
