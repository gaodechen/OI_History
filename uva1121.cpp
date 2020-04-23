#include	<cstdio>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e5 + 5;

int n, s, a[N];

int main()
{
	while( scanf( "%d%d", &n, &s ) == 2 )
	{
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%d", &a[i] );
			a[i] += a[i-1];
		}
		int cur = 1, ans = n + 1;
		for( int i = 1; i <= n; i ++ )
		{
			if( a[cur-1] + s > a[i] )
				continue ;
			while( a[cur] + s <= a[i] )
				cur ++;
			ans = min( i - cur + 1, ans );
		}
		printf( "%d\n", ans == n + 1 ? 0 : ans );
	}
	return 0;
}
