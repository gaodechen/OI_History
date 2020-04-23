#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 1e3 + 5;

int n, d[N], f[N];

int main()
{
	scanf( "%d", &n );
	for( int k = 1; k <= n / 2; k ++ )
		for( int i = k + k; i <= n; i += k )
			f[i] += k;
	for( int i = 1; i <= n; i ++ )
		for( int j = n; j >= i; j -- )
			d[j] = max( d[j], d[j-i] + f[i] );
	printf( "%d\n", d[n] );
	return 0;
}
