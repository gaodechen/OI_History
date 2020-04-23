#include	<cstdio>
#include	<iostream>

using	namespace	std;
typedef	long long	data;
const	int N = 100001;

data n, m;
int tot, mark[N], prime[N], phi[N];

void InitTable()
{
	phi[1] = 1;
	for( int i = 2; i < N; i ++ )
	{
		if( !mark[i] )
		{
			prime[tot++] = i;
			phi[i]  = i - 1;
		}
		for( int j = 0; j < tot; j ++ )
		{
			if( i * prime[j] >= N )
				break ;
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
	InitTable();
	cin >> n >> m;
	data ans = 0;
	for( data i = 1; i <= min( n, m ); i ++ )
		ans += phi[i] * ( n / i ) * ( m / i );
	ans = ans * 2 - n * m;
	printf( "%lld\n", ans );
	return 0;
}
