#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int INF = 0x3f3f3f3f, N = 1001;

struct Item
{
	int l, r, w;
	bool operator < ( const Item &b ) const
	{
		return l < b.l;
	}
} e[N];

int d[N], n, m, r;

int main()
{
	scanf( "%d%d%d", &n, &m, &r );
	for( int i = 1; i <= m; i ++ )
		scanf( "%d%d%d", &e[i].l, &e[i].r, &e[i].w );
	sort( e + 1, e + m + 1 );
	d[1] = e[1].w;
	int ans = 0;
	for( int i = 1; i <= n; i ++ )
	{
		d[i] = e[i].w;
		for( int j = 1; j < i; j ++ )
		{
			if( d[i] < d[j] + e[i].w && e[j].r + r <= e[i].l )
				d[i] = d[j] + e[i].w;
		}
		ans = max( ans, d[i] );
	}
	printf( "%d\n", ans );
	return 0;
}
