#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int INF = 0x3f3f3f3f;
const	int N = 1e2 + 5, M = 3e5;

int n_, n, s[N], f[N], d[M], low, up;

int main()
{
	scanf( "%d", &n_ );
	for( int i = 1; i <= n_; i ++ )
	{
		int a, b;
		scanf( "%d%d", &a, &b );
		if( a < 0 && b < 0 )
			continue ;
		s[++n] = a, f[n] = b;
		if( a > 0 )
			up += a;
		else
			low += a;
	}
	int *p = &d[M/2];
	memset( d, -INF, sizeof( d ) );
	p[0] = 0;
	for( int i = 1; i <= n; i ++ )
	{
		if( s[i] >= 0 )
 	{
			for( int j = up; j >= low; j -- )
				if( p[j-s[i]] > -INF )
					p[j] = max( p[j], p[j-s[i]] + f[i] );
		}
		else
		{
			for( int j = low; j <= up; j ++ )
				if( p[j-s[i]] > -INF )
					p[j] = max( p[j], p[j-s[i]] + f[i] );
		}
	}
	int ans = 0;
	for( int j = up; j >= 0; j -- )
		if( p[j] >= 0 )
			ans = max( j + p[j], ans );
	printf( "%d\n", ans );
	return 0;
}
