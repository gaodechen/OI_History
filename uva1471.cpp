#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 2e5 + 5;
const	int INF = 0x3f3f3f3f;

int t, n, a[N], pre[N], suf[N], d[N];

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d", &a[i] );
		for( int i = 1; i <= n; i ++ )
			pre[i] = suf[i] = 1;
		for( int i = 2; i <= n; i ++ )
			if( a[i] > a[i-1] )
				pre[i] += pre[i-1];
		for( int i = n - 1; i >= 1; i -- )
			if( a[i] < a[i+1] )
				suf[i] += suf[i+1];
		int ans = 0;
		memset( d, INF, sizeof( d ) );
		for( int i = 1; i <= n; i ++ )
		{
			int len = lower_bound( d + 1, d + n + 1, a[i] ) - d;
			ans = max( ans, suf[i] + len - 1 );
			d[pre[i]] = min( d[pre[i]], a[i] );
		}
		printf( "%d\n", ans );
	}
	return 0;
}
