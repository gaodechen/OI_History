#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 51, M = 5e6 / 2 + 5;

int n, val[N], num[N], d[M], sum;

void BinaryPack( int cost )
{
	for( int j = sum / 2; j >= cost; j -- )
		d[j] = max( d[j], d[j-cost] + cost );
	return ;
}

void InfinitePack( int cost )
{
	for( int j = cost; j <= sum / 2; j ++ )
		d[j] = max( d[j], d[j-cost] + cost );
	return ;
}

int main()
{
	while( scanf( "%d", &n ) && n > 0 )
	{
		sum = 0;
		memset( d, 0, sizeof( d ) );
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%d%d", &val[i], &num[i] );
			sum += val[i] * num[i];
		}
		for( int i = 1; i <= n; i ++ )
		{
			if( val[i] * num[i] >= sum )
				InfinitePack( val[i] );
			else
			{
				int k = 1;
				while( k < num[i] )
				{
					BinaryPack( val[i] * k );
					num[i] -= k;
					k *= 2;
				}
				BinaryPack( val[i] * num[i] );
			}
		}
		printf( "%d %d\n", sum - d[sum/2], d[sum/2] );
	}
	return 0;
}
