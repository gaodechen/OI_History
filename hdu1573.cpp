#include	<cstdio>
#include	<iostream>

using	namespace	std;
typedef	long long	data;
const	int N = 11;

int t, n, m, a[N], b[N];

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
	data a1 = a[0], b1 = b[0], a2, b2;
	for( int i = 1; i < m; i ++ )
	{
		a2 = a[i], b2 = b[i];
		c = b2 - b1;
		ExGCD( a1, a2, x, y, d );
		if( c % d )
			return 0;
		data t = a2 / d;
		k = ( ( c / d ) * x % t + t ) % t;
		b1 += a1 * k;
		a1 *= t;
	}
	data ans = 0;
	data tmp = ( b1 % a1 + a1 - 1 ) % a1 + 1;
	while( tmp <= n )
		ans ++, tmp += a1;
	return ans;
	// WA: b1 = ( b1 % a1 + a1 - 1 ) % a1 + 1;
	// WA: return ( n - 1 ) / a1 - ( b1 == 1 );
}

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d%d", &n, &m );
		for( int i = 0; i < m; i ++ )
			scanf( "%d", &a[i] );
		for( int i = 0; i < m; i ++ )
			scanf( "%d", &b[i] );
		printf( "%d\n", Solve() );
	}
	return 0;
}
