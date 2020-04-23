#include	<cstdio>
#include	<cstring>
#include	<iostream>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 2e5 + 5;

struct BIT
{
	int n, node[N];

	inline int lowbit( int x )
	{
		return x & ( -x );
	}

	int GetSum( int p )
	{
		int sum = 0;
		for( int i = p; i > 0; i -= lowbit( i ) )
			sum += node[i];
		return sum;
	}

	void Modify( int p, int k )
	{
		for( int i = p; i <= n; i += lowbit( i ) )
			node[i] += k;
		return ;
	}

} tree;

int n, a[N], b[N], v[N], ans[N];

void Cantor( int *arr )
{
	set( tree.node, 0 );
	for( int i = 1; i <= n; i ++ )
	{
		int k = arr[i] - tree.GetSum( arr[i] ) - 1;
		tree.Modify( arr[i], 1 );
		v[n-i] += k;
	}
	return ;
}

// Return with the right side [1, r] where
// the number of 0 in it is equal to k
int BinarySearch( int l, int r, int k )
{
	while( l < r )
	{
		int mid = ( l + r ) >> 1;
		if( mid - tree.GetSum( mid ) >= k )
			r = mid;
		else
			l = mid + 1;
	}
	return l;
}

void InvCator()
{
	set( tree.node, 0 );
	for( int t, i = n - 1; i >= 0; i -- )
	{
		t = BinarySearch( 1, n, v[i] + 1 );
		tree.Modify( t, 1 );
		ans[i] = t;
	}
	return ;
}

int main()
{
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &a[i] );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &b[i] );
	for( int i = 1; i <= n; i ++ )
		a[i] ++, b[i] ++;
	tree.n = n;
	Cantor( a ), Cantor( b );
	for( int i = 1; i < n - 1; i ++ ) if( v[i] > i )
	{
		v[i] -= i + 1;
		v[i + 1] ++;
	}
	v[n - 1] %= n;
	// How many n can there be
	// How many n! will be there
	// v[n - 1] % n is equivalent to v[n - 1] * (n - 1)! mod (n!)
	InvCator();
	for( int i = n - 1; i >= 0; i -- )
		printf( "%d ", ans[i] - 1 );
	return 0;
}
