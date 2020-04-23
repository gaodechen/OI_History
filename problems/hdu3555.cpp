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

int t, dig[20];
data n, d[20][10][2];

data Search( int k, int pre, int flag, int lim )
{
    if( !k )
        return flag;
    if( !lim && d[k][pre][flag] != -1 )
        return d[k][pre][flag];
    int last = lim ? dig[k] : 9;
    data r = 0;
    for( int i = 0; i <= last; i ++ )
        r += Search( k - 1, i, flag || ( pre == 4 && i == 9 ), lim && ( i == last ) );
    if( !lim )
        d[k][pre][flag] = r;
    return r;
}

data Count()
{
	int len = 0;
	while( n )
	{
		dig[++len] = n % 10;
		n /= 10;
	}
	dig[len+1] = 0;
	return Search( len, 0, 0, 1 );
}

int main()
{
    memset( d, -1, sizeof( d ) );
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%lld", &n );
		printf( "%lld\n", Count() );
	}
	return 0;
}

