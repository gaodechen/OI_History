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
	int sig, s, t, head[N], in[N], out[N];
	int n, m, d[N], gap[N], cur[N], pre[N];

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
		set( gap, 0 ), set( d, -1 );
		d[t] = 0, q.push( t );
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
		int u = t, sur = INF;
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

	inline bool Judge()
	{
		int tot = 0;
		s = n + 1, t = n + 2;
		for( int i = 1; i <= n; i ++ )
		{
			if( ( in[i] + out[i] ) & 1 )
				return 0;
			int q = out[i] - in[i];
			if( q > 0 )
			{
				AddEdge( s, i, q / 2 );
				tot += q / 2;
			}
			else if( q < 0 )
				AddEdge( i, t, - q / 2 );
		}
		n += 2;
		int flow = MaxFlow();
		return flow == tot;
	}

	inline void Interface()
	{
		sig = 0, set( head, 0 );
		set( in, 0 ), set( out, 0 );
		scanf( "%d%d", &n, &m );
		for( int i = 0; i < m; i ++ )
		{
			int u, v, k;
			scanf( "%d%d%d", &u, &v, &k );
			out[u] ++, in[v] ++;
			if( k == 0 )
				AddEdge( u, v, 1 );
		}
		int flag = Judge();
		if( flag )
			printf( "possible\n" );
		else
			printf( "impossible\n" );
		return ;
	}
} g;

int main()
{
	int c;
	scanf( "%d", &c );
	while( c -- )
		g.Interface();
	return 0;
}

