#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 2e4 + 5;
const	int M = 2e5 + 5;

int n, m, sig;
int head[N], col[N], tmp[N], a[2];

struct Edge
{
	int v, next;
} e[M];

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}


bool DFS( int u )
{
	a[col[u]] ++;
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if( col[v] == -1 )
		{
			col[v] = !col[u];
			if( !DFS( v ) )
				return false;
		}
		else if( col[v] == col[u] )
			return false;
	}
	return true;
}

inline int Color()
{
	int sum = 0;
	memset( col, -1, sizeof( col ) );
	for( int i = 1; i <= n; i ++ )
	{
		a[0] = a[1] = 0;
		if( col[i] == -1 )
		{
			col[i] = 0;
			if( !DFS( i ) )
			{
				sum = -1;
				break ;
			}
			sum += min( a[0], a[1] );
		}
	}
	return sum;
}

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 0; i < m; i ++ )
	{
		int u, v;
		scanf( "%d%d", &u, &v );
		AddEdge( u, v );
		AddEdge( v, u );
	}
	int ans = Color();
	if( ans == -1 )
		printf( "Impossible\n" );
	else
		printf( "%d\n", ans );
	return 0;
}
