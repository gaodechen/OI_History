#include	<cstdio>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e5 + 5;

struct Item
{
	int x, y, id;
	Item( int x = 0, int y = 0, int id = 0 )
	{
		this -> x = x;
		this -> y = y;
		this -> id = id;
	}
	bool operator < ( const Item &b ) const
	{
		if( x != b.x )
			return x < b.x;
		return y > b.y;
	}
} e[N];

Item d[N];
int n, len, pos[N];

int LowerBound( int l, int r, int k )
{
	while( l < r )
	{
		int mid = ( l + r ) >> 1;
		if( d[mid].y >= k )
			r = mid;
		else
			l = mid + 1;
	}
	return l;
}

int main()
{
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
	{
		scanf( "%d%d", &e[i].x, &e[i].y );
		e[i].id = i;
	}
	sort( e + 1, e + n + 1 );
	d[++len] = e[1], pos[1] = 1;
	for( int i = 2; i <= n; i ++ )
	{
		int p;
		if( d[len].y < e[i].y )
		{
			p = ++ len;
			pos[i] = len;
		}
		else
		{
			p = LowerBound( 1, len, e[i].y );
			pos[i] = p;
		}
		d[p] = e[i];
	}
	printf( "%d\n", len );
	int t = len;
	for( int i = n; i; i -- )
	{
		if( pos[i] == t )
		{
			printf( "%d ", e[i].id );
			t --;
		}
	}
	return 0;
}
