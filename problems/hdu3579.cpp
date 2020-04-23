#include	<cmath>
#include	<cstdio>
#include	<iostream>

using	namespace	std;
typedef	long long	data;

int t, n;
data m[7], a[7];

void ExGCD( int a, int b, data &x, data &y, data &d )
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

int Solve()
{
	data x, y, c, d, k;
	data m1 = m[0], a1 = a[0], m2, a2;
	for( int i = 1; i < n; i ++ )
	{
		m2 = m[i], a2 = a[i];
		c = a2 - a1;
		ExGCD( m1, m2, x, y, d );
		if( c % d )
			return -1;
		data t = m2 / d;
		k = ( ( c / d * x ) % t + t ) % t;
		a1 += m1 * k;
		m1 *= t;
	}
	if( a1 == 0 )
		return m1;
	return a1;
}

int main()
{
	scanf( "%d", &t );
	for( int q = 1; q <= t; q ++ )
	{
		scanf( "%d", &n );
		for( int i = 0; i < n; i ++ )
			scanf( "%lld", &m[i] );
		for( int i = 0; i < n; i ++ )
			scanf( "%lld", &a[i] );
		printf( "Case %d: %d\n", q, Solve() );
	}
	return 0;
}
