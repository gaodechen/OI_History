#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int MOD = 1e8, L = 50;
const	int N =  600, K = 550;

int k, w, d[N][K][L], ans[L];

inline void Add( int *a, int *b, int *c )
{
	int &g = c[0];
	g = max( a[0], b[0] );
	for( int i = 1; i <= g; i ++ )
		c[i] = a[i] + b[i];
	for( int i = 1; i <= g; i ++ )
	{
		if( c[i] >= MOD )
		{
			c[i+1] += c[i] / MOD;
			c[i] %= MOD;
		}
	}
	if( c[g+1] )
		g ++;
	return ;
}

int main()
{
	scanf( "%d%d", &k, &w );
	int q = ( 1 << k ) - 1;
	int p = ( w + k - 1 ) / k;
	int h = ( 1 << ( w % k ) ) - 1;
	d[0][0][1] = 1, d[0][0][0] = 1;
	for( int i = 1; i <= q; i ++ )
		d[1][i][1] = d[1][i][0] = 1;
	for( int len = 2; len <= p; len ++ )
		for( int i = q; i >= 1; i -- )
			Add( d[len][i+1], d[len-1][i+1], d[len][i] );
	ans[0] = 1;
	if( h == 0 )
		h = q;
	for( int len = 2; len <= p; len ++ )
	{
		int tmp = len == p ? h : q;
		for( int i = 1; i <= tmp; i ++ )
			Add( ans, d[len][i], ans );
	}
	printf( "%d", ans[ans[0]] );
	for( int i = ans[0] - 1; i; i -- )
		printf( "%08d", ans[i] );
	printf( "\n" );
	return 0;
}
