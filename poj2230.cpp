#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e4 + 5;
const	int M = 5e4 + 5;

int n, m, sig, head[N], vis[M*2];

struct Edge
{
	int v, next;
} e[M*2];

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

inline int F( int i )
{
	return ( ( i - 1 ) ^ 1 ) + 1;
}

void DFS( int u )
{
	for( int i = head[u]; i; i = e[i].next )
	{
		if( !vis[i] )
		{
			vis[i] = 1;
			DFS( e[i].v );
		}
	}
	printf( "%d\n", u );
	return ;
}

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 0, u, v; i < m; i ++ )
	{
		scanf( "%d%d", &u, &v );
		AddEdge( u, v );
		AddEdge( v, u );
	}
	DFS( 1 );
	return 0;
}
