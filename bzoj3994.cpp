#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 5e4 + 5;

int prime[N], f[N], k[N], mark[N];

void InitTable()
{
	f[1] = 1;
	int tot = 0;
	for( int i = 2; i < N; i ++ )
	{
		if( !mark[i] )
		{
			prime[tot++] = i;
			k[i] = 1, f[i] = 2;
		}
		for( int j = 0; j < tot && prime[j] * i < N; j ++ )
		{
			int t = prime[j] * i;
			mark[t] = 1;
			if( i % prime[j] == 0 )
			{
				k[t] = k[i] + 1;
				f[t] = f[i] / ( k[i] + 1 ) * ( k[t] + 1 );
				break ;
			}
			else
			{
				f[t] = f[i] * f[prime[j]];
				k[t] = 1;
			}
		}
	}
	return ;
}

int main()
{
	InitTable();
	int t, n, m;
	scanf( "%d", &t );
	while( t -- )
	{
		int ans = 0;
		scanf( "%d%d", &n, &m );
		for( int i = 1; i <= n; i ++ )
			for( int j = 1; j <= m; j ++ )
				ans += f[i*j];
		printf( "%d\n", ans );
	}
	return 0;
}
