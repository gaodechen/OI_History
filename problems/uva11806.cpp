#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 500, M = 1000007;

int t, n, m, k, ans, C[N][N];

void InitTable()
{
	C[0][0] = 1;
	for( int i = 1; i <= N - 50; i ++ )
	{
		C[i][0] = 1;
		for( int j = 1; j <= i; j ++ )
			C[i][j] = ( C[i-1][j-1] + C[i-1][j] ) % M;
	}
	return ;
}

void IEP( int x, int t, int r, int c )
{
	if( x == 0 )
	{
		if( t & 1 )
			ans -= C[r*c][k];
		else
			ans += C[r*c][k];
	}
	else if( x > 2 )
	{
		IEP( x - 1, t + 1, r - 1, c );
		IEP( x - 1, t, r, c );
	}
	else
	{
		IEP( x - 1, t + 1, r, c - 1 );
		IEP( x - 1, t, r, c );
	}
	return ;
}

int main()
{
	freopen( "in", "r", stdin );
	InitTable();
	scanf( "%d", &t );
	for( int i = 1; i <= t; i ++ )
	{
		ans = 0;
		scanf( "%d%d%d", &n, &m, &k );
		IEP( 4, 0, n, m );
		ans = ( ans % M + M ) % M;
		printf( "Case %d: %d\n", i, ans );
	}
	return 0;
}
