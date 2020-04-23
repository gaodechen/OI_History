#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<cmath>
#include	<cstring>

using	namespace	std;
const	int INF = 0x3f3f3f3f;

int gcd( int a, int b )
{
	if( b == 0 )
		return a;
	return gcd( b, a % b );
}

string str;

int main()
{
	freopen( "in", "r", stdin );
	while( cin >> str && str.length() > 1 )
	{
		int x = INF, y = INF;
		int p = 0, l = 0;
		for( int i = 2; str[i] != '.'; i ++ )
		{
			p = p * 10 + str[i] - '0';
			l ++;
		}
		for( int i = 1, q = p, k = 1; i <= l; i ++ )
		{
			q /= 10, k *= 10;
			int a = p - q;
			int b = ( int )pow( 10.0, l - i ) * ( k - 1 );
			int d = gcd( a, b );
			if( b / d < y )
				x = a / d, y = b / d;
		}
		printf( "%d/%d\n", x, y );
	}
	return 0;
}
