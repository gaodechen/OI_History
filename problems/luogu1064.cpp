#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 61, M = 320001;

int m, n, pre[N], num[N], son[N][N], val[N], cost[N], f[M], d[M];

void BinaryPack( int k )
{
	for(int j = m; j >= cost[k]; j --)
		d[j] = max(d[j], d[j - cost[k]] + val[k]);
	return ;
}

int main()
{
	scanf( "%d%d", &m, &n );
	for( int i = 1; i <= n; i ++ )
	{
		int p, v, f;
		scanf( "%d%d%d", &p, &v, &f );
		pre[i] = f;
		son[f][++ num[f]] = i;
		cost[i] = p, val[i] = p * v;
	}
	for( int i = 1; i <= n; i ++ )
	{
		if(!pre[i])
		{
			memcpy(d, f, sizeof(f));
			for(int j = 1; j <= num[i]; j ++)
				BinaryPack(son[i][j]);
			for(int j = cost[i]; j <= m; j ++)
				f[j] = max(f[j], d[j - cost[i]] + val[i]);
		}
	}
	printf( "%d\n", f[m] );
	return 0;
}
