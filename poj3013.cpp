#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<queue>

using	namespace	std;
typedef	long long	data;
const	int N = 5e4 + 5;

data dis[N], ans;
int T, n, m, tick, val[N], vis[N], head[N];

struct Edge
{
	int v, w, next;
} e[N*2];

void AddEdge( int u, int v, int w )
{
	e[++tick].v = v, e[tick].w = w;
	e[tick].next = head[u], head[u] = tick;
	return ;
}

void SPFA( int s )
{
	memset( vis, 0, sizeof( vis ) );
	memset( dis, -1, sizeof( dis ) );
	queue< int > q;
	q.push( s );
	vis[s] = 1, dis[s] = 0;
	while( !q.empty() )
	{
		int u = q.front(); q.pop();
		vis[u] = 0;
		for( int i = head[u]; i; i = e[i].next )
		{
			int &v = e[i].v;
			if( dis[v] == -1 || dis[v] > dis[u] + e[i].w )
			{
				dis[v] = dis[u] + e[i].w;
				if( !vis[v] )
				{
					q.push( v );
					vis[v] = 1;
				}
			}
		}
	}
	return ;
}

int main()
{
	scanf( "%d", &T );
	while( T -- )
	{
		tick = 0, ans = 0;
		memset( head, 0, sizeof( head ) );
		scanf( "%d%d", &n, &m );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d", &val[i] );
		for( int i = 1; i <= m; i ++ )
		{
			int u, v, w;
			scanf( "%d%d%d", &u, &v, &w );
			AddEdge( u, v, w );
			AddEdge( v, u, w );
		}
		if( n == 0 || n == 1 )
		{
			printf( "0\n" );
			continue ;
		}
		SPFA( 1 );
		bool flag = 1;
		if( m < n - 1 )
		{
			printf( "No Answer\n" );
			continue ;
		}
		for( int i = 2; i <= n; i ++ )
		{
			if( dis[i] == -1 )
			{
				printf( "No Answer\n" );
				flag = 0;
				break ;
			}
			ans += dis[i] * val[i];
		}
		if( flag )
			printf( "%lld\n", ans );
	}
	return 0;
}
