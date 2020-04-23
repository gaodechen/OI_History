#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
typedef	long long	data;
const	int N = 1e3 + 5;

data lim, mark, ans[N], tmp[N];

data gcd( data a, data b )
{
	return b ? gcd( b, a % b ) : a;
}

data GetFirst( data a, data b )
{
	data c = 1;
	while( a * c < b )
		c ++;
	return c;
}

void Search( data k, data p, data a, data b )
{
	if( k + 1 == lim )
	{
		if( b % a == 0 )
		{
			tmp[k] = b / a;
			if( !mark || tmp[k] < ans[k] )
			{
				memcpy( ans, tmp, sizeof( tmp ) );
				mark = 1;
			}
		}
		return ;
	}
	p = max( p, GetFirst( a, b ) );
	for( int i = p; ; i ++ )
	{
		if( mark && ans[lim-1] <= i )
			break ;
		if( b * ( lim - k ) <= a * i )
			break ;
		tmp[k] = i;
		data a_ = a * i - b, b_ = b * i;
		data d = gcd( a_, b_ );
		Search( k + 1, i + 1, a_ / d, b_ / d );
	}
	return ;
}

int main()
{
	data a, b;
	scanf( "%lld%lld", &a, &b );
	memset( ans, -1, sizeof( ans ) );
	for( lim = 1; ; lim ++ )
	{
		Search( 0, GetFirst( a, b ), a, b );
		if( mark )
			break ;
	}
	for( data i = 0; i < lim; i ++ )
		printf( "%lld ", ans[i] );
	printf( "\n" );
	return 0;
}
