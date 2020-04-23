#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef	const int & var;
const	int INF = 0x3f3f3f3f;
const	int N = 500, M = 100000;

struct Network
{
	int sig, head[N];
	int s, t, n, d[N], gap[N], cur[N], pre[N];

	struct Edge
	{
		int v, cap, next;
	} e[M];

	inline void Emit( var u, var v, var w )
	{
		e[++sig].v = v, e[sig].cap = w;
		e[sig].next = head[u], head[u] = sig;
		return ;
	}

	inline void AddEdge( var u, var v, var w )
	{
		Emit( u, v, w ), Emit( v, u, 0 );
		return ;
	}

	inline int F( var i )
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
}g;

int t, n, m, u[M], v[M], l[M], r[M];

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		int sum = 0;
		scanf( "%d%d", &n, &m );
		g.sig = 0, set( g.head, 0 );
		g.n = n + 2, g.s = n + 1, g.t = n + 2;
		for( int i = 0; i < m; i ++ )
		{
			scanf( "%d%d%d%d", &u[i], &v[i], &l[i], &r[i] );
			g.AddEdge( u[i], v[i], r[i] - l[i] );
			sum += l[i];
		}
		for( int i = 0; i < m; i ++ )
		{
			g.AddEdge( g.s, v[i], l[i] );
			g.AddEdge( u[i], g.t, l[i] );
		}
		int flow = g.MaxFlow();
		if( flow == sum )
		{
			printf( "YES\n" );
			for( int i = 0; i < m; i ++ )
				printf( "%d\n", r[i] - g.e[i+i+1].cap );
		}
		else
			printf( "NO\n" );
		printf( "\n" );
	}
	return 0;
}
