#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 11, INF = 0x3f3f3f3f;

int n, m, a[N][N], k[N], tmp[N], ans = INF;

void DFS( int x )
{
	if( tmp[1] * m >= ans )
		return ;
	if( x > n )
	{
		if( tmp[1] == 0 )
			return ;
		for( int i = 2; i <= m; i ++ )
			if( tmp[i] != tmp[1] )
				return ;
		if( tmp[1] * m <= 1000 )
			ans = min( ans, tmp[1] * m );
		return ;
	}
	for( int i = 0; i <= k[x]; i ++ )
	{
		for( int j = 1; j <= m; j ++ )
			tmp[j] += i * a[x][j];
		DFS( x + 1 );
		for( int j = 1; j <= m; j ++ )
			tmp[j] -= i * a[x][j];
	}
	return ;
}

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= m; j ++ )
			scanf( "%d", &a[i][j] );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &k[i] );
	DFS( 1 );
	if( ans >= INF )
		printf( "alternative!\n" );
	else
		printf( "%d\n", ans );
	return 0;
}
