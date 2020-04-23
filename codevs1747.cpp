#include	<cmath>
#include	<cstdio>
#include	<iostream>
using	namespace	std;
const	int N = 20;

int n, t, c[N], p[N], l[N];

void ExGCD( int a, int b, int &d, int &x, int &y )
{
	if( b == 0 )
		d = a, x = 1, y = 0;
	else
	{
		ExGCD( b, a % b, d, y, x );
		y -= x * ( a / b );
	}
	return ;
}

int Solve( int a, int b, int c )
{
	int d, x, y, t;
	ExGCD( a, b, d, x, y );
	if( c % d )
		return -1;
	x *= c / d;
	t = abs( b / d );
	x = ( x % t + t ) % t;
	return x;
}

bool Check( int m )
{
	for( int i = 0; i < n; i ++ )
	{
		for( int j = i + 1; j < n; j ++ )
		{
			int x = Solve( p[i] - p[j], m, c[j] - c[i] );
			if( x != -1 && x <= min( l[i], l[j] ) )
				return 0;
		}
	}
	return 1;
}

int main()
{
	scanf( "%d", &n );
	for( int i = 0; i < n; i ++ )
	{
		scanf( "%d%d%d", &c[i], &p[i], &l[i] );
		t = max( t, c[i] );
	}
	for( int i = t; i; i ++ )
	{
		if( Check( i ) )
		{
			printf( "%d\n", i );
			break ;
		}
	}
	return 0;
}
