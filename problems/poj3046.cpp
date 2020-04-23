#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int MOD = 1000000;
const	int T = 1001, N = 100001;

int num[T], d[N][2];

int main()
{
	int t, a, x, y;
	scanf( "%d%d%d%d", &t, &a, &x, &y );
	for( int i = 1, k; i <= a; i ++ )
	{
		scanf( "%d", &k );
		num[k] ++;
	}
	d[0][0] = 1;
	for(int i = 1; i <= t; i ++)
	{
		for(int j = 0; j <= y; j ++)
		{
			int p = i & 1, q = p ^ 1;
			if(j - 1 - num[i] >= 0)
			{
				d[j][p] = d[j-1][p] + d[j][q] - d[j-1-num[i]][q] + MOD;
				while(d[j][p] >= MOD) d[j][p] -= MOD;
			}
			else
			{
				d[j][p] = d[j-1][p] + d[j][q];
				while(d[j][p] >= MOD) d[j][p] -= MOD;
			}
		}
	}
	int ans = 0;
	for( int i = x; i <= y; i ++ )
	{
		ans += d[i][t&1];
		while( ans >= MOD ) ans -= MOD;
	}
	printf( "%d\n", ans );
	return 0;
}
