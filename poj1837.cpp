#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 21, M = 8000, K = 7501;

int n, m, sum, p[N], w[N], d[N][M*2];

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &p[i] );
	for( int j =  1; j <= m; j ++ )
		scanf( "%d", &w[j] );
	d[0][K] = 1;
	for( int i = 1; i <= m; i ++ )
		for( int j = 0; j < K * 2; j ++ )
			if( d[i-1][j] )
				for( int k = 1; k <= n; k ++ )
					d[i][j+p[k]*w[i]] += d[i-1][j];
	printf( "%d", d[m][K] );
	return 0;
}
