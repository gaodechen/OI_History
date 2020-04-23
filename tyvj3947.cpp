#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>
#include	<vector>

using	namespace	std;
const	int N = 1e4 + 5;
const	int M = 5e4 + 5;
const	int INF = 0x3f3f3f3f;

bool isrc[N];
int n, m, k, sig, head[N], src[5];

struct Edge
{
	int v, w, next;
} e[M+M];

inline void AddEdge( int u, int v, int w )
{
	e[++sig].v = v, e[sig].w = w;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

bool vis[N];
int d[N][5];
vector< int > perm;

inline void SPFA( int s, int *dis )
{
	queue< int > q;
	q.push( s );
	memset( vis, 0, sizeof( vis ) );
	dis[s] = 0, vis[s] = 1;
	while( !q.empty() )
	{
		int u = q.front(); q.pop();
		vis[u] = 0;
		for( int i = head[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( dis[v] > dis[u] + e[i].w )
			{
				dis[v] = dis[u] + e[i].w;
				if( !vis[v] )
				{
					vis[v] = 1;
					q.push( v );
				}
			}
		}
	}
	return ;
}

int main()
{
	scanf( "%d%d%d", &n, &m, &k );
	for( int i = 0; i < k; i ++ )
	{
		scanf( "%d", &src[i] );
		isrc[src[i]] = 1;
		perm.push_back( i );
	}
	for( int i = 0; i < m; i ++ )
	{
		int u, v, w;
		scanf( "%d%d%d", &u, &v, &w );
		AddEdge( u, v, w );
		AddEdge( v, u, w );
	}
	memset( d, INF, sizeof( d ) );
	for( int i = 0; i < k; i ++ )
		SPFA( src[i], d[i] );
	int ans = INF;
	do
	{
		int sum = 0, tmp = INF;
		for( int i = 1; i < k; i ++ )
			sum += d[perm[i-1]][src[perm[i]]];
		for( int i = 1; i <= n; i ++ )
			if( !isrc[i] )
				tmp = min( tmp, d[perm[0]][i] + d[perm[k-1]][i] );
		ans = min( ans, sum + tmp );
	}
	while( next_permutation( perm.begin(), perm.end() ) );
	printf( "%d\n", ans );
	return 0;
}
