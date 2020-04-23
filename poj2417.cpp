#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<cmath>

using	namespace	std;
typedef	long long	data;
const	int MOD = 133331;

int a, b, n, sig;
int hash[MOD], head[MOD], next[MOD], ind[MOD];

void Insert( int x, int p )
{
	int k = x % MOD;
	hash[++ sig] = x, ind[sig] = p;
	next[sig] = head[k], head[k] = sig;
	return ;
}

int Find( int x )
{
	int k = x % MOD;
	for( int i = head[k]; i != -1; i = next[i] )
		if( hash[i] == x )
			return ind[i];
	return -1;
}

int BSGS()
{
	// Be careful to judge specially!
    // The minimum solution
	if(b == 1) return 0;
	a %= n, b %= n;
	int m = (int) sqrt(n + 0.5);
	data x = 1, p = 1;
	for(int i = 0; i < m; i ++)
	{
		Insert(p * b % n, i);
		p = p * a % n;
	}
	// Now, p = a ^ m
	for(data i = m; ; i += m)
	{
		x = x * p % n;
		data t = Find(x);
		if(t != -1) return i - t;
		if(i > n) break ;
	}
	return -1;
}

int main()
{
	while( scanf( "%d%d%d", &n, &a, &b ) == 3 )
	{
		sig = 0;
		memset( head, -1, sizeof( head ) );
		int ans = BSGS();
		if( ans == -1 )
			printf( "no solution\n" );
		else
			printf( "%d\n", ans );
	}
	return 0;
}
