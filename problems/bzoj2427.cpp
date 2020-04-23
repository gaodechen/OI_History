#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 105, M = 505;

struct Edge
{
	int sig, head[N];

	inline void Init()
	{
		sig = 0;
		set( head, 0 );
		return ;
	}

	inline void AddEdge( int u, int v )
	{
		e[++sig].v = v;
		e[sig].next = head[u];
		head[u] = sig;
		return ;
	}

	struct Item
	{
		int v, next;
	} e[M];
};

struct SCC
{
	bool vis[N];
	Edge edge, tree;
	int n, m, top, ont, index;
	int W[N], V[N], in[N], d[N][M];
	int mark[N], dfn[N], low[N], stack[N], val[N], cost[N];

	inline void Init( int x, int y )
	{
		n = x, m = y;
		top = ont = index = 0;
		edge.Init(), tree.Init();
		set( in, 0 ), set( dfn, 0 );
		set( low, 0 ), set( vis, 0 );
		set( val, 0 ), set( cost, 0 );
		set( d, 0 ), set( stack, 0 );
		return ;
	}

	void DFS( int u )
	{
		dfn[u] = low[u] = ++ index;
		stack[++top] = u, vis[u] = 1;
		for( int i = edge.head[u]; i; i = edge.e[i].next )
		{
			int &v = edge.e[i].v;
			if( !dfn[v] )
			{
				DFS( v );
				low[u] = min( low[u], low[v] );
			}
			else if( vis[v] )
				low[u] = min( low[u], dfn[v] );
		}
		if( dfn[u] == low[u] )
		{
			int v;
			ont ++;
			do
			{
				v = stack[top--];
				vis[v] = 0;
				mark[v] = ont;
				val[ont] += V[v];
				cost[ont] += W[v];
			}
			while( u != v && top );
		}
		return ;
	}

	void Tarjan()
	{
		for( int i = 1; i <= n; i ++ )
			if( !dfn[i] )
				DFS( i );
		return ;
	}
	void Dynamic( int u )
	{
		for( int i = tree.head[u]; i; i = tree.e[i].next )
		{
			int &v = tree.e[i].v;
			Dynamic( v );
			for( int j = m - cost[u]; j >= 0; j -- )
				for( int k = 0; k <= j; k ++ )
					d[u][j] = max( d[u][j], d[u][k] + d[v][j-k] );
		}
		for( int j = m; j >= 0; j -- )
		{
			if( j >= cost[u] )
				d[u][j] = d[u][j-cost[u]] + val[u];
			else
				d[u][j] = 0;
		}
		return ;
	}

	int Interface()
	{
		for( int i = 1, pre; i <= n; i ++ )
		{
			scanf( "%d", &pre );
			edge.AddEdge( pre, i );
		}
		Tarjan();
		for( int u = 1; u <= n; u ++ )
		{
			for( int i = edge.head[u]; i; i = edge.e[i].next )
			{
				if( mark[u] != mark[edge.e[i].v] )
				{
					tree.AddEdge( mark[u], mark[edge.e[i].v] );
					in[mark[edge.e[i].v]] ++;
				}
			}
		}
		for( int i = 1; i <= ont; i ++ )
			if( in[i] == 0 )
				tree.AddEdge( ont + 1, i );
		Dynamic( ont + 1 );
		return d[ont+1][m];
	}
} g;

int main()
{
	int n, m;
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &g.W[i] );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &g.V[i] );
	g.Init( n, m );
	printf( "%d\n", g.Interface() );
	return 0;
}
