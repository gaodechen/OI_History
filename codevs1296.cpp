#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int INF = 0x3f3f3f3f, N = 32768;

struct SplayTree
{
	struct Node
	{
		int key, val;
		Node *lson, *rson, *pre;
	};

	Node *root;
	Node pool[N], *tail;

	inline void Rotate( Node *x )
	{
		Node *b;
		Node *y = x -> pre;
		Node *z = y -> pre;
		if( y -> lson == x )
			b = x -> rson;
		else
			b = x -> lson;
		x -> pre = z;
		y -> pre = x;
		if( b )
			b -> pre = y;
		if( z )
		{
			if( z -> lson == y )
				z -> lson = x;
			else
				z -> rson = x;
		}
		if( x == y -> lson )
			x -> rson = y, y -> lson = b;
		else
			x -> lson = y, y -> rson = b;
		return ;
	}

	inline void Splay( Node *x, Node *target = NULL )
	{
		while( x -> pre != target )
		{
			if( x -> pre -> pre != target )
			{
				if( ( x -> pre -> pre -> lson == x -> pre ) == ( x -> pre -> lson == x ) )
					Rotate( x -> pre );
				else
					Rotate( x );
			}
			Rotate( x );
		}
		if( target == NULL )
			root = x;
		return ;
	}

	SplayTree()
	{
		root = NULL;
		tail = pool;
	}

	inline void Insert( var key, var val )
	{
		Node *f = NULL;
		Node *p  = root;
		Node **q = &root;
		while( p )
		{
			f = p;
			if( key < p -> key )
				q = &p -> lson, p = p -> lson;
			else
				q = &p -> rson, p = p -> rson;
		}
		p = tail ++;
		p -> key = key, p -> val = val;
		p -> pre = f;
		p -> lson = p -> rson = NULL;
		*q = p;
		Splay( p );
		return ;
	}

	inline Node *FindNode( var key )
	{
		Node *p = root;
		while( p )
		{
			if( key < p -> key )
				p = p -> lson;
			else if( key > p -> key )
				p = p -> rson;
			else
				break ;
		}
		return p;
	}

	inline int FindValue( var key )
	{
		Node *p = FindNode( key );
		Splay( p );
		return p -> val;
	}

	inline void Delete( var key )
	{
		Node *p = FindNode( key );
		Splay( p );
		if( !p -> lson && !p -> rson )
			root = NULL;
		else if( !p -> lson )
			root = p -> rson, root -> pre = NULL;
		else if( !p -> rson )
			root = p -> lson, root -> pre = NULL;
		else
		{
			Node *prev = p -> lson, *next = p -> rson;
			while( prev -> rson )
				prev = prev -> rson;
			while( next -> lson )
				next = next -> lson;
			Splay( prev );
			Splay( next, prev );
			next -> lson = NULL;
		}
	}

	inline int GetPrev( Node *u )
	{
		Node *p = u -> lson;
		if( !p )
			return INF;
		while( p -> rson )
			p = p -> rson;
		return p -> val;
	}

	inline int GetNext( Node *u )
	{
		Node *p = u -> rson;
		if( !p )
			return INF;
		while( p -> lson )
			p = p -> lson;
		return p -> val;
	}
};

inline int ABS( int x )
{
	return x > 0 ? x : -x;
}

int main()
{
	SplayTree tree;
	int n, x, ans;
	scanf( "%d%d", &n, &ans );
	tree.Insert( ans, ans );
	for( int i = 1; i < n; i ++ )
	{
		scanf( "%d", &x );
		tree.Insert( x, x );
		int a = tree.GetPrev( tree.root );
		int b = tree.GetNext( tree.root );
		ans += min( ABS( x - a ), ABS( b - x ) );
	}
	printf( "%d\n", ans );
	return 0;
}
