#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
const	int INF = 0x3f3f3f3f;
const	int N = 151, M = 10001;

struct SCC
{
	bool vis[N];
	int n, sig, top, ont, ind, head[N];
	int mark[N], dfn[N], low[N], stack[N], in[N], out[N];

	struct Edge
	{
		int v, next;
	} e[M];

	inline void Init()
	{
		sig = top = ont = ind = 0;
		set( out, 0 ), set( in, 0 );
		set( low, 0 ), set( dfn, 0 );
		set( vis, 0 ), set( stack, 0 );
		set( head, 0 ), set( mark, 0 );
		return ;
	}

	inline void AddEdge( int u, int v )
	{
		e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
		return ;
	}

	void DFS( int u )
	{
		dfn[u] = low[u] = ++ ind;
		stack[++top] = u, vis[u] = 1;
		for( int i = head[u]; i; i = e[i].next )
		{
			int &v = e[i].v;
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
				mark[v] = ont;
				vis[v] = 0;
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

	void Interface()
	{
		Tarjan();
		for( int u = 1; u <= n; u ++ )
		{
			for( int i = head[u]; i; i = e[i].next )
			{
				if( mark[u] != mark[e[i].v] )
				{
					out[mark[u]] ++;
					in[mark[e[i].v]] ++;
				}
			}
		}
		if( ont == 1 )
		{
			printf( "1\n0\n" );
			return ;
		}
		int t1 = 0, t2 = 0;
		for( int i = 1; i <= ont; i ++ )
		{
			if( in[i] == 0 )
				t1 ++;
			if( out[i] == 0 )
				t2 ++;
		}
		printf( "%d\n%d\n", t1, max( t1, t2 ) );
		return ;
	}

} g;

int main()
{
	scanf( "%d", &g.n );
	g.Init();
	for( int u = 1, v; u <= g.n; u ++ )
		while( scanf( "%d", &v ) == 1 && v )
			g.AddEdge( u, v );
	g.Interface();
	return 0;
}
