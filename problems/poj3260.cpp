#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int INF = 0x3f3f3f3f;
const	int N = 1e2 + 1, M = 125 * 125;

int n, s, sum;
int d1[M+M], d2[M], val[N], num[N];

void BinaryPack( int *d, int val, int k )
{
	for( int j = sum; j >= val; j -- )
		d[j] = min( d[j], d[j-val] + k );
	return ;
}

void InfinitePack( int *d, int val )
{
	for( int j = val; j <= sum; j ++ )
		d[j] = min( d[j], d[j-val] + 1 );
	return ;
}

int main()
{
	memset( d1, 0x3f, sizeof( d1 ) );
	memset( d2, 0x3f, sizeof( d2 ) );
	d1[0] = d2[0] = 0;
	scanf( "%d%d", &n, &s );
	for( int i = 1; i <= n; i ++ )
	{
		scanf( "%d", &val[i] );
		sum = max( val[i], sum );
	}
	sum *= sum;
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &num[i] );
	for( int i = 1; i <= n; i ++ )
	{
		InfinitePack( d2, val[i] );
		if( num[i] * val[i] >= s )
			InfinitePack( d1, val[i] );
		else
		{
			int k = 1;
			while( num[i] > k )
			{
				BinaryPack( d1, val[i] * k, k );
				num[i] -= k;
				k <<= 1;
			}
			BinaryPack( d1, val[i] * num[i], num[i] );
		}
	}
	int ans = INF;
	for( int i = s; i <= sum; i ++ )
		if( d1[i] != INF && d2[i-s] != INF )
			ans = min( ans, d1[i] + d2[i-s] );
	printf( "%d\n", ans == INF ? -1 : ans );
	return 0;
}
