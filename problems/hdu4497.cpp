#include	<cstdio>
#include	<iostream>

using	namespace	std;

int main()
{
	int t, a, b;
	scanf( "%d", &t );
	while( t -- )
	{
		int ans = 1;
		scanf( "%d%d", &a, &b );
		if( b % a )
		{
			printf( "0\n" );
			continue ;
		}
		int k = b / a;
		for( int i = 2; i * i <= k; i ++ )
		{
			int t = 0;
			if( k % i == 0 )
			{
				while( k % i == 0 )
					k /= i, t ++;
				ans *= t * 6;
				// ans *= ( t + 1 ) * ( t + 1 ) * ( t + 1 ) - 2 * t * t * t + ( t - 1 ) * ( t - 1 ) * ( t - 1 );
			}
		}
		if( k > 1 )
			ans *= 6;
		printf( "%d\n", ans );
	}
	return 0;
}
