#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<queue>

using	namespace	std;
const	int N = 5e3 + 5, M = 2e5 + 5;

int n, m, tick, head[N], d1[N], d2[N], vis[N];

struct Edge
{
	int v, w, next;
} e[M];

void AddEdge( int u, int v, int w )
{
	e[++tick].v = v, e[tick].w = w;
	e[tick].next = head[u], head[u] = tick;
	return ;
}

void SPFA( int s, int *dis )
{
	memset( vis, 0, sizeof( vis ) );
	memset( dis, 0x3f, sizeof( vis ) );
	queue< int > q;
	q.push( s );
	dis[s] = 0, vis[s] = 1;
	while( !q.empty() )
	{
		int u = q.front(); q.pop();
		for( int i = head[u]; i; i = e[i].next )
		{
			int &v = e[i].v;
			if( dis[v] > dis[u] + e[i].w )
			{
				dis[v] = dis[u] + e[i].w;
				if( !vis[v] )
				{
					q.push( v );
					vis[v] = 1;
				}
			}
		}
		vis[u] = 0;
	}
	return ;
}

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= m; i ++ )
	{
		int u, v, w;
		scanf( "%d%d%d", &u, &v, &w );
		AddEdge( u, v, w );
		AddEdge( v, u, w );
	}
	SPFA( 1, d1 );
	SPFA( n, d2 );
	int ans = 0x3f3f3f3f;
	for( int u = 1; u <= n; u ++ )
	{
		for( int i = head[u]; i; i = e[i].next )
		{
			int d = d1[u] + d2[e[i].v] + e[i].w;
			if( d > d1[n] && d < ans )
				ans = d;
		}
	}
	printf( "%d\n", ans );
	return 0;
}
