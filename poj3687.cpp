#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>
#include	<vector>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int INF = 0x3f3f3f3f;
const	int N = 201, M = 40001;

vector< int > list;
int t, n, m, sig, head[N], in[N], ans[N];

struct Edge
{
	int v, next;
} e[M];

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

inline void TopoSort()
{
	priority_queue< int, vector< int >, less< int > > q;
	for( int i = 1; i <= n; i ++ )
		if( in[i] == 0 )
			q.push( i );
	while( !q.empty() )
	{
		int u = q.top(); q.pop();
		list.push_back( u );
		for( int i = head[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( -- in[v] == 0 )
				q.push( v );
		}
	}
	bool flag = true;
	for( int i = 1; i <= n; i ++ )
		if( in[i] > 0 )
			flag = false;
	if( flag )
	{
		// The problem asks for the position for every vertex...
		for( int i = ( int )list.size() - 1, j = 1; i >= 0; i --, j ++ )
			ans[list[i]] = j;
		for( int j = 1; j <= n; j ++ )
			printf( "%d ", ans[j] );
	}
	else
		printf( "-1" );
	printf( "\n" );
	return ;
}

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		sig = 0;
		list.clear();
		set( head, 0 ), set( in, 0 );
		scanf( "%d%d", &n, &m );
		for( int i = 0; i < m; i ++ )
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			AddEdge( v, u );
			in[u] ++;
		}
		TopoSort();
	}
	return 0;
}
