#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 4e4 + 5;

bool mark[N];
int prime[N], sum[N], mu[N], tot, n;

void InitTable()
{
	mu[1] = 1;
	for( int i = 2; i <= n; i ++ )
	{
		if( !mark[i] )
		{
			mu[i] = -1;
			prime[tot++] = i;
		}
		for( int j = 0; j < tot && i * prime[j] <= N; j ++ )
		{
			mark[i * prime[j]] = 1;
			if( i % prime[j] == 0 )
			{
				mu[i*prime[j]] = 0;
				break ;
			}
			else
				mu[i*prime[j]] = -mu[i];
		}
	}
	for( int i = 1; i <= n; i ++ )
		sum[i] = sum[i-1] + mu[i];
	return ;
}

int main()
{
	scanf( "%d", &n );
	int ans = 0; n --;
	InitTable();
	for( int i = 1, last = 0; i <= n; i = last + 1 )
	{
		last = n / ( n / i );
		ans += ( sum[last] - sum[i-1] ) * ( n / i ) * ( n / i );
	}
	printf( "%d\n", ans + 2 );
	return 0;
}
