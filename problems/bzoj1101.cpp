#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 5e4 + 5;

bool mark[N];
int prime[N], sum[N], mu[N], tot, n;

void InitTable()
{
	mu[1] = 1;
	for( int i = 2; i < N; i ++ )
	{
		if( !mark[i] )
		{
			mu[i] = -1;
			prime[tot++] = i;
		}
		for( int j = 0; j < tot; j ++ )
		{
			int t = i * prime[j];
			if( t >= N )
				break ;
			mark[t] = 1;
			if( i % prime[j] == 0 )
			{
				mu[t] = 0;
				break ;
			}
			else
				mu[t] = -mu[i];
		}
	}
	for( int i = 1; i < N; i ++ )
		sum[i] = sum[i-1] + mu[i];
	return ;
}

int t, a, b, d;

int main()
{
	scanf( "%d", &t );
	InitTable();
	while( t -- )
	{
		scanf( "%d%d%d", &a, &b, &d );
		int a_ = a / d, b_ = b / d;
		int m = min(a_, b_), ans = 0;
		for( int i = 1, last = 0; i <= m; i = last + 1 )
		{
			int t1 = a_ / i, t2 = b_ / i;
			last = min(a_ / t1, b_ / t2);
			ans += (sum[last] - sum[i-1]) * t1 * t2;
		}
		printf("%d\n", ans);
	}
	return 0;
}
