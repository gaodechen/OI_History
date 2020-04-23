#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int N = 50000, K = 11;
const	int INF = 0x3f3f3f3f;

int t, q, k, n, s, y, d[N], f[N], cost[K], val[K];

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d%d%d", &s, &y, &n );
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%d%d", &cost[i], &val[i] );
			cost[i] /= 1000;
		}
		for( int k = 1; k <= y; k ++ )
		{
			q = s / 1000;
			for( int i = 1; i <= n; i ++ )
				for( int j = cost[i]; j <= q; j ++ )
					d[j] = max( d[j], d[j-cost[i]] + val[i] );
			s += d[q];
			set( d, 0 );
		}
		printf( "%d\n", s );
	}
	return 0;
}
