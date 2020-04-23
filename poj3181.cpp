#include	<cstdio>
#include	<iostream>

using	namespace	std;
typedef	long long	data;
const	data BASE = 1e3;
const	int  N = 1001, W = 16;

int n, m;
int d[N][20];

void Add( int i, int j )
{
	for( int k = 0; k < W; k ++ )
	{
		d[i][k] += d[j][k];
		d[i][k+1] += d[i][k] / BASE;
		d[i][k] %= BASE;
	}
	return ;
}

int main()
{
	scanf( "%d%d", &n, &m );
	d[0][0] = 1;
	for( int i = 1; i <= m; i ++ )
		for( int j = i; j <= n; j ++ )
			Add( j, j - i );
	int p = W;
	while( !d[n][p] )
		p --;
	printf( "%d", d[n][p] );
	for( int i = p - 1; i + 1; i -- )
		printf( "%03d", d[n][i] );
	printf( "\n" );
	return 0;
}
