#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int N = 1e5 + 5;
const	int INF = 0x3f3f3f3f;

int n, g, sig, cnt, ans, head[N], list[N];

inline int Read()
{
	int res = 0, c;
	for( c = getchar(); c > '9' && c < '0'; )
		c = getchar();
	res = c - '0';
	for( ; c <= '9' && c >= '0'; c = getchar() )
		res = res * 10 + c - '0';
	return res;
}

struct Edge
{
	int v, w, next;
} e[N*2];

inline void AddEdge( int u, int v, int w )
{
	e[++sig].v = v, e[sig].w = w;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

void DFS( int u, int p, int k )
{
	list[g++] = k;
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if( v != p )
			DFS( v, u, k ^ e[i].w );
	}
	return ;
}

struct Trie
{
	int val, son[2];
} node[N*30];

void Insert( int x, int u, int dep )
{
	bool k;
	for( int i = dep; i >= 0; i -- )
	{
		k = x & ( 1 << i );
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
		k = x & ( 1 << i );
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
	set( node, -1 );
	for( int i = 1; i < n; i ++ )
	{
		int u, v, w;
		scanf( "%d%d%d", &u, &v, &w );
		AddEdge( u, v, w );
		AddEdge( v, u, w );
	}
	DFS( 1, 1, 0 );
	for( int i = 0; i < g; i ++ )
	{
		Insert( list[i], 0, 30 );
		Query( list[i], 0, 30 );
	}
	printf( "%d\n", ans );
	return 0;
}
