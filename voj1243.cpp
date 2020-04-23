
#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<deque>

using	namespace	std;
const	int M = 1e5 + 5;
const	int INF = 0x7f7f7f7f;

int m, n, K, l;
int sum[6][M], d[6][M];
deque< int > q[6][6];

inline int F( int i, int j, int k )
{
	return d[k][j] - sum[i][j];
}

int main()
{
	scanf( "%d%d%d%d", &m, &n, &K, &l );
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= m; j ++ )
			scanf( "%d", &sum[i][j] );
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= m; j ++ )
			sum[i][j] += sum[i][j-1];
	memset( d, INF, sizeof( d ) );
	for( int i = 1; i <= n; i ++ )
		d[i][0] = 0;
	for( int j = 0; j <= m; j ++ )
	{
		for( int i = 1; i <= n; i ++ )
		{
			for( int k = 1; k <= n; k ++ )
			{
				if( i == k )
					continue ;
				while( !q[i][k].empty() && j - q[i][k].front() > l )
					q[i][k].pop_front();
                int a = 0, b;
                if( !q[i][k].empty() )
                	a = F( i, q[i][k].front(), k );
                b = sum[i][j] + K;
                if( a + b < d[i][j] )
                	d[i][j] = a + b;
			}
		}
		for( int i = 1; i <= n; i ++ )
		{
			for( int k = 1; k <= n; k ++ )
			{
				int tmp = F( i, j, k );
				while( !q[i][k].empty() && F( i, q[i][k].back(), k ) >= tmp )
					q[i][k].pop_back();
				q[i][k].push_back( j );
			}
		}
	}
	int ans = INF;
	for( int i = 1; i <= n; i ++ )
		if( ans > d[i][m] )
			ans = d[i][m];
	printf( "%d\n", ans - K );
	return 0;
}
