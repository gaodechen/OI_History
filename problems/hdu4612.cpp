// #pragma comment(linker, "/STACK:1024000000,1024000000")
#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
const	int N = 2e5 + 5;
const	int M = 1e6 + 5;

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

int *vis, *d, n, m, ind, sig, dis, bridge;
int dfn[N], low[N], head[N], head_[N], pre[N];

struct Edge
{
	int v, next;
} e[M+M], e_[M+M];

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

inline int Find( int u )
{
	while( u != pre[u] )
	{
		int t = pre[u];
		pre[u] = pre[t];
		u = t;
	}
	return pre[u];
}

inline void Union( int u, int v )
{
	pre[Find(v)] = Find( u );
	return ;
}

void Tarjan( int u, int p )
{
	int cnt = 0;
	dfn[u] = low[u] = ++ ind;
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if( !cnt && v == p ) {
			cnt ++; continue ;
		}
		if( !dfn[v] )
		{
			Tarjan( v, u );
			low[u] = min( low[u], low[v] );
			if(dfn[u] < low[v])
				bridge ++;
			else
				Union( u, v );
		}
		else
			low[u] = min( low[u], dfn[v] );
	}
	return ;
}

int DFS( int u, int p )
{
	vis[u] = 1;
	int max1 = 0, max2 = 0;
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if( v == p || vis[v] )
			continue ;
		int tmp = DFS( v, u ) + 1;
		if( max1 < tmp )
			max2 = max1, max1 = tmp;
		else if( max2 < tmp )
			max2 = tmp;
	}
	dis = max( dis, max1 + max2 );
	return max1;
}

int main()
{
	while( true )
	{
		n = in(), m = in();
		if( n == 0 )
			break ;
		set( head, 0 ), set( dfn, 0 );
		ind = sig = bridge = 0, set( low, 0 );
		for( int i = 1; i <= n; i ++ )
			pre[i] = i;
		for( int i = 0; i < m; i ++ )
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			AddEdge( u, v );
			AddEdge( v, u );
		}
		Tarjan( 1, 0 );
		for( int i = 1; i <= n; i ++ )
			pre[i] = Find( i );
		cpy( head_, head ), cpy( e_, e );
		sig = 0, set( head, 0 );
		for( int u = 1; u <= n; u ++ )
		{
			for( int i = head_[u]; i; i = e_[i].next )
			{
				int v = e_[i].v;
				if( pre[u] != pre[v] )
				{
					AddEdge( pre[u], pre[v] );
					AddEdge( pre[v], pre[u] );
				}
			}
		}
		dis = 0, vis = low;
		set( low, 0 );
		DFS( pre[1], 0 );
		printf( "%d\n", bridge - dis );
	}
	return 0;
}
