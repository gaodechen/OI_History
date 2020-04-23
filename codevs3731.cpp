#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

using	namespace	std;
const	int N = 1e4 + 5;
const	int M = 2e5 + 5;
const	int INF = 0x3f3f3f3f;

struct Edge
{
	int v, next;
} e[M], g[M];

bool vis[N];
int n, m, s, t, sig, sigg;
int head[N], headg[N], mark[N], d[N];

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

inline void EdgeAdd( int u, int v )
{
	g[++sigg].v = v, g[sigg].next = headg[u], headg[u] = sigg;
	return ;
}

void Judge()
{
	queue< int > q; q.push( t );
	memset( vis, 0, sizeof( vis ) );
	vis[t] = 1;
	while( !q.empty() )
	{
		int u = q.front(); q.pop();
		for( int i = headg[u]; i; i = g[i].next )
		{
			int v = g[i].v;
			if( !vis[v] )
			{
				vis[v] = 1;
				q.push( v );
			}
		}
	}
	for( int u = 1; u <= n; u ++ )
	{
		int tmp1 = 0, tmp2 = 0;
		for( int i = head[u]; i; i = e[i].next, tmp1 ++ )
			if( vis[e[i].v] )
				tmp2 ++;
		if( tmp1 == tmp2 && tmp1 )
			mark[u] = 1;
	}
	mark[t] = 1;
	return ;
}

void BFS()
{
	queue< int > q; q.push( s );
	memset( vis, 0, sizeof( vis ) );
	vis[s] = 1;
	while( !q.empty() )
	{
		int u = q.front(); q.pop();
		for( int i = head[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( !vis[v] && mark[v] )
			{
				vis[v] = 1;
				d[v] = d[u] + 1;
				q.push( v );
			}
		}
	}
	if( vis[t] )
		printf( "%d\n", d[t] );
	else
		printf( "-1\n" );
	return ;
}

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 0, u, v; i < m; i ++ )
	{
		scanf( "%d%d", &u, &v );
		AddEdge( u, v );
		EdgeAdd( v, u );
	}
	scanf( "%d%d", &s, &t );
	Judge(), BFS();
	return 0;
}
