#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 51, K = 201;

bool mark[K][N][2];
int n, m, T, M, t[N], d[K][N], tick;

int main()
{
	while( scanf( "%d", &n ) && n )
	{
		memset( d, 0x3f, sizeof( d ) );
		memset( mark, 0, sizeof( mark ) );
		scanf( "%d", &T );
		for( int i = 1; i < n; i ++ )
			scanf( "%d", &t[i] );
		scanf( "%d", &M );
		while( M -- )
		{
			scanf( "%d", &m );
			for( int i = 1; i < n && m <= T; i ++ )
				mark[m][i][0] = 1, m += t[i];
		}
		scanf( "%d", &M );
		while( M -- )
		{
			scanf( "%d", &m );
			for( int i = n; i > 1 && m <= T; i -- )
				mark[m][i][1] = 1, m += t[i-1];
		}
		d[0][1] = 0;
		for( int i = 0; i <= T; i ++ )
		{
			for( int j = 1; j <= n; j ++ )
			{
				if( i )
					d[i][j] = d[i-1][j] + 1;
				if( i - t[j-1] >= 0 && j > 1 && mark[i-t[j-1]][j-1][0] )
					d[i][j] = min( d[i-t[j-1]][j-1], d[i][j] );
				if( i - t[j] >= 0 && j < n && mark[i-t[j]][j+1][1] )
					d[i][j] = min( d[i-t[j]][j+1], d[i][j] );
			}
		}
		printf( "Case Number %d: ", ++ tick );
		if( d[T][n] >= 0x3f3f3f3f )
			printf( "impossible\n" );
		else
			printf( "%d\n", d[T][n] );
	}
	return 0;
}
