#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 5e2 + 5;

struct Edge
{
	int v, next;
} e[N+N];

bool cut[N];
int n, ind, sig, cnt, head[N];
int low[N], dfn[N], bcc[N], size[N];

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

void Tarjan( int u, int p )
{
	int son = 0;
	dfn[u] = low[u] = ++ ind;
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if( !dfn[v] )
		{
			son ++;
			Tarjan( v, u );
			if( dfn[u] <= low[v] && p != 0 )
				cut[u] = 1;
			low[u] = min( low[u], low[v] );
		}
		else
			low[u] = min( low[u], dfn[v] );
	}
	if( p == 0 && son > 1 )
		cut[u] = 1;
	return ;
}

void DFS( int u )
{
	low[u] = 1, size[cnt] ++;
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if(!low[v])
		{
			if( !cut[v] )
				DFS( v );
			else if( bcc[v] != cnt )
				bcc[v] = cnt, dfn[cnt] ++;
		}
	}
	return ;
}

int main()
{
	int c = 0, m;
	while( scanf( "%d", &m ) && m )
	{
		n = sig = ind = cnt = 0;
		set( low, 0 ), set( cut, 0 );
		set( head, 0 ), set( dfn, 0 );
		for( int i = 0, u, v; i < m; i ++ )
		{
			scanf( "%d%d", &u, &v );
			AddEdge( u, v );
			AddEdge( v, u );
			n = max( max( u, v ), n );
		}
		for( int i = 1; i <= n; i ++ )
			if( !dfn[i] )
				Tarjan( i, 0 );
		set( low, 0 ), set( bcc, 0 );
		set( dfn, 0 ), set( size, 0 );
        // low = vis...
		for( int i = 1; i <= n; i ++ )
			if( !cut[i] && !low[i] )
				cnt ++, DFS( i );
		int tot = 0;  long long ans = 1;
		if( cnt == 1 )
			tot = 2, ans = ( long long ) n * ( n - 1 ) / 2;
		else
		{
			for( int i = 1; i <= cnt; i ++ )
				if( dfn[i] == 1 )
					tot ++, ans *= ( long long ) size[i];
			// We don't go on DFS() when v is a cut vertex
			// So here ans *= size[i]
		}
		printf( "Case %d: %d %lld\n", ++ c, tot, ans );
	}
	return 0;
}
