#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int INF = 0x3f3f3f3f;
const	int N = 1001, M = 100001;

bool vis[N];
int n, m, k, s, t, sig;
int dis[N], cnt[N], head[N], head_[N];

struct Edge
{
	int v, w, next;
} e[M], inv[M];

struct Status
{
	int v, g, h;
	bool operator < ( const Status &b ) const
	{
		return g + h > b.g + b.h;
	}
};

priority_queue< Status > q;

void AddEdge( int u, int v, int w )
{
	e[++sig].v = v, e[sig].w = w;
	e[sig].next = head[u], head[u] = sig;
	inv[sig].v = u, inv[sig].w = w;
	inv[sig].next = head_[v], head_[v] = sig;
	return ;
}

void Dijkstra()
{
	set( dis, 0x3f );
	dis[t] = 0;
	for( int q = 1; q <= n; q ++ )
	{
		int p = -1, d = INF;
		for( int j = 1; j <= n; j ++ )
			if( vis[j] == false && d > dis[j] )
				d = dis[j], p = j;
		if( p == -1 )
			break ;
		vis[p] = 1;
		for( int i = head_[p]; i; i = inv[i].next )
		{
			int v = inv[i].v;
			if( dis[v] > dis[p] + inv[i].w )
				dis[v] = dis[p] + inv[i].w;
		}
	}
	return ;
}

int Astar()
{
	set( cnt, 0 );
	Status cur, next;
	cur.h = dis[s], cur.v = s, cur.g = 0;
	q.push( cur );
	while(!q.empty())
	{
		cur = q.top(); q.pop();
		cnt[cur.v] ++;
		if(cnt[t] == k)
			return cur.g;
		for(int i = head[cur.v]; i; i = e[i].next)
		{
			int v = e[i].v;
			next.g = cur.g + e[i].w;
			next.h = dis[v];
			next.v = v;
			q.push( next );
		}
	}
	return -1;
}

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 0; i < m; i ++ )
	{
		int u, v, w;
		scanf( "%d%d%d", &u, &v, &w );
		AddEdge( u, v, w );
	}
	scanf( "%d%d%d", &s, &t, &k );
	if(s == t) k ++;
	Dijkstra();
	int res = Astar();
	printf( "%d\n", res );
	return 0;
}
