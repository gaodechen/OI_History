#include    <cstdio>
#include    <cstring>
#include    <iostream>

using	namespace	std;
typedef long long	data;
const	int N = 1e6 + 5, M = 8e4;

data n;
bool mark[N];
int t, tot, prime[M], mu[N];

void InitTable()
{
	mu[1] = 1;
	for( int i = 2; i < N; i ++ )
	{
		if( !mark[i] )
		{
			prime[tot++] = i;
			mu[i] = -1;
		}
		for( int j = 0; j < tot; j ++ )
		{
			if( i * prime[j] >= N )
				break ;
			mark[i*prime[j]] = 1;
			if( i % prime[j] == 0 )
			{
				mu[i*prime[j]] = 0;
				break ;
			}
			mu[i*prime[j]] = -mu[i];
		}
	}
	return ;
}

int main()
{
	InitTable();
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%lld", &n );
		data ans = 3;
		for( data i = 1; i <= n; i ++ )
			ans += mu[i] * ( n / i ) * ( n / i ) * ( n / i + 3 );
		printf( "%lld\n", ans );
	}
	return 0;
}
