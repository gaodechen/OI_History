#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e4 + 5;

bool mark[N];
int n, tot, prime[N];

void InitTable()
{
	for( int i = 2; i < N; i ++ )
	{
		if( !mark[i] )
			prime[++tot] = i;
		for( int j = 1; j <= tot; j ++ )
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

int main()
{
	InitTable();
	while( scanf( "%d", &n ) == 1 && n )
	{
		int l = 1, r = 0, sum = 0, ans = 0;
		while( prime[r] <= n )
		{
			if( sum == n )
				ans ++, sum -= prime[l++];
			else if( sum < n )
				sum += prime[++r];
			else
				sum -= prime[l++];
		}
		printf( "%d\n", ans );
	}
	return 0;
}
