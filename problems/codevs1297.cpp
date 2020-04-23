#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 220, M = 22000;

bool d[M][M/2];
int w, n, q, val[N], cost[N];

int main()
{
	scanf( "%d%d", &w, &n );
	for( int i = 1; i <= n; i ++ )
	{
		int a, b, v;
		scanf( "%d%d%d", &v, &a, &b );
		for( int j = a; j <= b; j ++ )
			cost[++q] = j, val[q] = v;
	}
	d[0][0] = 1;
	for( int i = 1; i <= q; i ++ )
		for( int j = cost[i]; j <= w; j ++ )
			for( int k = val[i]; k < M / 2; k ++ )
				d[j][k] = d[j][k] || d[j-cost[i]][k-val[i]];
	int res = 0;
	for( int k = 1; k < M; k ++ )
		res += d[w][k];
	printf( "%d\n", res );
	return 0;
}
