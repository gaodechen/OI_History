#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<map>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
const	int N = 1e5 + 5;
const	int K = 1e1 + 6;

int n, q, sig, head[N];
int size[N], dep[N], pre[N][K+1];

struct Edge
{
	int v, next;
} e[N+N];

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

void DFS( int u, int p )
{
	dep[u] = dep[p] + 1;
	size[u] = 1, pre[u][0] = p;
	for( int i = 1; i <= K; i ++ )
		pre[u][i] = pre[pre[u][i-1]][i-1];
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if( v != p )
		{
			DFS( v, u );
			size[u] += size[v];
		}
	}
	return ;
}

inline int Jump( int u, int d )
{
	for( int i = 0; i <= K; i ++ )
		if( d & ( 1 << i ) )
			u = pre[u][i];
	return u;
}

int LCA( int a, int b )
{
	if( dep[a] < dep[b] )
		swap( a, b );
	a = Jump( a, dep[a] - dep[b] );
	if( a == b )
		return a;
	for( int i = K; i >= 0; i -- )
	{
		if( pre[a][i] != pre[b][i] )
		{
			a = pre[a][i];
			b = pre[b][i];
		}
	}
	return pre[a][0];
}

inline int Compute( int a, int b )
{
	if( a == b )
		return n;
	if( dep[a] < dep[b] )
		swap( a, b );
	int lca = LCA( a, b );
	int dis = dep[a] - dep[lca] * 2 + dep[b];
	if( dis & 1 )
		return 0;
	dis >>= 1;
	int mid = Jump( a, dis );
	if( mid == lca )
	{
		int u = Jump( a, dis - 1 );
		int v = Jump( b, dis - 1 );
		return n - size[u] - size[v];
	}
	int u = Jump( a, dis - 1 );
	return size[mid] - size[u];
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
	DFS( 1, 1 );
	scanf( "%d", &q );
	for( int i = 0; i < q; i ++ )
	{
		int u, v, ans;
		scanf( "%d%d", &u, &v );
		ans = Compute( u, v );
		printf( "%d\n", ans );
	}
	return 0;
}
