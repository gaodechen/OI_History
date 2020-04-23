#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int INF = 0x3f3f3f3f;
const	int N = 1e4 + 5, MOD = 133;

int c[N], d[200][200], n, m;

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &c[i] );
	memset( d, INF, sizeof( INF ) );
	for( int i = 1; i <= m; i ++ )
		for( int j = 1; j < i; j ++ )
			d[i][j] = c[i] + c[j];
	for( int i = 2; i <= n; i ++ )
	{
		int tmp = INF;
		for( int j = i + m - 1; j > i; j -- )
		{
			if( j <= m )
				break ;
			tmp = min( tmp, d[i%MOD][(j-m)%MOD] );
			d[j%MOD][i%MOD] = tmp + c[j];
		}
	}
	int ans = INF;
	for( int i = n - m + 1; i <= n; i ++ )
		for( int j = i - 1; i - j < m && n - j < m; j -- )
			ans = min( ans, d[i%MOD][j%MOD] );
	printf( "%d\n", ans );
	return 0;
}
