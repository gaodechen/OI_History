#include	<cstdio>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 100;

struct Item
{
	int t, l;
	bool operator < ( const Item &b ) const
	{
		return l > b.l;
	}
} e[N];

int n, cur, cur_;

int main()
{
	scanf( "%d", &n );
	for( int i = 0; i < n; i ++ )
		scanf( "%d", &e[i].t );
	for( int i = 0; i < n; i ++ )
		scanf( "%d", &e[i].l );
	sort( e, e + n );
	for( int i = 0; i < n; i ++ )
	{
		cur += e[i].t;
		cur_ = max( cur_, cur + e[i].l );
	}
	printf( "%d\n", cur_ );
	return 0;
}
