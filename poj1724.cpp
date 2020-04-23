#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<queue>

using	namespace	std;
const	int INF = 0x3f3f3f3f;
const	int N = 105, M = 10005; 

struct Edge
{
	int v, c, d, next;
} e[M];

int k, n, m, sig, head[N], vis[N], dis[N], d[M][N];

void AddEdge( int u, int v, int d, int c )
{
	e[++sig].v = v, e[sig].c = c, e[sig].d = d;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

void SPFA()
{
	queue< int > q;
	q.push( 1 );
	vis[1] = 1;
	memset( d, INF, sizeof( d ) );
	for( int i = 0; i <= k; i ++ )
		d[i][1] = 0;
	while( !q.empty() )
	{
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for( int i = head[u]; i; i = e[i].next )
		{
			int v = e[i].v, w = e[i].d, c = e[i].c;
			for( int j = c; j <= k; j ++ )
			{
				if( d[j][v] > d[j-c][u] + w )
				{
					d[j][v] = d[j-c][u] + w;
					if( !vis[v] )
					{
						q.push( v );
						vis[v] = 1;
					}
				}
			}
		}
	}
	return ;
}

int main()
{
	scanf( "%d%d%d", &k, &n, &m );
	for( int i = 1; i <= m; i ++ )
	{
		int u, v, d, c;
		scanf( "%d%d%d%d", &u, &v, &d, &c );
		AddEdge( u, v, d, c );
	}
	SPFA();
	int res = INF;
	for( int i = 0; i <= k; i ++ )
		res = min( res, d[i][n] );
	printf( "%d\n", res == INF ? -1 : res );
	return 0;
}
