#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 1e3 + 5;
const	int M = 1e6 + 5;

struct Edge
{
	int v, next;
} e[M];

int n, sig, ind, head[N];
int dfn[N], low[N], sum[N];

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

void Tarjan( int u )
{
	low[u] = dfn[u] = ++ ind;
	for(int i = head[u]; i; i = e[i].next)
	{
		int v = e[i].v;
		if(!dfn[v])
		{
			Tarjan(v);
			low[u] = min(low[u], low[v]);
			if(dfn[u] <= low[v])
				sum[u] ++;
		}
		else
			low[u] = min(low[u], dfn[v]);
	}
	return ;
}

int main()
{
	freopen( "in", "r", stdin );
	int u, v, c = 0;
	while( scanf( "%d", &u ) == 1 && u )
	{
		set( dfn, 0 ), set( low, 0 );
		n = ind = sig = 0, set( head, 0 );
		do
		{
			scanf( "%d", &v );
			AddEdge( u, v );
			AddEdge( v, u );
			n = max( max( u, v ), n );
		}
		while( scanf( "%d", &u ) && u );
		for( int i = 1; i <= n; i ++ )
			sum[i] = 1;
		sum[1] = 0;
		Tarjan(1);
		printf("Network #%d\n", ++ c);
		bool tmp = false;
		for( int i = 1; i <= n; i ++ )
		{
			if(sum[i] > 1)
			{
				printf("  SPF node %d leaves %d subnets\n", i, sum[i]);
				tmp = true;
			}
		}
		if(!tmp)
			printf("  No SPF nodes\n");
		printf( "\n" );
	}
	return 0;
}
