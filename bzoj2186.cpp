#include	<cstdio>
#include	<iostream>

using	namespace	std;
typedef	long long	data;
const	int N = 1e7 + 5, M = 70e4;

bool mark[N];
int t, r, n, m, tot;
data phi[N], inv[N], fac[N], prime[M];

void InitTable()
{
	fac[1] = 1, inv[1] = 1, phi[1] = 1;
	for( data i = 2; i < N; i ++ )
	{
		if( !mark[i] )
			prime[tot++] = i;
		for( int j = 0; j < tot && i * prime[j] < N; j ++ )
		{
			mark[i*prime[j]] = 1;
			if( i % prime[j] == 0 )
				break ;
		}
	}
	for( int i = 2; i < N && i < r; i ++ )
		inv[i] = ( r - r / i ) * inv[r%i] % r;
	for( int i = 2; i < N; i ++ )
		fac[i] = fac[i-1] * i % r;
	for( int i = 2; i < N; i ++ )
	{
		if( !mark[i] )
			phi[i] = phi[i-1] * ( i - 1 ) % r * inv[i%r] % r;
		else
			phi[i] = phi[i-1];
	}
	return ;
}

int main()
{
	scanf( "%d%d", &t, &r );
	InitTable();
	while( t -- )
	{
		scanf( "%d%d", &n, &m );
		printf( "%lld\n", phi[m] * fac[n] % r );
	}
	return 0;
}
