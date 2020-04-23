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
const	int N = 51, M = 5001;

struct Network
{
	int sig, head[N];
	int n, m, s, t, d[N], cur[N], gap[N], pre[N];

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

	inline void Interface()
	{
		sig = 0;
		set( head, 0 );
		int sum = 0;
		scanf( "%d%d%d%d", &n, &m, &s, &t );
		for( int i = 0; i < m; i ++ )
		{
			int u, v, w;
			scanf( "%d%d%d", &u, &v, &w );
			AddEdge( u, v, w * 1000 + 1 );
			AddEdge( v, u, w * 1000 + 1 );
			sum += w;
		}
		int flow = MaxFlow();
		if( flow == 0 )
			printf( "Inf\n" );
		else
		{
			int x, y;
			if( flow % 1000 == 0 )
			{
				y = 1000;
				flow -= 1000;
			}
			else
				y = flow % 1000;
			x = sum - flow / 1000;
			printf( "%.2lf\n", 1.0 *  x / y );
		}
		return ;
	}

} g;

int main()
{
	int t;
	scanf( "%d", &t );
	while( t -- )
		g.Interface();
	return 0;
}
