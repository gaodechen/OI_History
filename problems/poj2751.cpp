#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e4 + 5;

struct Item
{
	int x, y;
	bool operator < ( const Item &b ) const
	{
		return x + max( y, b.x ) + b.y < y + max( x, b.y ) + b.x;
	}
} e[N];

int n;

int main()
{
	while( scanf( "%d", &n ) && n )
	{
		for( int i = 0; i < n; i ++ )
			scanf( "%d%d", &e[i].x, &e[i].y );
		sort( e, e + n );
		int curA = 0, curB = 0;
		for( int i = 0; i < n; i ++ )
		{
			curA += e[i].x;
			curB = max( curA, curB ) + e[i].y;
		}
		printf( "%d\n", max( curA, curB ) );
	}
	return 0;
}

