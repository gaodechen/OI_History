#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
typedef	long long	data;
const	data M = 1e9 + 7;

data f[16][16][16][16][16][5];

data F( int a, int b, int c, int d, int e, int cur )
{
	if( ( a | b | c | d | e ) == 0 )
		return 1;
	data &q = f[a][b][c][d][e][cur];
	if( q )
		return q;
	data k = 0;
	if( a ) k += F( a - 1, b, c, d, e, 1 ) * ( a - ( cur == 2 ) );
	if( b ) k += F( a + 1, b - 1, c, d, e, 2 ) * ( b - ( cur == 3 ) );
	if( c ) k += F( a, b + 1, c - 1, d, e, 3 ) * ( c - ( cur == 4 ) );
	if( d ) k += F( a, b, c + 1, d - 1, e, 4 ) * ( d - ( cur == 5 ) );
	if( e ) k += F( a, b, c, d + 1, e - 1, 5 ) * e;
	q = k % M;
	return q;
}

int main()
{
	int n, sum[6] = { 0 };
	scanf( "%d", &n );
	for( int i = 0, x; i < n; i ++ )
	{
		scanf( "%d", &x );
		sum[x] ++;
	}
	int ans = F( sum[1], sum[2], sum[3], sum[4], sum[5], 0 );
	printf( "%d\n", ans );
	return 0;
}
