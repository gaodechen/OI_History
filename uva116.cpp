#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 11, M = 101;

int n, m, a[N][M], d[N][M], next[N][M], ans, pos;

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		memset( d, 0x3f, sizeof( d ) );
		for( int i = 1; i <= n; i ++ )
			for( int j = 1; j <= m; j ++ )
				scanf( "%d", &a[i][j] );
		for( int i = 1; i <= n; i ++ )
			d[i][m] = a[i][m];
		for( int j = m - 1; j; j -- )
		{
			for( int i = 1; i <= n; i ++ )
			{
				int r[] = { i - 1, i, i + 1 };
				if( i == n ) r[2] = 1;
				if( i == 1 ) r[0] = n;
				sort( r, r + 3 );
				for( int k = 0; k < 3; k ++ )
				{
					int t = d[r[k]][j+1] + a[i][j];
					if( t < d[i][j] )
						d[i][j] = t, next[i][j] = r[k];
				}
			}
		}
		ans = 0x3f3f3f3f, pos = -1;
		for( int i = 1; i <= n; i ++ )
			if( d[i][1] < ans )
				ans = d[i][1], pos = i;
		int j = 1;
		printf( "%d", pos );
		while( j < m )
		{
			pos = next[pos][j++];
			printf( " %d", pos );
		}
		printf( "\n%d\n", ans );
	}
	return 0;
}
