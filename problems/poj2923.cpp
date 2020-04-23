#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = ( 1 << 10 ), M = 11;
const	int INF = 0x3f3f3f3f;

int T, n, m1, m2, tot, ans, cost[M], state[N], d[N];

bool Check( int x )
{
	bool vis[N];
	int sum = 0;
	memset( vis, 0, sizeof( vis ) );
	vis[0] = 1;
	for( int i = 0; i < n; i ++ )
	{
		if( ( 1 << i ) & x )
		{
			sum += cost[i];
			for( int j = m1; j >= cost[i]; j -- )
				if( vis[j-cost[i]] )
					vis[j] = 1;
		}
	}
	for( int i = 0; i <= m1; i ++ )
		if( vis[i] && sum - i <= m2 )
			return 1;
	return false;
}

int main()
{
	scanf( "%d", &T );
	for( int c = 1; c <= T; c ++ )
	{
		scanf( "%d%d%d", &n, &m1, &m2 );
		for( int i = 0; i < n; i ++ )
			scanf( "%d", &cost[i] );
		for( int i = 1; i < ( 1 << n ); i ++ )
			d[i] = INF;
		d[0] = tot = ans = 0;
		for( int i = 1; i < ( 1 << n ); i ++ )
			if( Check( i ) )
				state[tot++] = i;
		for( int i = 0; i < tot; i ++ )
		{
			for( int j = ( 1 << n ) - 1; j + 1; j -- )
			{
				if( d[j] == INF )
					continue ;
				int t = j | state[i];
				if( ( j & state[i] ) == 0 )
					d[t] = min( d[t], d[j] + 1 );
			}
		}
		printf( "Scenario #%d:\n%d\n\n", c, d[(1<<n)-1] );
	}
	return 0;
}
