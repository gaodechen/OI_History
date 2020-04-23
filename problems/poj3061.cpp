#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 1e5 + 5, INF = 0x3f3f3f3f;

int t, n, s, a[N];

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d%d", &n, &s );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d", &a[i] );
		int l = 1, r = 0, sum = 0, ans = INF;
		while( l <= n )
		{
			while( r < n && sum < s )
				sum += a[++r];
			if( sum < s )
				break ;
			ans = min( ans, r - l + 1 );
			sum -= a[l++];
		}
		printf( "%d\n", ans == INF ? 0 : ans );
	}
	return 0;
}
