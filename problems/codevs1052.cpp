#include    <cstdio>
#include    <iostream>
#include	<algorithm>
#include	<queue>

using   namespace   std;
const   int N = 101;

struct Item
{
	int t, val;
	bool operator < ( const Item &b ) const
	{
		return val > b.val;
	}
} e[N];

bool cmp( const Item &a, const Item &b )
{
	return a.t < b.t;
}

int n, sum, sum_;
priority_queue< Item > q;

int main()
{
    scanf( "%d", &n );
    for( int i = 1; i <= n; i ++ )
        scanf( "%d", &e[i].t );
    for( int i = 1; i <= n; i ++ )
	{
        scanf( "%d", &e[i].val );
		sum += e[i].val;
	}
	sort( e + 1, e + n + 1, cmp );
	for( int i = 1; i <= n; i ++ )
	{
		q.push( e[i] );
		if( e[i].t < ( int )q.size() )
		{
			Item t = q.top();
			sum_ += t.val;
			q.pop();
		}
	}
	printf( "%d\n", sum - sum_ );
    return 0;
}
