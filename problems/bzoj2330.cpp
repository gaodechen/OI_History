#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
const	int INF = 0x3f3f3f3f;
const	int BUF = 1024 * 1024 * 60;
const	int N = 1e5 + 5, M = 3e5 + 5;

int len;
char buf[BUF], *s;

inline int Cin()
{
	int res = 0;
	while( *s > '9' || *s < '0' )
		s ++;
	while( *s <= '9' && *s >= '0' )
	{
		res = res * 10 + *s - '0';
		s ++;
	}
	return res;
}

bool vis[N];
int n, m, sig, head[N], dis[N], cnt[N];

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

void SPFA()
{
	queue< int > q;
	for( int i = 1; i <= n; i ++ )
	{
		vis[i] = 1, dis[i] = 1;
		q.push( i );
	}
	while( !q.empty() )
	{
		int u = q.front(); q.pop();
		vis[u] = 0;
		for( int i = head[u]; i; i = e[i].next )
		{
			int &v = e[i].v;
			if( dis[v] < dis[u] + e[i].w )
			{
				dis[v] = dis[u] + e[i].w;
				if( !vis[v] )
				{
					vis[v] = 1;
					if( ++ cnt[v] > n )
					{
						printf( "-1\n" );
						exit( 0 );
					}
					q.push( v );
				}
			}
		}
	}
	return ;
}

int main()
{
	len = fread( buf, 1, BUF, stdin );
	s = buf, buf[len] = '\0';
	n = Cin(), m = Cin();
	for( int i = 0; i < m; i ++ )
	{
		int x, a, b;
		x = Cin(), a = Cin(), b = Cin();
		if( x == 1 )
		{
			AddEdge( b, a, 0 );
			AddEdge( a, b, 0 );
		}
		else if( x == 2 )
		{
			if( a == b )
			{
				printf( "-1\n" );
				return 0;
			}
			AddEdge( a, b, 1 );
		}
		else if( x == 3 )
			AddEdge( b, a, 0 );
		else if( x == 4 )
		{
			if( a == b )
			{
				printf( "-1\n" );
				return 0;
			}
			AddEdge( b, a, 1 );
		}
		else
			AddEdge( a, b, 0 );
	}
	SPFA();
	long long ans = 0;
	for( int i = 1; i <= n; i ++ )
		ans += dis[i];
	printf( "%lld\n", ans );
	return 0;
}
