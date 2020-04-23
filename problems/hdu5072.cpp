#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
typedef	long long	data;
const	int N = 1e5 + 5, M = 1e4;

int a[N], cnt[N], cop[N];
int t, tot, mark[N], prime[N], mu[N];

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
		for( int j = 0; j < tot && i * prime[j] < N; j ++ )
		{
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
		data n, ans, res = 0;
		scanf( "%lld", &n );
		ans = n * ( n - 1 ) * ( n - 2 ) / 6;
		memset( cop, 0, sizeof( cop ) );
		memset( cnt, 0, sizeof( cnt ) );
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%d", &a[i] );
			cnt[a[i]] ++;
		}
		for( int i = 1; i < N; i ++ )
			for( int j = i + i; j < N; j += i )
				cnt[i] += cnt[j];
		for( int i = 1; i < N; i ++ )
			for( int j = i; j < N; j += i )
				cop[j] += mu[i] * cnt[i];
		for( int i = 1; i <= n; i ++ )
		{
			if( a[i] == 1 )
				continue ;
			res += ( data )cop[a[i]] * ( data )( n - 1 - cop[a[i]] );
		}
		ans -= res / 2;
		printf( "%lld\n", ans );
	}
	return 0;
}
