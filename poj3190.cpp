#include	<cstdio>
#include	<iostream>
#include	<algorithm>
#include	<queue>

using	namespace	std;
const	int N = 5e4 + 5;

struct Item
{
	int r, p;
	Item( int r = 0, int p = 1 ): r( r ), p( p )
	{
	}
	bool operator < ( const Item &b ) const
	{
		return r > b.r;
	}
};

int n, k = 1, mark[N];
priority_queue< Item > q;

struct Interval
{
	int l, r, id;
	bool operator < ( const Interval &b ) const
	{
		return l < b.l;
	}
} e[N];

int main()
{
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
	{
		scanf( "%d%d", &e[i].l, &e[i].r );
		e[i].id = i;
	}
	sort( e + 1, e + n + 1 );
	q.push( Item( 0, 1 ) );
	for( int i = 1; i <= n; i ++ )
	{
		Item tmp = q.top();
		q.pop();
		if( tmp.r < e[i].l )
		{
			tmp.r = e[i].r;
			mark[e[i].id] = tmp.p;
			q.push( tmp );
		}
		else
		{
			q.push( tmp );
			mark[e[i].id] = ++ k;
			q.push( Item( e[i].r, k ) );
		}
	}
	printf( "%d\n", k );
	for( int i = 1; i <= n; i ++ )
		printf( "%d\n", mark[i] );
	return 0;
}
