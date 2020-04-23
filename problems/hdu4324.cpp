#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
typedef const int & var;
const	int N = 2001;

struct SCC
{
	bool ins[N];
	int stack[N], dfn[N], low[N], mark[N];
	int n, sig, top, cnt, index, head[N], size[N];

	struct Edge
	{
		int v, next;
	} e[N*N/2];

	inline void AddEdge( var u, var v )
	{
		e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
		return ;
	}
	
	inline void Init( int x )
	{
		top = cnt = index = 0, n = x;
		sig = 0, set( head, 0 );
		set( dfn, 0 ), set( low, 0 );
		return ;
	}

	void DFS( int u )
	{
		dfn[u] = low[u] = ++ index;
		stack[++top] = u, ins[u] = 1;
		for( int i = head[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( !dfn[v] )
			{
				DFS( v );
				low[u] = min( low[u], low[v] );
			}
			else if( ins[v] )
				low[u] = min( low[u], dfn[v] );
		}
		if( dfn[u] == low[u] )
		{
			int v;
			cnt ++;
			do
			{
				v = stack[top--];
				ins[v] = 0;
				mark[v] = cnt;
			}
			while( u != v && top );
		}
		return ;
	}

	inline void Tarjan()
	{
		for( int i = 1; i <= n; i ++ )
			if( !dfn[i] )
				DFS( i );
		return ;
	}

	inline void Interface( int c )
	{
		Tarjan();
		set( size, 0 );
		for( int i = 1; i <= n; i ++ )
			size[mark[i]] ++;
		bool flag = false;
		for( int i = 1; i <= cnt; i ++ )
		{
			if( size[i] >= 3 )
			{
				flag = true;
				break ;
			}
		}
		printf( "Case #%d: ", c );
		if( flag )
			printf( "Yes\n" );
		else
			printf( "No\n" );
		return ;
	}

} g;

int t, n;

int  main()
{
	scanf( "%d", &t );
	for( int c = 1; c <= t; c ++ )
	{
		scanf( "%d", &n );
		g.Init( n );
		for( int i = 1; i <= n; i ++ )
		{
			char buf[N];
			scanf( "%s", buf + 1 );
			for( int j = 1; j <= n; j ++ )
				if( buf[j] == '1' )
					g.AddEdge( i, j );
		}
		g.Interface( c );
	}
	return 0;
}
