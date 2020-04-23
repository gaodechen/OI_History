#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<cmath>
#include	<queue>
#include	<stack>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 1000, M = 400000;

struct Edge
{
	double w;
	int v, next;
} e[M];

bool vis[N];
double dis[N], L, R, l, u, k;
int n, m, sig, head[N], cnt[N];

void AddEdge( int u, int v, double w )
{
	e[++sig].v = v, e[sig].w = w;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

bool SPFA()
{
	stack< int > q;
	q.push( 1 );
	for( int i = 1; i <= n + n; i ++ )
		dis[i] = 1e10;
	dis[1] = 0;
	set( vis, 0 ), vis[1] = 0;
	set( cnt, 0 ), cnt[1] = 1;
	int war = ( int )sqrt( ( double ) n + m + 1 );
	while( !q.empty() )
	{
		int u = q.top(); q.pop();
		vis[u] = 0;
		for( int i = head[u]; i; i = e[i].next )
		{
			int &v = e[i].v;
			if( dis[v] > dis[u] + e[i].w )
			{
				dis[v] = dis[u] + e[i].w;
				if( !vis[v] )
				{
					if( ++ cnt[v] > war )
						return false;
					q.push( v );
					vis[v] = 1;
				}
			}
		}
	}
	return true;
}

int main()
{
	while( scanf( "%d%d%lf%lf", &n, &m, &l, &u ) == 4 )
	{
		// log(a[i]) - log(b[j]) >= log(l) - log(x)
		// log(a[i]) - log(b[j]) >= log(x) - log(u)
		sig = 0, set( head, 0 );
		L = log( l ), R = log( u );
		for( int i = 1; i <= n; i ++ )
		{
			for( int j = 1; j <= m; j ++ )
			{
				scanf( "%lf", &k );
				k = log( k );
				AddEdge( i, j + n, k - L );
				AddEdge( j + n, i, R - k );
			}
		}
		if( SPFA() )
			printf( "YES\n" );
		else
			printf( "NO\n" );
	}
	return 0;
}
