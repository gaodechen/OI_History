#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int INF = 0x3f3f3f3f, N = 2001;

int n, a[N], d[N][N];

int main()
{
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &a[i] );
	for( int i = 1; i <= n; i ++ )
		d[i][i] = a[i] * n;
	for( int len = 1; len < n; len ++ )
	{
		for( int i = 1; i + len <= n; i ++ )
		{
			int j = i + len;
			d[i][j] = max( d[i+1][j] + ( n - len ) * a[i], d[i][j-1] + ( n - len ) * a[j] );
		}
	}
	printf( "%d\n", d[1][n] );
	return 0;
}
