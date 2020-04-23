#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		seg		root -> son[1] -> son[0]

using	namespace	std;
typedef	long long	data;
const	int N = 1e5 + 5;

struct Node
{
	Node *son[2], *pre;
	int add, val, size;
	data sum;

	void PushDown()
	{
		if( add == 0 )
			return ;
		for( int i = 0; i < 2; i ++ )
		{
			if( !son[i] )
				continue ;
			son[i] -> add += add, son[i] -> val += add;
			son[i] -> sum += ( data )add * son[i] -> size;
		}
		add = 0;
		return ;
	}

	void PushUp()
	{
		size = son[0] -> size + son[1] -> size + 1;
		sum = val + add + son[0] -> sum + son[1] -> sum;
		return ;
	}
};

Node node[N], *root;
Node *null = &node[0];

struct SplayTree
{
	int top, a[N];

	void Rotate( Node *x, int c )
	{
		Node *y = x -> pre, *z = y -> pre;
		y -> PushDown(), x -> PushDown();
		y -> son[!c] = x -> son[c];
		x -> son[c] -> pre = y;
		x -> pre = z;
		z -> son[z->son[1]==y] = x;
		x -> son[c] = y;
		y -> pre = x;
		y -> PushUp();
		return ;
	}

	void Splay( Node *x, Node *target = null )
	{
		while( x -> pre != target )
		{
			if( x -> pre -> pre == target )
				Rotate( x, x -> pre -> son[0] == x );
			else
			{
				Node *y = x -> pre, *z = y -> pre;
				int f = z -> son[1] == y;
				if( y -> son[f] == x )
					Rotate( y, !f ), Rotate( x, !f );
				else
					Rotate( x, f ), Rotate( x, !f );
			}
		}
		x -> PushUp();
		if( target == null )
			root = x;
		return ;
	}

	void RotateTo( int k, Node *target )
	{
		Node *x = root;
		x -> PushDown();
		while( x -> son[0] -> size != k)
		{
			if( x -> son[0] -> size > k )
				x = x -> son[0];
			else
			{
				k -= x -> son[0] -> size + 1;
				x = x -> son[1];
			}
			x -> PushDown();
		}
		Splay( x, target );
		return ;
	}

	Node *NewNode( Node *f, int c )
	{
		Node *x = &node[++top];
		x -> val = x -> sum = c;
		x -> son[0] = x -> son[1] = null;
		x -> size = 1, x -> add = 0, x -> pre = f;
		return x;
	}

	void Build( Node* &x, int l, int r, Node *f )
	{
		if( l > r )
			return ;
		int mid = ( l + r ) >> 1;
		x = NewNode( f, a[mid] );
		Build( x -> son[0], l, mid - 1, x );
		Build( x -> son[1], mid + 1, r, x );
		x -> PushUp();
	}

	void Init( int n )
	{
		top = 0;
		root = NewNode( null, -1 );
		root -> son[1] = NewNode( root, -1 );
		for( int i = 0; i < n; i ++ )
			scanf( "%d", &a[i] );
		Build( seg, 0, n - 1, root -> son[1] );
		root -> son[1] -> PushUp();
		root -> PushUp();
		return ;
	}

	void Update()
	{
		int l, r, c;
		scanf( "%d%d%d", &l, &r, &c );
		RotateTo( l - 1, null );
		RotateTo( r + 1, root );
		seg -> add += c, seg -> val += c;
		seg -> sum += ( data )c * seg -> size;
	}

	void Query()
	{
		int l, r;
		scanf( "%d%d", &l, &r );
		RotateTo( l - 1, null );
		RotateTo( r + 1, root );
		printf( "%lld\n", seg -> sum );
		return ;
	}
} tree;

int main()
{
	int n, m;
	char s[2];
	scanf( "%d%d", &n, &m );
	tree.Init( n );
	while( m -- )
	{
		scanf( "%s", s );
		if( s[0] == 'Q' )
			tree.Query();
		else
			tree.Update();
	}
	return 0;
}

