#include	<cstdio>
#include	<iostream>

using	namespace	std;
typedef	long long	data;

int next( data n, int k )
{
	n *= n;
	int buf[100], len = 0;
	while( n )
	{
		buf[len++] = n % 10;
		n /= 10;
	}
	int res = 0;
	for( int i = len - 1; i >= max( len - k, 0 ); i -- )
		res = res * 10 + buf[i];
	return res;
}

int main()
{
	int t, n, k;
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d%d", &k, &n );
		int ans = n, k1 = n, k2 = n;
		do
		{
			k1 = next( k1, k );
			k2 = next( k2, k );
			if( k2 > ans )
				ans = k2;
			k2 = next( k2, k );
			if( k2 > ans )
				ans = k2;
		} while( k1 != k2 );
		printf( "%d\n", ans );
	}
	return 0;
}
