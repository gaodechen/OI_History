#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<stack>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int N = 1e5 + 5;
const	int INF = 0x3f3f3f3f;

struct Edge
{
	int v, next;
} e[N*2];

bool vis[N];
int tmp[N], val[N], ans[N], seq[N*2];
int n, root, sig, tick, head[N], cur[N];

inline int lowbit( int p )
{
	return p & ( -p );
}

inline int Query( int p )
{
	int res = 0;
	for( int i = p; i > 0; i -= lowbit( i ) )
		res += val[i];
	return res;
}

inline void Modify( int p, int x )
{
	for( int i = p; i <= n; i += lowbit( i ) )
		val[i] += x;
	return ;
}

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

void DFS( int root )
{
	tick = 0;
	set( vis, 0 );
	cpy( cur, head );
	stack< int > s;
	s.push( root );
	while( !s.empty() )
	{
		int u = s.top();
		// When backtracking to u, don't modify u again
		if( !vis[u] )
		{
			vis[u] = 1;
			tmp[u] = Query( u );
			Modify( u, 1 );
		}
		bool flag = false;
		for( int i = cur[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( !vis[v] )
			{
				s.push( v );
				flag = true;
				cur[u] = e[i].next;
				break ;
			}
		}
		if( flag )
			continue ;
		// After backtracking to u
		ans[u] = Query( u ) - tmp[u];
		s.pop();
	}
	return ;
}

int main()
{
	while( scanf( "%d%d", &n, &root ) && n )
	{
		sig = 0, set( head, 0 );
		set( tmp, 0 ), set( val, 0 );
		for( int i = 1; i < n; i ++ )
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			AddEdge( u, v ), AddEdge( v, u );
		}
		DFS( root );
		printf( "%d", ans[1] - 1 );
		for( int i = 2; i <= n; i ++ )
			printf( " %d", ans[i] - 1 );
		printf( "\n" );
	}
	return 0;
}
