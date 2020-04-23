// Negative cycle makes no solution!
#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<queue>

using	namespace	std;
const	int N = 1001, M = 20001;

struct Edge
{
	int v, w, next;
} e[M];

bool vis[N];
int sig, head[N];
int n, ml, md, dis[N], cnt[N];

inline void AddEdge( int u, int v, int w )
{
	e[++sig].v = v, e[sig].w = w;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

bool SPFA()
{
	queue< int > q;
	memset( dis, 0x3f, sizeof( dis ) );
	q.push( 1 );
	dis[1] = 0;
	while( !q.empty() )
	{
		int u = q.front();
		q.pop();
		vis[u] = 0;
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
					if( ++ cnt[v] > n )
						return false;
				}
			}
		}
	}
	return true;
}

int main()
{
	scanf( "%d%d%d", &n, &ml, &md );
	for( int i = 0; i < ml; i ++ )
	{
		int a, b, d;
		scanf( "%d%d%d", &a, &b, &d );
		AddEdge( a, b, d );
	}
	for( int i = 0; i < md; i ++ )
	{
		int a, b, d;
		scanf( "%d%d%d", &a, &b, &d );
		AddEdge( b, a, -d );
	}
	if( !SPFA() )
		printf( "-1\n" );
	else if( dis[n] >= 0x3f3f3f3f )
		printf( "-2\n" );
	else
		printf( "%d\n", dis[n] );
	return 0;
}
