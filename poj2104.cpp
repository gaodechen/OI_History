#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e5 + 5;
const	int M = 3e6 + 5;

inline int in()
{
	int k = 0, c = '\0';
	for( ; c > '9' || c < '0'; )
		c = getchar();
	for( ; c >= '0' && c <= '9'; )
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

struct Node
{
	int l, r, val;
} node[M];

int n, T, tot, arr[N], d[N], root[N];

void Insert( int &x, int p, int k, int l, int r )
{
	x = ++ tot;
	node[x] = node[p];
	node[x].val ++;
	if( l == r )
		return ;
	int mid = ( l + r ) >> 1;
	if( k <= mid )
		Insert( node[x].l, node[p].l, k, l, mid );
	else
		Insert( node[x].r, node[p].r, k, mid + 1, r );
	return ;
}

int Query( int p, int q, int l, int r, int k )
{
	if( l == r )
		return l;
	int mid = (l + r) >> 1, t;
	Node a = node[p], b = node[q];
	t = node[b.l].val - node[a.l].val;
	if( t >= k )
		return Query( a.l, b.l, l, mid, k );
	return Query( a.r, b.r, mid + 1, r, k - t );
}

int main(int argc, char **argv)
{
	while( scanf( "%d%d", &n, &T ) == 2 )
	{
		tot = 0;
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%d", &arr[i] );
			d[i] = arr[i];
		}
		sort( d + 1, d + n + 1 );
		for( int i = 1; i <= n; i ++ )
			arr[i] = lower_bound( d + 1, d + n + 1, arr[i] ) - d;
		root[0] = 0;
		for( int i = 1; i <= n; i ++ )
			Insert( root[i], root[i - 1], arr[i], 1, n );
		while( T -- )
		{
			int l, r, c;
			scanf("%d%d%d", &l, &r, &c);
			int x = Query(root[l - 1], root[r], 1, n, c);
			printf("%d\n", d[x]);
		}
	}
	return 0;
}
