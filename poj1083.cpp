#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

using	namespace	std;
const	int N = 201;

struct Segment
{
	int l, r;
	bool operator < ( const Segment &a ) const
	{
		return r > a.r;
	}
} e[N];

bool cmp( const Segment &a, const Segment &b )
{
	return a.l < b.l;
}

int main()
{
	int t, n;
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ )
		{
			int a, b;
			scanf( "%d%d", &a, &b );
			if( a > b )
				swap( a, b );
			a = ( a + 1 ) / 2;
			b = ( b + 1 ) / 2;
			e[i].l = a, e[i].r = b;
		}
		sort( e + 1, e + n + 1, cmp );
		priority_queue< Segment > q;
		q.push( e[1] );
		int sum = 1;
		for( int i = 2; i <= n; i ++ )
		{
			Segment tmp = q.top(); q.pop();
			if( tmp.r < e[i].l )
			{
				tmp.r = e[i].r;
				q.push( tmp );
			}
			else
			{
				sum ++;
				q.push( tmp );
				tmp.r = e[i].r;
				q.push( tmp );
			}
		}
		printf( "%d0\n", sum );
	}
	return 0;
}
