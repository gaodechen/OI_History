#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		lSon( k )		k + k
#define		rSon( k )		k + k + 1

using	namespace	std;
const	int N = 201, M = 201;

int n;
double v[N];

struct Interval
{
	int w;
	double l, r, h;

	Interval( double l = 0.0, double r = 0.0, double h = 0.0, int w = 1 )
	{
		this -> l = l, this -> r = r;
		this -> h = h, this -> w = w;
	}

	bool operator < ( const Interval &b ) const
	{
		return h < b.h;
	}
} e[N];

struct Node
{
	double len;
	int l, r, cnt;
} node[M*4];

void BuildTree( int k, int l, int r )
{
	Node *p = &node[k];
	p -> l = l, p -> r = r;
	p -> cnt = 0, p -> len = 0.0;
	if( l != r )
	{
		int mid = ( l + r ) >> 1;
		BuildTree( lSon( k ), l, mid );
		BuildTree( rSon( k ), mid + 1, r );
	}
	return ;
}

void Maintain( int k )
{
	Node *p = &node[k];
	if( p -> cnt )
		p -> len = v[p->r] - v[p->l-1];
	else if( p -> l == p -> r )
		p -> len = 0.0;
	else
		p -> len = node[lSon(k)].len + node[rSon(k)].len;
	return ;
}

void Update( int k, int l, int r, int w )
{
	Node *p = &node[k];
	int mid = ( p -> l + p -> r ) >> 1;
	if( p -> l == l && p -> r == r )
		p -> cnt += w;
	else
	{
		if( r <= mid )
			Update( lSon( k ), l, r, w );
		else if( l > mid )
			Update( rSon( k ), l, r, w );
		else
		{
			Update( lSon( k ), l, mid, w );
			Update( rSon( k ), mid + 1, r, w );
		}
	}
	Maintain( k );
	return ;
}

int main()
{
	freopen( "in", "r", stdin );
	int c = 0;
	while( scanf( "%d", &n ) && n )
	{
		for( int i = 1; i <= n; i ++ )
		{
			double x, y, a, b;
			scanf( "%lf%lf%lf%lf", &x, &y, &a, &b );
			e[i+i] = Interval( x, a, y, 1 );
			e[i+i-1] = Interval( x, a, b, -1 );
			v[i+i-1] = x, v[i+i] = a;
		}
		sort( e + 1, e + n + n + 1 );
		sort( v + 1, v + n + n + 1 );
		int tot = unique( v + 1, v + n + n + 1 ) - v - 1;
		BuildTree( 1, 1, tot );
		double res = 0.0;
		for( int i = 1; i <= n + n; i ++ )
		{
			int w, l, r;
			w = e[i].w;
			l = lower_bound( v + 1, v + tot + 1, e[i].l ) - v + 1;
			r = lower_bound( v + 1, v + tot + 1, e[i].r ) - v;
			res += node[1].len * ( e[i].h - e[i-1].h );
			Update( 1, l, r, w );
		}
		printf( "Test case #%d\nTotal explored area: %.2lf\n\n", ++ c, res );
	}
	return 0;
}
