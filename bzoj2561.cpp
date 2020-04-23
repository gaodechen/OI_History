#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
const	int N = 2e4 + 2;
const	int M = 2e5 + 2;
const	int INF = 0x3f3f3f3f;

inline int in()
{
	int k = 0, c = '\0';
	for( ; c > '9' || c < '0'; )
		c = getchar();
	for( ; c >= '0' && c <= '9'; )
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

struct Network
{
	int n, s, t, sig, head[N];
	int d[N], cur[N], gap[N], pre[N];

	struct Edge
	{
		int v, cap, next;
	} e[M+M];

	inline void Init( int x, int y, int z )
	{
		n = x, s = y, t = z;
		sig = 0, set( head, 0 );
		return ;
	}

	inline void Emit( int u, int v )
	{
		e[++sig].v = v, e[sig].cap = 1;
		e[sig].next = head[u], head[u] = sig;
		return ;
	}

	inline void AddEdge( int u, int v )
	{
		Emit( u, v ), Emit( v, u );
		return ;
	}

	inline int F( int i )
	{
		return ( ( i - 1 ) ^ 1 ) + 1;
	}

	inline void BFS()
	{
		queue< int > q;
		set( d, -1 ), set( gap, 0 );
		q.push( t ), d[t] = 0;
		while( !q.empty() )
		{
			int u = q.front(); q.pop();
			gap[d[u]] ++;
			for( int i = head[u]; i; i = e[i].next )
			{
				int v = e[i].v;
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
		bool flag = false;
		for( int &i = cur[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( e[i].cap > 0 && d[u] == d[v] + 1 )
			{
				u = v, pre[v] = i;
				flag = true;
				break ;
			}
		}
		return flag;
	}

	inline void Retreat( int &u )
	{
		int k = n - 1;
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
		while( d[s] < n )
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

} g1, g2;

struct Item
{
	int u, v, w;
} e[M];

int n, m, U, V, W;

int main()
{
	n = in(), m = in();
	for(int i = 0; i < m; i ++)
		e[i].u = in(), e[i].v = in(), e[i].w = in();
	U = in(), V = in(), W = in();
	g1.Init(n, U, V);
	g2.Init(n, U, V);
	for(int i = 0; i < m; i ++)
	{
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if(w > W)
			g1.AddEdge(u, v);
		else if(w < W)
			g2.AddEdge(u, v);
	}
	int ans = g1.MaxFlow() + g2.MaxFlow();
	printf("%d\n", ans);
	return 0;
}
