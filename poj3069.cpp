#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e3 + 5;

int r, n, ans, x[N], mark[N];

int Find( int k )
{
	int flag = 0;
	for( int j = n; j > k; j -- )
	{
		if( x[j] - r <= x[k] )
		{
			flag = j;
			break ;
		}
	}
	ans ++;
	if( !flag )
		return k;
	return flag;
}

int main()
{
	while( scanf( "%d%d", &r, &n ) && r >= 0 )
	{
		ans = 0;
		memset( mark, 0, sizeof( mark ) );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d", &x[i] );
		sort( x + 1, x + n + 1 );
		for( int i = 1; i <= n; i ++ )
		{
			if( !mark[i] )
			{
				int t = Find( i );
				for( int j = 1; j <= n; j ++ )
					if( x[t] + r >= x[j] && x[t] - r <= x[j] )
						mark[j] = 1;
			}
		}
		printf( "%d\n", ans );
	}
	return 0;
}
