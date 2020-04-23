#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;

int main()
{
	int N = 20;
	bool w[N][N];
	memset( w, 0, sizeof( w ) );
	for( int k = 3; k < N; k ++ )
	{
		for( int n = 1; n < N; n ++ )
		{
			int m = k - n, t = max( n, m );
			for( int i = 1; i < t; i ++ )
				if( !w[i][n-i] )
					w[n][m] = 1;
			if( n <= m && !w[n][m] )
				printf( "%d %d\n", n, m );
		}
	}
	int n;
	while( scanf( "%d", &n ) && n )
	{
	}
	return 0;
}
