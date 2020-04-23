#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 1e4 + 5, M = 2e4 + 5;

struct Set
{
	int n, pre[N];

	inline void Init( int x )
	{
		n = x;
		for( int i = 1; i <= n; i ++ )
			pre[i] = i;
		return ;
	}

	inline int Find( int u )
	{
		if( u != pre[u] )
			pre[u] = Find( pre[u] );
		return pre[u];
	}

	inline void Union( int u, int v )
	{
		pre[Find(v)] = Find( u );
		return ;
	}

} atom;

struct Edge
{
	int v, next;
} e[M];

int c, n, m, num, sig, head[N], x[M], y[M], in[N];

void TopoSort()
{
	queue< int > q;
	for( int i = 1; i <= n; i ++ )
	{
		int p = atom.Find( i );
		if( i == p && in[p] == 0 )
			q.push( i );
	}
	bool only = true;
	while( !q.empty() )
	{
		if( q.size() > 1 )
			only = false;
		num --;
		int u = q.front(); q.pop();
		for( int i = head[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( -- in[v] == 0 )
				q.push( v );
		}
	}
	// When num == 1, it maybe legal
	// For there maybe repeated edges or only given one vertex
	// For this disturbing problem, we should judge for edges like (u, u) specially...
	if( num > 1 )
		printf( "CONFLICT\n" );
	else if( !only )
		printf( "UNCERTAIN\n" );
	else
		printf( "OK\n" );
	return ;
}

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		num = n, set( G, 0 );
		set( x, 0 ), set( y, 0 ), set( in, 0 );
		sig = 0, set( head, 0 ), atom.Init( n );
		for( int i = 0; i < m; i ++ )
		{
			int u, v; char buf[2];
			scanf( "%d%s%d", &u, buf, &v );
			u ++, v ++;
			if( buf[0] == '>' )
				x[i] = u, y[i] = v;
			else if( buf[0] == '<' )
				x[i] = v, y[i] = u;
			else
			{
				atom.Union( u, v );
				num --;
			}
		}
		bool flag = true;
		for( int i = 0; i < m; i ++ )
		{
			if( x[i] && y[i] )
			{
				int u = atom.Find( x[i] );
				int v = atom.Find( y[i] );
				AddEdge( u, v );
				if( u == v )
					flag = false;
			}
		}
		if( !flag )
		{
			printf( "CONFLICT\n" );
			continue ;
		}
		TopoSort();
	}
	return 0;
}
