#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 1e5 + 5;
const	int M = 2e5 + 5;

inline int in()
{
	int k = 0, c = '\0';
	for( ; c > '9' || c < '0'; )
		c = getchar();
	for( ; c >= '0' && c <= '9'; )
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

struct Edge
{
	int v, next;
} e[M+M];

int n, m, q, ind, sig, bridge;
int pre[N], dfn[N], low[N], head[N], father[N];

int Find( int u )
{
	if( father[u] != u )
		father[u] = Find( father[u] );
	return father[u];
}

inline bool Union( int u, int v )
{
	u = Find( u );
	v = Find( v );
	if( u != v )
	{
		father[v] = u;
		return true;
	}
	return false;
}

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

void Tarjan( int u, int p )
{
	pre[u] = p, dfn[u] = low[u] = ++ ind;
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if( v == p )
			continue ;
		if( !dfn[v] )
		{
			Tarjan( v, u );
			low[u] = min( low[u], low[v] );
			if( dfn[u] < low[v] )
				bridge ++;
			else
				Union( u, v );
		}
		else
			low[u] = min( low[u], dfn[v] );
	}
	return ;
}

/* inline void LCA( int u, int v )
{
	if( dfn[u] > dfn[v] )
		swap( u, v );
	while( dfn[u] < dfn[v] )
	{
		if( Union( v, pre[v] ) )
			bridge --;
		v = pre[v];
	}
	while( u != v )
	{
		if( Union( u, pre[u] ) )
			bridge --;
		u = pre[u];
	}
	return ;
} */

inline int Climb( int u )
{
	bridge --;
	Union( Find( pre[u] ), u );
	return Find( u );
}

inline void LCA( int u, int v )
{
	while( u != v )
	{
		if( dfn[u] > dfn[v] )
			u = Climb( u );
		else
			v = Climb( v );
	}
	return ;
}

int main()
{
	freopen( "in", "r", stdin );
	int c = 0;
	while( scanf( "%d%d", &n, &m ) && n )
	{
		set( head, 0 );
		ind = sig = bridge = 0;
		set( dfn, 0 ), set( low, 0 );
		for( int i = 1; i <= n; i ++ )
			father[i] = i;
		for( int i = 0; i < m; i ++ )
		{
			int u, v;
			u = in(), v = in();
			AddEdge( u, v );
			AddEdge( v, u );
		}
		for( int i = 1; i <= n; i ++ )
			if( !dfn[i] )
				Tarjan( i, 0 );
		q = in();
		printf( "Case %d:\n", ++ c );
		for( int i = 0; i < q; i ++ )
		{
			int u, v;
			u = in(), v = in();
			u = Find( u ), v = Find( v );
			if( u != v )
				LCA( u, v );
			printf( "%d\n", bridge );
		}
		printf( "\n" );
	}
	return 0;
}
