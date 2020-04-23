#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 5e3 + 100;
const	int INF = 0x3f3f3f3f;

bool dir[N], f[N];

int main()
{
	int n, K = 1, ans = 0;
	scanf( "%d", &n );
	for( int i = 0; i < n; i ++ )
	{
		char buf[2];
		scanf( "%s", buf );
		if( buf[0] == 'B' )
			dir[i] = 0, ans ++;
		else
			dir[i] = 1;
	}
	for( int k = 2; k <= n; k ++ )
	{
		int sum = 0, res = 0;
		memset( f, 0, sizeof( f ) );
		for( int i = 0; i <= n - k; i ++ )
		{
			if( sum == dir[i] )
				f[i] = 1, res ++, sum ^= 1;
			if( i - k + 1 >= 0 )
				sum ^= f[i-k+1];
		}
		for( int i = n - k + 1; i < n; i ++ )
		{
			if( sum == dir[i] )
			{
				res = INF;
				break ;
			}
			if( i - k + 1 >= 0 )
				sum ^= f[i-k+1];
		}
		if( res < ans )
			K = k, ans = res;
	}
	printf( "%d %d\n", K, ans );
	return 0;
}
