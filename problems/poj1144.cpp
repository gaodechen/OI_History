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

bool mark[N];
int dfn[N], low[N];
int n, sig, ind, head[N];

inline void Init()
{
	sig = ind = 0;
	set( dfn, 0 ), set( low, 0 );
	set( mark, 0 ), set( head, 0 );
	return ;
}

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

void Tarjan( int u )
{
	int son = 0;
	low[u] = dfn[u] = ++ ind;
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
        // if(v == p) continue ;
		if( !dfn[v] )
		{
			son ++;
			Tarjan( v );
			if((u == 1 && son > 1) || (u != 1 && dfn[u] <= low[v]))
				mark[u] = 1;
			low[u] = min( low[u], low[v] );
		}
		else
			low[u] = min( low[u], dfn[v] );
	}
	return ;
}

int main()
{
	while( scanf( "%d", &n ) && n )
	{
		Init();
		int u, v;
		while( scanf( "%d", &u ) && u )
		{
			while( getchar() != '\n' )
			{
				scanf( "%d", &v );
				AddEdge( u, v );
				AddEdge( v, u );
			}
		}
		Tarjan( 1 );
		int ans = 0;
		for( int i = 1; i <= n; i ++ )
			if( mark[i] )
				ans ++;
		printf( "%d\n", ans );
	}
	return 0;
}
