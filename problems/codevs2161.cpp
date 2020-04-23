#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 10001;

int n, m, w[N], d[N][501];

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &w[i] );
	for( int i = 1; i <= n; i ++ )
	{
		d[i][0] = max( d[i][0], d[i-1][0] );
		for( int j = 1; j <= min( i, m ); j ++ )
		{
			d[i][j] = d[i-1][j-1] + w[i];
			if( i + j <= n )
				d[i+j][0] = max( d[i+j][0], d[i][j] );
		}
	}
	printf( "%d\n", d[n][0] );
	return 0;
}
