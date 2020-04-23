#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e5 + 5;
const	int INF = 0x7fffffff;

inline int ABS( int x )
{
	return x > 0 ? x : -x;
}

struct Item
{
	int k, p;

	Item( int k = 0, int p = 0 ): k( k ), p( p )
	{
	}

	bool operator < ( const Item &b ) const
	{
		return k < b.k;
	}
} e[N];

int n, q, key;

void Interface()
{
	int res = INF, ans;
	// r = 1 at first!
	// l <= n && r <= n!
	int s, t, l = 0, r = 1;
	while( l <= n && r <= n )
	{
		int tmp = ABS( e[r].k - e[l].k );
		if( ABS( tmp - key ) < res )
		{
			ans = tmp;
			res = ABS( tmp - key );
			s = e[l].p, t = e[r].p;
		}
		if( tmp == key )
			break ;
		tmp < key ? r ++ : l ++;
		if( l == r )
			r ++;
	}
	if( s > t )
		swap( s, t );
	printf( "%d %d %d\n", ans, s + 1, t );
	return ;
}

int main()
{
	while( scanf( "%d%d", &n, &q ) == 2 && ( n || q ) )
	{
		e[0] = Item();
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%d", &e[i].k );
			e[i].k += e[i-1].k;
			e[i].p = i;
		}
		sort( e, e + n + 1 );
		while( q -- )
		{
			scanf( "%d", &key );
			Interface();
		}
	}
	return 0;
}
