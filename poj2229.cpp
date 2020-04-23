#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e6 + 5, M = 1e9;

int n, d[N];

int main()
{
	d[1] = 1;
	scanf( "%d", &n );
	for( int i = 2; i <= n; i ++ )
	{
		if( i & 1 )
			d[i] = d[i-1] % M;
		else
		{
			d[i] = d[i-1] % M + d[i>>1] % M;
			d[i] %= M;
		}
	}
	printf( "%d\n", d[n] );
	return 0;
}
