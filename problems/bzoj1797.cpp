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
const	int N = 4e3 + 5;
const	int M = 6e4 + 5;
const	int S = 6e7 + 5;
const	int INF = 0x3f3f3f3f;

int len;
char buf[S], *s;

inline int in()
{
	int r = 0;
	while( *s > '9' || *s < '0' )
		s ++;
	while( *s <= '9' && *s >= '0' )
	{
		r = r * 10 + *s - '0';
		s ++;
	}
	return r;
}

struct Network
{
	int n, m, s, t, sig, head[N];
	int d[N], cur[N], gap[N], pre[N];
	int ind, cnt, top, mark[N];
	int *ins, *dfn, *low, *stack;

	struct Edge
	{
		int v, cap, next;
	} e[M+M];

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
		set( d, -1 ), set( gap, 0 );
		q.push( t ), d[t] = 0;
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

	void Tarjan( int u )
	{
		dfn[u] = low[u] = ++ ind;
		stack[++ top] = u, ins[u] = 1;
		for( int i = head[u]; i; i = e[i].next )
		{
			if( !e[i].cap )
				continue ;
			int v = e[i].v;
			if( !dfn[v] )
			{
				Tarjan( v );
				low[u] = min( low[u], low[v] );
			}
			else if( ins[v] )
				low[u] = min( low[u], dfn[v] );
		}
		if( dfn[u] == low[u] )
		{
			int v;
			cnt ++;
			do
			{
				v = stack[top--];
				mark[v] = cnt;
				ins[v] = 0;
			}
			while( u != v && top );
		}
		return ;
	}

	inline void Interface()
	{
		n = in(), m = in(), s = in(), t = in();
		set( head, 0 ), sig = ind = cnt = top = 0;
		for( int i = 0; i < m; i ++ )
		{
			int u, v,  w;
			u = in(), v = in(), w = in();
			AddEdge( u, v, w );
			AddEdge( v, u, 0 );
		}
		MaxFlow();
		set( d, 0 ), set( cur, 0 );
		set( pre, 0 ), set( gap, 0 );
		ins = cur, dfn = d, low = gap, stack = pre;
		for( int i = 1; i <= n; i ++ )
			if( !dfn[i] )
				Tarjan( i );
		int S = mark[s], T = mark[t];
		for( int i = 1; i <= sig; i += 2 )
		{
			if( e[i].cap )
			{
				puts( "0 0" );
				continue ;
			}
			int x = 0, y = 0;
			int u = e[F(i)].v, v = e[i].v;
			if( mark[u] != mark[v] )
				x = 1;
			if( mark[u] == S && mark[v] == T )
				y = 1;
			printf( "%d %d\n", x, y );
		}
		return ;
	}

} g;

int main()
{
	len = fread( buf, 1, S, stdin );
    buf[len] = '\0', s = buf;
	g.Interface();
	return 0;
}
