#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 101, INF = 0x3f3f3f3f;

bool cut[N][N];
int t, n, G[N][N];

int main()
{
	scanf( "%d", &t );
	for( int c = 1; c <= t; c ++ )
	{
		memset( cut, 0, sizeof( cut ) );
		scanf( "%d", &n );
		int ans = n * ( n - 1 );
		for( int i = 0; i < n; i ++ )
			for( int j = 0; j < n; j ++ )
				scanf( "%d", &G[i][j] );
		bool flag = true;
		for( int k = 0; k < n; k ++ )
		{
			for( int i = 0; i < n; i ++ )
			{
				if( k == i )
					continue ;
				for( int j = 0; j < n; j ++ )
				{
					if( i == j || k == j )
						continue ;
					if( G[i][j] > G[i][k] + G[k][j] )
						flag = false;
					else if( !cut[i][j] && G[i][j] == G[i][k] + G[k][j] )
						cut[i][j] = 1, ans --;
				}
			}
		}
		printf( "Case %d: ", c );
		if( flag )
			printf( "%d\n", ans );
		else
			printf( "impossible\n" );
	}
	return 0;
}
