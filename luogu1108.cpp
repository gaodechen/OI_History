#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 6e3 + 5;

int a[N], b[N], d[N], s[N], mark[N], n, m, sum;

int main()
{
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &a[i] );
	memcpy( b, a, sizeof( a ) );
	sort( b + 1, b + n + 1 );
	for( int i = 1; i <= n; i ++ )
		a[i] = lower_bound( b + 1, b + n + 1, a[i] ) - b;
	a[++n] = -2;
	for( int i = 1; i <= n; i ++ )
	{
		d[i] = 1;
		for( int j = 1; j < i; j ++ )
			if( a[j] > a[i] )
				d[i] = max( d[i], d[j] + 1 );
		for( int j = i; j >= 1; j -- )
		{
			if( a[j] == a[i] )
				s[j] = 0;
			else if( a[j] > a[i] && d[i] == d[j] + 1 )
				s[i] += s[j];
		}
		m = max( m, d[i] );
		s[i] = max( 1, s[i] );
	}
	printf( "%d %d\n", m - 1, s[n] );
	return 0;
}

