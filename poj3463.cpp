#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int INF = 0x3f3f3f3f;
const	int N = 1001, M = 10001;

int sig, head[N];
int T, n, m, s, t;

struct Edge
{
	int v, w, next;
} e[M];

inline void AddEdge( int u, int v, int w )
{
	e[++sig].v = v, e[sig].w = w;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

bool vis[N][2];
int dis[N], sdis[N], cnt[N][2];

inline int Compute()
{
	cnt[s][0] = 1, dis[s] = 0;
	for( int q = 1; q < n + n; q ++ )
	{
		int d = INF, p = -1, flag;
		for( int j = 1; j <= n; j ++ )
		{
			if( !vis[j][0] && dis[j] < d )
				p = j, d = dis[j], flag = 0;
			else if( !vis[j][1] && sdis[j] < d )
				p = j, d = sdis[j], flag = 1;
		}
		if( d == INF ) break ;
		vis[p][flag] = 1;
		for( int i = head[p]; i; i = e[i].next )
		{
			int v = e[i].v, w = e[i].w;
			if( dis[v] > d + w )
			{
				sdis[v] = dis[v], cnt[v][1] = cnt[v][0];
				dis[v] = d + w, cnt[v][0] = cnt[p][flag];
			}
			else if( dis[v] == d + w )
				cnt[v][0] += cnt[p][flag];
			else if( sdis[v] > d + w )
			{
				sdis[v] = d + w;
				cnt[v][1] = cnt[p][flag];
			}
			else if( sdis[v] == d + w )
				cnt[v][1] += cnt[p][flag];
		}
	}
	int ans = cnt[t][0];
	if( dis[t] + 1 == sdis[t] )
		ans += cnt[t][1];
	return ans;
}

int main()
{
	scanf( "%d", &T );
	while( T -- )
	{
		sig = 0, set( head, 0 );
		set( cnt, 0 ), set( vis, 0 );
		set( dis, INF ), set( sdis, INF );
		scanf( "%d%d", &n, &m );
		for( int i = 0; i < m; i ++ )
		{
			int u, v, w;
			scanf( "%d%d%d", &u, &v, &w );
			AddEdge( u, v, w );
		}
		scanf( "%d%d", &s, &t );
		int res = Compute();
		printf( "%d\n", res );
	}
	return 0;
}
