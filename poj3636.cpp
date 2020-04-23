#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 2e4 + 5;

struct Item
{
	int w, h;
} e[N];

int t, n, d[N];

bool cmp( const Item &a, const Item &b )
{
	if( a.w == b.w )
		return a.h > b.h;
	return a.w < b.w;
}

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d%d", &e[i].w, &e[i].h );
		sort( e + 1, e + n + 1, cmp );
		for( int i = 1; i <= n; i ++ )
			e[i].h = -e[i].h;
		int len = 0;
		memset( d, 0, sizeof( d ) );
		d[++len] = e[1].h;
		for( int i = 2; i <= n; i ++ )
		{
			int p;
			if( e[i].h >= d[len] )
				p = ++ len;
			else
				p = upper_bound( d + 1, d + len + 1, e[i].h ) - d;
			d[p] = e[i].h;
		}
		printf( "%d\n", len );
	}
	return 0;
}
