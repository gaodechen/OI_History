#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int N = 60, M = 50000;
const	int INF = 0x3f3f3f3f;

struct Edge
{
	int v, w, next;
} e[M];

bool vis[M];
int s, sig, deg[N], head[N];

inline void AddEdge( int u, int v, int w )
{
	e[++sig].v = v, e[sig].w = w;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

inline int F( int i )
{
	return ( ( i - 1 ) ^ 1 ) + 1;
}

void Euler( int u )
{
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if( !vis[i] && !vis[F(i)] )
		{
			vis[i] = vis[F(i)] = 1;
			Euler( v );
			printf( "%d ", e[i].w );
		}
	}
	return ;
}

int main()
{
	while( 1 )
	{
		int u, v, w;
		sig = 0, set( head, 0 );
		set( deg, 0 ), set( vis, 0 );
		scanf( "%d%d", &u, &v );
		if( u == 0 && v == 0 )
			break ;
		s = u;
		do
		{
			scanf( "%d", &w );
			AddEdge( u, v, w );
			AddEdge( v, u, w );
			deg[u] ++, deg[v] ++;
		}
		while( scanf( "%d%d", &u, &v ) && u );
		bool flag = true;
		for( int i = 1; i <= 50; i ++ )
		{
			if( deg[i] & 1 )
			{
				flag = false;
				break ;
			}
		}
		if( !flag )
		{
			printf("Round trip does not exist.\n" );
			continue ;
		}
		Euler( s );
		printf( "\n" );
	}
	return 0;
}
