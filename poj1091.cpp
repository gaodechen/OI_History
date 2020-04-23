#include	<cstdio>
#include	<iostream>

using	namespace	std;
typedef	long long	data;
const	int M = 20;

data sum, ans;
int n, m, tot, e[M], t[M];

void GetFactors( int k )
{
	for( int i = 2; i * i <= k; i ++ )
	{
		if( k % i == 0 )
		{
			e[tot++] = i;
			while( k % i == 0 )
				k /= i;
		}
	}
	if( k > 1 )
		e[tot++] = k;
	return ;
}

data pow( data a, int k )
{
	data res = 1;
	while( k )
	{
		if( k & 1 )
			res *= a;
		k >>= 1;
		a *= a;
	}
	return res;
}

void DFS( int k, int p, int s )
{
	if( k == s )
	{
		data m_ = m;
		for( int i = 0; i < k; i ++ )
			m_ /= t[i];
		sum += pow( m_, n );
		return ;
	}
	for( int i = p; i < tot; i ++ )
	{
		t[k] = e[i];
		DFS( k + 1, i + 1, s );
	}
	return ;
}

int main()
{
	scanf( "%d%d", &n, &m );
	GetFactors( m );
	data ans = pow( m, n );
	for( int i = 1; i <= tot; i ++ )
	{
		sum = 0;
		DFS( 0, 0, i );
		if( i & 1 )
			ans -= sum;
		else
			ans += sum;
	}
	printf( "%lld\n", ans );
	return 0;
}
