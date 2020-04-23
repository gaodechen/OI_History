#include	<cstdio>
#include	<iostream>
#include	<vector>

using	namespace	std;
const	int N = 2e5 + 5, M = 10007;

vector< int > e[N];
int n, max_, sum, val[N];

int main()
{
	scanf( "%d", &n );
	for( int i = 1; i < n; i ++ )
	{
		int u, v;
		scanf( "%d%d", &u, &v );
		e[u].push_back( v );
		e[v].push_back( u );
	}
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &val[i] );
	for( int i = 1; i <= n; i ++ )
	{
		int k = e[i].size();
		for( int u = 0; u < k; u ++ )
		{
			for( int v = u + 1; v < k; v ++ )
			{
				int a = e[i][u], b = e[i][v];
				int tmp = val[a] * val[b] % M;
				max_ = max( max_, tmp );
				sum += tmp, sum %= M;
			}
		}
	}
	printf( "%d %d\n", max_, sum * 2 % M );
	return 0;
}
