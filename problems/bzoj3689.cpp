#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e5 + 5;

struct Trie
{
	int size;
	Trie *son[2];
	Trie();
};

Trie *null = new Trie;
Trie *root = null;

Trie :: Trie()
{
	son[0] = son[1] = null;
	size = 0;
}

int n, k;

int main()
{
	freopen( "in", "r", stdin );
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ )
	{
		scanf( "%d", &a[i] );
		Insert( root, a[i] );
	}
	return 0;
}
