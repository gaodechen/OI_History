#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<deque>

using	namespace	std;
typedef const int & var;
const	int N = 1e3 + 5;
const	int M = 5e5 + 5;

struct SP
{
	int sig, head[N];
	bool vis[N], mark[M*2];
	int dis[N], dis_[N], pre[N];

	struct Edge
	{
		int v, w, next;
	} e[M*2];

	inline void AddEdge( var u, var v, var w )
	{
		e[++sig].v = v, e[sig].w = w;
		e[sig].next = head[u], head[u] = sig;
		return ;
	}

	inline void Init()
	{
		sig = 0;
		memset( pre, -1, sizeof( pre ) );
		memset( head, 0, sizeof( head ) );
		memset( mark, 0, sizeof( mark ) );
		return ;
	}

	inline int F( int i )
	{
		return ( ( i - 1 ) ^ 1 ) + 1;
	}

	void SPFA( int s, int *d, bool k )
	{
		memset( d, -1, sizeof( dis ) );
		memset( vis, 0, sizeof( vis ) );
		deque< int > q;
		q.push_back( s );
		vis[s] = 1, d[s] = 0;
		while( !q.empty() )
		{
			int u = q.front();
			q.pop_front();
			vis[u] = 0;
			for( int i = head[u]; i; i = e[i].next )
			{
				if( mark[i] )
					continue ;
				int &v = e[i].v;
				if( d[v] == -1 || d[v] > d[u] + e[i].w )
				{
					d[v] = d[u] + e[i].w;
					if( k )
						pre[v] = i;
					if( !vis[v] )
					{
						vis[v] = 1;
						if( !q.empty() && dis[v] < dis[q.front()] )
							q.push_front( v );
						else
							q.push_back( v );
					}
				}
			}
		}
		return ;
	}

	int Interface( int n )
	{
		int u = n, ans = 0;
		SPFA( 1, dis, 1 );
		while( u != 1 )
		{
			int k = F( pre[u] );
			mark[pre[u]] = mark[k] = 1;
			SPFA( 1, dis_, 0 );
			mark[pre[u]] = mark[k] = 0;
			ans = max( ans, dis_[n] );
			u = e[k].v;
		}
		return ans;
	}
} g;

int n, m, u, v, w;

int main()
{
	g.Init();
	scanf( "%d%d", &n, &m );
	for( int i = 0; i < m; i ++ )
	{
		scanf( "%d%d%d", &u, &v, &w );
		g.AddEdge( u, v, w );
		g.AddEdge( v, u, w );
	}
	printf( "%d\n", g.Interface( n ) );
	return 0;
}
