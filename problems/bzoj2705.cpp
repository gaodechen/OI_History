#include	<cmath>
#include	<cstdio>
#include	<iostream>

using	namespace	std;
typedef	long long	Data;

Data phi( Data k )
{
	Data res = k;
	Data k_ = ( Data )sqrt( k + 0.5 );
	for( int i = 2; i <= k_; i ++ )
	{
		if( k % i == 0 )
		{
			res = res / i * ( i - 1 );
			while( k % i == 0 )
				k /= i;
		}
	}
	if( k > 1 )
		res = res / k * ( k - 1 );
	return res;
}

int main()
{
	Data a, a_, res = 0;
	cin >> a;
	a_ = ( Data )sqrt( a + 0.5 );
	for( int i = 1; i <= a_; i ++ )
	{
		if( a % i == 0 )
		{
			res += phi( a / i ) * i;
			if( i * i < a )
				res += phi( i ) * a / i;
		}
	}
	cout << res;
	return 0;
}
