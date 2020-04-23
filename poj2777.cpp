#include	<cstdio>
#include	<iostream>

#define		lSon( p )		p + p
#define		rSon( p )		p + p + 1
#define		MID( l, r )		( l + r ) >> 1

using	namespace	std;
const	int N = 1e5 + 5;

struct Node
{
	int l, r;
	int val, mark;
} node[N*4];

void BuildTree( int l, int r, int k )
{
	Node &p = node[k];
	p.mark = 0;
	p.l = l, p. r = r;
	if( l == r )
		p.val = 1;
	else
	{
		int mid = MID( l, r );
		BuildTree( l, mid, lSon( k ) );
		BuildTree( mid + 1, r, rSon( k ) );
	}
	return ;
}

inline Node MergeNode( Node &a, Node &b )
{
	Node res;
	res.l = a.l, res. r = b.r;
	res.mark = 0, res.val = ( a.val | b.val );
	return res;
}

void PushDown( int k )
{
	Node &p = node[k];
	if( p.mark )
	{
		Node &ls = node[lSon(k)];
		Node &rs = node[rSon(k)];
		ls.mark = rs.mark = p.mark;
		ls.val = rs.val = ( 1 << ( p.mark - 1 ) );
		p.mark = 0;
	}
	return ;
}

void Modify( int l, int r, int c, int k )
{
	Node &p = node[k];
	if( p.l >= l && p.r <= r )
	{
		p.mark = c;
		p.val = ( 1 << ( c - 1 ) );
		return ;
	}
	int mid = MID( p.l, p.r );
	PushDown( k );
	if( r <= mid )
		Modify( l, r, c, lSon( k ) );
	else if( l > mid )
		Modify( l, r, c, rSon( k ) );
	else
	{
		Modify( l, mid, c, lSon( k ) );
		Modify( mid + 1, r, c, rSon( k ) );
	}
	p = MergeNode( node[lSon(k)], node[rSon(k)] );
	return ;
}

int Query( int l, int r, int k )
{
	Node &p = node[k];
	if( p.l >= l && p.r <= r )
		return p.val;
	int mid = MID( p.l, p.r ), res;
	PushDown( k );
	if( r <= mid )
		res = Query( l, r, lSon( k ) );
	else if( l > mid )
		res = Query( l, r, rSon( k ) );
	else
		res = Query( l, mid, lSon( k ) ) | Query( mid + 1, r, rSon( k ) );
	return res;
}

inline int Sum( int k )
{
	int res;
	for( res = 0; k; res ++ )
		k &= ( k - 1 );
	return res;
}

int l, t, o;

int main()
{
	while( scanf( "%d%d%d", &l, &t, &o ) == 3 )
	{
		BuildTree( 1, l, 1 );
		for( int i = 1; i <= o; i ++ )
		{
			char buf[1];
			int l, r, c;
			scanf( "%s%d%d", buf, &l, &r );
			if( l > r )
				swap( l, r );
			if( buf[0] == 'C' )
			{
				scanf( "%d", &c );
				Modify( l, r, c, 1 );
			}
			else
			{
				int ans = Query( l, r, 1 );
				printf( "%d\n", Sum( ans ) );
			}
		}
	}
	return 0;
}
