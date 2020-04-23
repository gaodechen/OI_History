#include	<cmath>
#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 1e6 + 5, M = 8e4;

long long f[N];
int prime[M], phi[N], mark[N];

inline long long F( int d )
{
	if( d == 1 )
		return 1;
	return ( long long )phi[d] * d >> 1;
}

void InitTable()
{
	phi[1] = 1;
	int tot = 0;
	for( int i = 2; i < N; i ++ )
	{
		if( !mark[i] )
		{
			prime[tot++] = i;
			phi[i] = i - 1;
		}
		for( int j = 0; j < tot; j ++ )
		{
			int t = prime[j];
			if( t * i >= N )
				break ;
			mark[t*i] = 1;
			if( i % t == 0 )
			{
				phi[t*i] = phi[i] * t;
				break ;
			}
			else
				phi[t*i] = phi[i] * ( t - 1 );
		}
	}
	for( int d = 1; d < N; d ++ )
		for( int i = d; i < N; i += d )
			f[i] += F( i / d ) * i;
	return ;
}

int main()
{
	int t, q;
	InitTable();
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d", &q );
		printf( "%lld\n", f[q] );
	}
	return 0;
}
