#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

using	namespace	std;
const	int N = 26, M = 900;
const	int INF = 0x3f3f3f3f;

// sum[i-1] - sum[i] >= -t[i]
// sum[i] - sum[i-1] >= 0
// sum[i] - sum[i-8] >= r[i]			( 8 <= i <= 24 )
// sum[i] - sum[i+16] >= r[i] - k       ( 1 <= i <=  7 )
// sum[24] >= k

bool vis[N];
int T, n, m, sig, head[N];
int r[N], t[N], d[N], cnt[N];

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

inline int SPFA( int s = 0 )
{
	queue< int > q;
	memset( vis, 0, sizeof( vis ) );
	memset( cnt, 0, sizeof( cnt ) );
	for( int i = 0; i < N; i ++ )
		d[i] = -INF;
	q.push( s );
	d[s] = 0, vis[s] = 1, cnt[s] = 1;
	while( !q.empty() )
	{
		int u = q.front(); q.pop();
		vis[u] = 0;
		for( int i = head[u]; i != -1; i = e[i].next )
		{
			int v = e[i].v;
			if( d[v] < d[u] + e[i].w )
			{
				d[v] = d[u] + e[i].w;
				if( !vis[v] )
				{
					vis[v] = 1;
					q.push( v );
					if( ++ cnt[v] > 24 )
						return INF;
				}
			}
		}
	}
	return d[24];
}

inline bool Check( int k )
{
	// sum[i] - sum[i-8] >= r[i]			( 8 <= i <= 24 )
	// sum[i] - sum[i+16] >= r[i] - sum[24] ( 1 <= i <=  7 )
	sig = 0;
	memset( head, -1, sizeof( head ) );
	for( int i = 1; i <= 24; i ++ )
	{
		AddEdge( i - 1, i, 0 );
		AddEdge( i, i - 1, -t[i] );
	}
	// sum[24] >= k
	AddEdge( 24, 0, -k );
	AddEdge( 0, 24, k );
	for( int i = 1; i <= 8; i ++ )
		AddEdge( i + 16, i, r[i] - k );
	for( int i = 9; i <= 24; i ++ )
		AddEdge( i - 8, i, r[i] );
	int dis = SPFA();
	return dis == k;
}

int main()
{
	scanf( "%d", &T );
	while( T -- )
	{
		memset( t, 0, sizeof( t ) );
		for( int i = 1; i <= 24; i ++ )
			scanf( "%d", &r[i] );
		scanf( "%d", &n );
		for( int i = 1, x; i <= n; i ++ )
		{
			scanf( "%d", &x );
			t[x+1] ++;
		}
		int l = 0, r = n, flag = 0;
		while( l < r )
		{
			int mid = ( l + r ) >> 1;
			if( Check( mid ) )
				r = mid, flag = 1;
			else
				l = mid + 1;
		}
		if( flag )
			printf( "%d\n", l );
		else
			printf( "No Solution\n" );
	}
	return 0;
}
