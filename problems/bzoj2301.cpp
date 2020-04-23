#include    <cstdio>
#include    <cstring>
#include    <iostream>

using	namespace	std;
typedef	long long	data;
const	int N = 5e4 + 5;

bool mark[N];
int t, tot, prime[N], mu[N];

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

int main(int argc, char **argv)
{
	freopen( "in", "r", stdin );
	InitTable();
	scanf( "%d", &t );
	while( t -- )
	{
		data a, b, c, d, k, sum = 0, sum_ = 0;
		scanf( "%lld%lld%lld%lld%lld", &a, &b, &c, &d, &k );
		for( data i = 1; i <= min( a / k, c / k ); i ++ )
			sum_ += mu[i] * ( a / ( k * i ) ) * ( b / ( k * i ) );
		for( data i = 1; i <= min( b / k, d / k ); i ++ )
			sum += mu[i] * ( a / ( k * i ) ) * ( b / ( k * i ) );
		printf( "%lld\n", sum - sum_ );
	}
	return 0;
}
