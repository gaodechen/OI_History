#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e3 + 5;
const	int M = 1e4 + 5;
const	int INF = 0x3f3f3f3f;

int n, up, low, sum, a[N], d[M];

int main()
{
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
	{
		int x, y;
		scanf( "%d%d", &x, &y );
		a[i] = x - y;
		if( a[i] < 0 )
			low += a[i];
		else
			up += a[i];
		sum += a[i];
	}
	memset( d, 0x3f, sizeof( d ) );
	int *p = &d[M/2];
	p[sum] = 0;
	for( int i = 1; i <= n; i ++ )
	{
		int q = a[i] + a[i];
		if( q < 0 )
		{
			for( int j = up; j >= low; j -- )
				p[j] = min( p[j], p[j+q] + 1 );
		}
		else
		{
			for( int j = low; j <= up; j ++ )
				p[j] = min( p[j], p[j+q] + 1 );
		}
	}
	int i = 0, j = 0;
	while( p[i] >= 10000 && p[j] >= 10000 )
		i ++, j --;
	printf( "%d\n", min( p[i], p[j] ) );
	return 0;
}
