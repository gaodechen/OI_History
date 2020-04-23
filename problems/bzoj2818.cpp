#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 1e7 + 5, M = 63e4;

long long res, sum[N];
int prime[M], mark[N], phi[N], tot, n;

void InitTable()
{
	phi[1] = 1;
	for( int i = 2; i <= n; i ++ )
	{
		if( !mark[i] )
		{
			prime[tot++] = i;
			phi[i] = i - 1;
		}
		for( int j = 0; j < tot && prime[j] * i <= n; j ++ )
		{
			mark[i*prime[j]] = 1;
			if( i % prime[j] == 0 )
			{
				phi[i*prime[j]] = phi[i] * prime[j];
				break ;
			}
			else
				phi[i*prime[j]] = phi[i] * ( prime[j] - 1 );
		}
	}
	return ;
}

int main()
{
	scanf( "%d", &n );
	InitTable();
	sum[1] = 1;
	for( int i = 2; i <= n; i ++ )
		sum[i] = sum[i-1] + phi[i] * 2;
	for( int i = 0; i < tot; i ++ )
		res += sum[n/prime[i]];
	printf( "%lld\n", res );
	return 0;
}
