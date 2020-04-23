#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int INF = 0x3f3f3f3f, N = 21;

int n, c, ans, need[N];

struct Item
{
	int v, b;
	bool operator < ( const Item &b ) const
	{
		return v < b.v;
	}
} e[N];

int main()
{
	freopen( "in", "r", stdin );
	scanf( "%d%d", &n, &c );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d%d", &e[i].v, &e[i].b );
	for( int i = 1; i <= n; i ++ )
		if( e[i].v >= c )
			ans += e[i].b, e[i].v = 0;
	sort( e + 1, e + n + 1 );
	while( true )
	{
		int sum = c;
		set( need, 0 );
		for( int i = n; i >= 1; i -- )
		{
			if( sum > 0 && e[i].v > 0 )
			{
				int t = min( e[i].b, sum / e[i].v );
				if( t > 0 )
				{
					sum -= t * e[i].v;
					need[i] = t;
				}
			}
		}
		if( sum > 0 )
		for ( int i = 1; i <= n; i ++ )
		{
			if( e[i].v >= sum && e[i].b - need[i] )
			{
				need[i] ++, sum = 0;
				break ;
			}
		}
		if( sum > 0 )
			break ;
		int add = INF;
		for( int i = 1; i <= n; i ++ )
			if( need[i] )
				add = min( add, e[i].b / need[i] );
		if( add == 0 )
			break ;
		ans += add;
		for( int i = 1; i <= n; i ++ )
			if( need[i] )
				e[i].b -= add * need[i];
	}
	printf( "%d\n", ans );
	return 0;
}
