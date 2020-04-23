#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 1e7 + 5, K = 63e4;

int tot, f[N], k[N], mark[N], prime[N];

void InitTable()
{
	for( int i = 2; i < N; i ++ )
	{
		if( !mark[i] )
		{
			prime[tot++] = i;
		}
		for( int j = 0; j < tot && i * prime[j] < N; j ++ )
		{
			mark[i*prime[j]] = 1;
			if( i % prime[j] == 0 )
			{
				break ;
			}
			else
			{
			}
		}
	}
	return ;
}

int main()
{
	int t, n;
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d", &n );
		printf( "%d\n", f[n] );
	}
	return 0;
}
