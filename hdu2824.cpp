#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 3e6 + 5;

bool mark[N];
int prime[N/2];
long long phi[N];

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
		for( int j = 0; j < tot && prime[j] * i < N; j ++ )
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
	int a, b;
	InitTable();
	for( int i = 2; i < N; i ++ )
		phi[i] += phi[i-1];
	while( scanf( "%d%d", &a, &b ) == 2 )
		printf( "%lld\n", phi[b] - phi[a-1] );
	return 0;
}
