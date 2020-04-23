#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e5 + 5;

struct Trie
{
	int val, son[2];
} node[N];

int n, cnt, ans;

void Insert( int x, int u, int dep )
{
	bool k;
	for( int i = dep; i >= 0; i -- )
	{
		k = ( 1 << i ) & x;
		if( node[u].son[k] == -1 )
			node[u].son[k] = ++ cnt;
		u = node[u].son[k];
	}
	node[u].val = x;
	return ;
}

void Query( int x, int u, int dep )
{
	bool k;
	for( int i = dep; i >= 0; i -- )
	{
		k = ( 1 << i ) & x;
		if( node[u].son[!k] != -1 )
			u = node[u].son[!k];
		else
			u = node[u].son[k];
	}
	ans = max( ans, node[u].val ^ x );
	return ;
}

int main()
{
	while( ~scanf( "%d", &n ) )
	{
		ans = cnt = 0;
		memset( node, -1, sizeof( node ) );
		for( int i = 0, t; i < n; i ++ )
		{
			scanf( "%d", &t );
			Insert( t, 0, 31 );
			Query( t, 0, 31 );
		}
		printf( "%d\n", ans );
	}
	return 0;
}
