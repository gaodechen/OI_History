#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e2 + 5;
const   int INF = 0x3f3f3f3f;

int h, n, sum, d[N][N];

struct Item
{
	int t, w, h;

	bool operator < ( const Item &b ) const
	{
		return t < b.t;
	}
} e[101];

int main()
{
	scanf( "%d%d", &h, &n );
	for( int i = 1; i <= n; i ++ )
		cin >> e[i].t >> e[i].w >> e[i].h;
	memset( d, 128, sizeof( d ) );
	e[0].t = 0, d[0][0] = 10;
	sort( e + 1, e + n + 1 );
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = 0; j <= h; j ++ )
		{
			if( d[i-1][j] >= e[i].t )
				d[i][j] = d[i-1][j] + e[i].w;
			if( j >= e[i].h && d[i-1][j-e[i].h] >= e[i].t )
				d[i][j] = max( d[i][j], d[i-1][j-e[i].h] );
			if( d[i][j] >= 0 && j == h )
			{
				printf( "%d\n", e[i].t );
				return 0;
			}
		}
	}
	int live = 10;
	for( int i = 1; i <= n; i ++ )
		if( live >= e[i].t )
			live += e[i].w;
	printf( "%d\n", live );
	return 0;
}
