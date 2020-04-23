#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 5e4 + 5;

int n, k, pre[N], rank[N];

int Find( int u )
{
	if( u != pre[u] )
	{
		int t = pre[u];
		pre[u] = Find( pre[u] );
		rank[u] = ( rank[u] + rank[t] ) % 3;
	}
	return pre[u];
}

inline void Union( int u, int v, int d )
{
	int x = Find( u );
	int y = Find( v );
	pre[y] = x;
	rank[y] = ( rank[u] - rank[v] - d + 3 ) % 3;
	return ;
}

int main()
{
	int ans = 0;
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ )
		pre[i] = i;
	for( int i = 0; i < k; i ++ )
	{
		int d, x, y;
		scanf( "%d%d%d", &d, &x, &y );
		if( x > n || y > n )
		{
			ans ++;
			continue ;
		}
		d --;
		Find( x ), Find( y );
		if( pre[x] == pre[y] )
		{
			if( rank[x] != ( rank[y] + d ) % 3 )
				ans ++;
			continue ;
		}
		Union( x, y, d );
	}
	printf( "%d\n", ans );
	return 0;
}
