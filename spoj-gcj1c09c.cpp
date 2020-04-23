#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 1e4 + 5, INF = 0x3f3f3f3f;

int t, p, q, x, a[N], d[N][N];

int main(int argc, char **argv)
{
	scanf( "%d", &t );
	for( int c = 1; c <= t; c ++ )
	{
		memset( d, 0, sizeof( d ) );
		scanf( "%d%d", &p, &q );
		a[q + 1] = p + 1;
		for( int i = 1; i <= q; i ++ )
			scanf( "%d", &a[i] );
		for( int len = 2; len <= q + 1; len ++ )
		{
			for( int i = 0; i + len <= q + 1; i ++ )
			{
				int j = i + len, t = INF;
				for( int k = i + 1; k < j; k ++ )
					t = min( t, d[i][k] + d[k][j] );
				d[i][j] = t + a[j] - a[i] - 2;
			}
		}
		printf( "Case #%d: %d\n", c, d[0][q+1] );
	}
	return 0;
}
