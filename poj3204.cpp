#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>
#include	<vector>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
const	int INF = 0x3f3f3f3f;
const	int N = 501, M = 5001;

struct Network
{
	int sig, head[N], vis[N];
	int s, t, d[N], cur[N], gap[N], pre[N];

	struct Edge
	{
		int v, cap, next;
	} e[M*2];

	inline void AddEdge( int u, int v, int w )
	{
		e[++sig].v = v, e[sig].cap = w;
		e[sig].next = head[u], head[u] = sig;
		return ;
	}

	inline int F( int i )
	{
		return ( ( i - 1 ) ^ 1 ) + 1;
	}

	inline void BFS()
	{
		queue< int > q;
		q.push( t );
		set( d, -1 );
		set( gap, 0 );
		d[t] = 0;
		while( !q.empty() )
		{
			int u = q.front(); q.pop();
			gap[d[u]] ++;
			for( int i = head[u]; i; i = e[i].next )
			{
				int &v = e[i].v;
				if( d[v] == -1 && e[F(i)].cap > 0 )
				{
					d[v] = d[u] + 1;
					q.push( v );
				}
			}
		}
		return ;
	}

	inline int Augment()
	{
		int sur = INF, u = t;
		while( u != s )
		{
			sur = min( sur, e[pre[u]].cap );
			u = e[F(pre[u])].v;
		}
		u = t;
		while( u != s )
		{
			e[pre[u]].cap -= sur;
			e[F(pre[u])].cap += sur;
			u = e[F(pre[u])].v;
		}
		return sur;
	}

	inline bool Advance( int &u )
	{
		bool res = false;
		for( int &i = cur[u]; i; i = e[i].next )
		{
			int &v = e[i].v;
			if( e[i].cap > 0 && d[u] == d[v] + 1 )
			{
				u = v, pre[v] = i;
				res = true;
				break ;
			}
		}
		return res;
	}

	inline void Retreat( int &u )
	{
		int k = t - 1;
		for( int i = head[u]; i; i = e[i].next )
			if( e[i].cap > 0 )
				k = min( k, d[e[i].v] );
		d[u] = k + 1;
		gap[d[u]] ++;
		cur[u] = head[u];
		if( u != s )
			u = e[F(pre[u])].v;
		return ;
	}

	int MaxFlow()
	{
		BFS();
		int u = s, flow = 0;
		cpy( cur, head );
		while( d[s] < t )
		{
			if( u == t )
			{
				flow += Augment();
				u = s;
			}
			if( !Advance( u ) )
			{
				if( -- gap[d[u]] == 0 )
					break ;
				Retreat( u );
			}
		}
		return flow;
	}

	void SourceDFS( int u )
	{
		vis[u] = 1;
		for( int i = head[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( !vis[v] && e[i].cap > 0 )
				SourceDFS( v );
		}
		return ;
	}

	void SinkDFS( int u )
	{
		vis[u] = 2;
		for( int i = head[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( !vis[v] && e[F(i)].cap > 0 )
				SinkDFS( v );
		}
		return ;
	}

	inline void Interface( int n )
	{
		s = 1, t = n;
		set( vis, 0 );
		MaxFlow();
		SourceDFS( s );
		SinkDFS( t );
		int sum = 0;
		for( int i = 1; i <= sig; i += 2 )
			if( vis[e[F(i)].v] == 1 && vis[e[i].v] == 2 )
				sum ++;
		printf( "%d\n", sum );
		return ;
	}

} g;

int n, m;

int main()
{
	freopen( "in", "r", stdin );
	g.sig = 0;
	set( g.head, 0 );
	scanf( "%d%d", &n, &m );
	for( int i = 0; i < m; i ++ )
	{
		int u, v, w;
		scanf( "%d%d%d", &u, &v, &w );
		u ++, v ++;
		g.AddEdge( u, v, w );
		g.AddEdge( v, u, 0 );
	}
	g.Interface( n );
	return 0;
}

/* 从s开始dfs
如果一条边的s能到达t不能
就是割边
不能到达s的就是在t
Q: 起点在S"或者"终点再T
对啊
在t的肯定s到不了啊
Q: 那起点在S"并且"终点再T的有什么特殊意义吗?
最小割中的边
Q: 是不是"一定"再最小割中的边?
不一定, 在某个最小割中的边
Q: 用DFS和mark[u] != mark[v]求出了一堆割边, 其中有的不是最小割的边?
mark[u] > mark[v]
要这样吧
不然起点是t终点是s的边也算了？
Q: 不一定是最小割边吗?
起点是t终点是s的边肯定不是啊
用这样可以求出一个最小割的方案来
但是不一定是唯一的方案
Q: 那个mark[u] > mark[v]的一定是最小割边?如果v没有被T访问
嗯
*/
