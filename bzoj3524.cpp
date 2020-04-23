#include	<cstdio>
#include	<cstdlib>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 5e5 + 5;
const	int M = 1e7 + 5;

int n, m, size, root[N];

inline int in()
{
	int k = 0, c = '\0';
	for(; c > '9' || c < '0';)
		c = getchar();
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

struct Node
{
	int lSon, rSon, val;
} node[M];

void Insert( int p, int &q, int l, int r, int x )
{
	q = ++ size;
	node[size] = node[p];
	node[size].val ++;
	if( l == r )
		return ;
	int mid = ( l + r ) >> 1;
	if( mid >= x )
		Insert( node[p].lSon, node[q].lSon, l, mid, x );
	else
		Insert( node[p].rSon, node[q].rSon, mid + 1, r, x );
	return ;
}

int Query( int L, int R, int k, int l, int r )
{
	if( l == r )
		return l;
	int mid = ( l + r ) >> 1;
	Node a = node[L], b = node[R];
	if( node[b.lSon].val - node[a.lSon].val > k )
		return Query( a.lSon, b.lSon, k, l, mid );
	if( node[b.rSon].val - node[a.rSon].val > k )
		return Query( a.rSon, b.rSon, k, mid + 1, r );
	return 0;
}

int main()
{
	n = in(), m = in();
	size = 0, root[0] = 0;
	for( int i = 1; i <= n; i ++ )
		Insert( root[i-1], root[i], 1, n, in() );
	for( int i = 1, l, r; i <= m; i ++ )
	{
		l = in(), r = in();
		if( l > r )
			swap( l, r );
		int q = ( r - l + 1 ) >> 1;
		int a = Query( root[l-1], root[r], q, 1, n );
		printf( "%d\n", a );
	}
	return 0;
}
