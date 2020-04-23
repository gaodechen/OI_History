#include	<cmath>
#include	<cstdio>
#include	<iostream>

using	namespace	std;

int main()
{
	int n;
	while( scanf( "%d", &n ) && n )
	{
		int res = 1, n_ = n;
		for( int i = 2; n > 1; i ++ )
		{
			if( n % i == 0 )
			{
				int k = 0;
				while( n % i == 0 )
					k ++, n /= i;
				res *= ( k + k + 1 );
			}
		}
		printf( "%d %d\n", n_, ( res + 1 ) / 2 );
	}
	return 0;
}
