#include	<cstdio>
#include	<iostream>

using	namespace	std;
typedef	unsigned long long data;
const	int N = 1e2, M = 9901;

data ans = 1, a, b;
int tot, d[N], p[N];

data mul( data a, data b, data m )
{
	a %= m;
	data res = 0;
	while( b )
	{
		if( b & 1 )
			res = ( res + a ) % m;
		b >>= 1;
		a = ( a + a ) % m;
	}
	return res;
}

data pow( data k, data p, data m )
{
	k %= m;
	data res = 1;
	while( p )
	{
		if( p & 1 )
			res = mul( res, k, m );
		k = mul( k, k, m );
		p >>= 1;
	}
	return res;
}

int main()
{
	cin >> a >> b;
	if( a == 0 )
		printf( "0\n" );
	else if( b == 0 )
		printf( "1\n" );
	else
	{
		for( int i = 2; i * i <= a; i ++ )
		{
			if( a % i == 0 )
			{
				d[tot] = i;
				while( a % i == 0 )
					p[tot] ++, a /= i;
				tot ++;
			}
		}
		if( a > 1 )
			d[tot] = a, p[tot] ++, tot ++;
		for( int i = 0; i < tot; i ++ )
			p[i] *= b;
		for( int i = 0; i < tot; i ++ )
		{
			data c = M * ( data )( d[i] - 1 );
			ans *= ( pow( d[i], p[i] + 1, c ) + c - 1 ) / ( d[i] - 1 );
			ans %= M;
		}
		cout << ans << endl;
	}
	return 0;
}
