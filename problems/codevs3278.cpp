#include	<cstdio>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 2e5 + 5;
const	int M = 1e4 + 7;

int n, sig, head[N], val[N], ans1, ans2;

struct Edge
{
	int v, next;
} e[N*2];

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

void DFS( int u, int p, int a, int b )
{
	int sum = 0, tmp = val[p];
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if( v != p )
		{
			DFS( v, u, ( val[p] + sum ) % M, tmp );
			sum += val[v];
			tmp = max( tmp, val[v] );
		}
	}
	ans1 = max( ans1, b * val[u] );
	ans2 = ( ans2 + val[u] * a % M ) % M;
	return ;
}

int main()
{
	scanf( "%d", &n );
	for( int i = 1; i < n; i ++ )
	{
		int u, v;
		scanf( "%d%d", &u, &v );
		AddEdge( u, v );
		AddEdge( v, u );
	}
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &val[i] );
	DFS( 1, 0, 0, 0 );
	ans2 = ( ans2 + ans2 ) % M;
	printf( "%d %d\n", ans1, ans2 );
	return 0;
}
