#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;

void ExGCD( data a, data b, data &x, data &y )
{
	if( b == 0 )
		x = 1, y = 0;
	else
	{
		ExGCD( b, a % b, y, x );
		y -= x * ( a / b );
	}
	return ;
}


int main()
{
	int t;
	scanf( "%d", &t );
	while( t -- )
	{
		data n, p, q, x1, x2, y;
		scanf( "%lld", &n );
		for( data i = 2; i * i <= n; i ++ )
		{
			if( n % i == 0 )
			{
				p = i, q = n / i;
				break ;
			}
		}
		printf( "0 1" );
		ExGCD( p, q, x1, y );
		ExGCD( q, p, x2, y );
		data a1 = ( ( p * x1 % n ) + n ) % n;
		data a2 = ( ( q * x2 % n ) + n ) % n;
		if( a1 > a2 )
			swap( a1, a2 );
		printf( " %lld %lld\n", a1, a2 );
	}
	return 0;
}
