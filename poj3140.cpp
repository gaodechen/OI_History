#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<vector>

using	namespace	std;
typedef	long long	data;
const	int N = 1e5 + 5;

int n, m, c;
vector< int > e[N];
data sum, d[N];

inline data abs( data x )
{
	return x > 0 ? x : -x;
}

data DFS( int u, int pre )
{
	for( int i = 0; i < ( int )e[u].size(); i ++ )
		if( e[u][i] != pre )
			d[u] += DFS( e[u][i], u );
	return d[u];
}

int main()
{
	while( scanf( "%d%d", &n, &m ) && n && m )
	{
		sum = 0;
		memset( d, 0, sizeof( d ) );
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%I64d", &d[i] );
			sum += d[i];
			e[i].clear();
		}
		for( int i = 1; i <= m; i ++ )
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			e[u].push_back( v );
			e[v].push_back( u );
		}
		DFS( 1, 1 );
		data ans = 0x7fffffffffffff;
		for( int i = 1; i <= n; i ++ )
			ans = min( ans, abs( sum - d[i] - d[i] ) );
		printf( "Case %d: %I64d\n", ++ c, ans );
	}
	return 0;
}
