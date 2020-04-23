#include	<cmath>
#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 1e4;

/*
int t, n, m;
int a[N], b[N], n1, n2;

void GetFactors( int *arr, int n )
{
	int p = ( int )sqrt( n + 0.5 );
	for( int i = 2; i <= p; i ++ )
		while( n % i == 0 )
			n /= i, arr[i] ++;
	if( n > 1 )
		arr[n] ++;
	return ;
}

int main()
{
	scanf( "%d", &t );
	for( int tick = 1; tick <= t; tick ++ )
	{
		memset( a, 0, sizeof( a ) );
		memset( b, 0, sizeof( b ) );
		scanf( "%d%d", &n, &m );
		GetFactors( a, n );
		for( int i = 2; i <= m; i ++ )
			GetFactors( b, i );
		int res = 0x7fffffff;
		for( int i = 2; i < N; i ++ )
			if( a[i] && b[i] )
				res = min( res, b[i] / a[i] );
		if( res )
			printf( "%d\n", res );
		else
			printf( "Impossible to divide\n" );
	}
	return 0;
}
*/

int t, n, m, tick;

int GetNum( int n, int d )
{
	int res = 0;
	while( n )
	{
		res += n / d;
		n /= d;
	}
	return res;
}

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		int res = 0x3f3f3f3f;
		scanf( "%d%d", &n, &m );
		for( int i = 2; n > 1; i ++ )
		{
			int a = 0;
			while( n % i == 0 )
			{
				a ++;
				n /= i;
			}
			if( a )
			{
				int b = GetNum( m, i );
				res = min( res, b / a );
			}
		}
		printf( "Case %d:\n", ++ tick );
		if( res )
			printf( "%d\n", res );
		else
			printf( "Impossible to divide\n" );
	}
	return 0;
}
