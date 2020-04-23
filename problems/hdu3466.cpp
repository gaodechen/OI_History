#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 5e2 + 5, M = 5e3 + 5;

int n, m, d[M];

struct Item
{
	int p, q, v;
	bool operator < ( const Item &b ) const
	{
		return q - p < b.q - b.p;
	}
} e[N];

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		memset( d, 0, sizeof( d ) );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d%d%d", &e[i].p, &e[i].q, &e[i].v );
		sort( e + 1, e + n + 1 );
		for( int i = 1; i <= n; i ++ )
			for( int j = m; j >= e[i].q; j -- )
				d[j] = max( d[j], d[j-e[i].p] + e[i].v );
		printf( "%d\n", d[m] );
	}
	return 0;
}
