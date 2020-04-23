#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int INF = 0x3f3f3f3f;
const	int T = 1001, W = 31;

bool a[T][2];
int t, w, d[T][W];

int main()
{
	scanf( "%d%d", &t, &w );
	for( int i = 1, x; i <= t; i ++ )
	{
		scanf( "%d", &x );
		a[i][x-1] = 1;
	}
	d[1][0] = a[1][0];
	d[1][1] = a[1][1];
	for( int i = 2; i <= t; i ++ )
	{
		for( int j = 0; j <= min( w, i ); j ++ )
		{
			if( j == 0 )
				d[i][j] = d[i-1][j] + a[i][0];
			else
				d[i][j] = max( d[i-1][j-1], d[i-1][j] ) + a[i][j&1];
		}
	}
	printf( "%d\n", d[t][w] );
	return 0;
}
