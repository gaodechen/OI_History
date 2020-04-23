#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
typedef	long long	data;
const	int N = 500;

data f[N][N];
int a, b, tot, mark[N], prime[N];

void InitTable()
{
	for( int i = 2; i < N; i ++ )
	{
		if( !mark[i] )
			prime[tot++] = i;
		for( int j = 0; j < tot; j ++ )
		{
			if( i * prime[j] >= N )
				break ;
			mark[i*prime[j]] = 1;
			if( i % prime[j] == 0 )
				break ;
		}
	}
	return ;
}

data F( int n, int p )
{
	if( n >= p )
		return n / p + F( n / p, p );
	return 0;
}

int main()
{
	InitTable();
	for( int i = 1; i < N; i ++ )
		for( int j = 0; j < tot; j ++ )
			if( i >= prime[j] )
				f[i][prime[j]] = F( i, prime[j] );
	while( scanf( "%d%d", &a, &b ) == 2 )
	{
		data ans = 1;
		for( int i = 0; i < tot; i ++ )
			ans *= ( f[a][prime[i]] - f[b][prime[i]] - f[a-b][prime[i]] + 1 );
		cout << ans << endl;
	}
	return 0;
}
