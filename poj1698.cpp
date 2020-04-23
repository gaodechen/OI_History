#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<queue>

using	namespace	std;
const	int N = 500;
const	int INF = 0x3f3f3f3f;

inline int A( const int &x )
{
	return ( ( x + 1 ) ^ 1 ) - 1;
}

struct Edge
{
	int v, cap, next;
} e[N*N];

int head[N], level[N], cur[N];
int n, sig, sum, s = N - 2, t = N - 1, flag;

void AddEdge( int u, int v, int w )
{
	e[++sig].v = v, e[sig].cap = w;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

bool BFS()
{
	queue< int > q;
	memset(level, -1, sizeof(level));
	level[s] = 0;
	q.push( s );
	while( !q.empty() )
	{
		int u = q.front();
		q.pop();
		for( int i = head[u]; i; i = e[i].next )
		{
			int &v = e[i].v;
			if( level[v] == -1 && e[i].cap > 0 )
			{
				level[v] = level[u] + 1;
				q.push( v );
			}
		}
	}
	return level[t] != -1;
}

int DFS( int u, int sur )
{
	if( u == t || sur == 0 )
		return sur;
	int flow = 0;
	for( int i = cur[u]; i; i = e[i].next )
	{
		int &v = e[i].v;
		if( e[i].cap && level[v] == level[u] + 1 )
		{
			int del = DFS( v, min( e[i].cap - flow, sur ) );
			e[i].cap -= del, e[A(i)].cap += del;
			flow += del, sur -= del;
			if( sur == 0 )
				break ;
		}
		cur[u] = i;
	}
	return flow;
}

int MaxFlow()
{
	int flow = 0;
	while( BFS() )
	{
		for( int i = 1; i <= t; i ++ )
			cur[i] = head[i];
		flow += DFS( s, INF );
	}
	return flow;
}

int main()
{
	int T, n, d, w, mark[7];
	scanf( "%d", &T );
	while( T -- )
	{
		scanf( "%d", &n );
		sig = 0, sum = 0, flag = 0;
		memset( head, 0, sizeof( head ) );
		for( int i = 1; i <= n; i ++ )
		{
			for( int j = 0; j < 7; j ++ )
				scanf( "%d", &mark[j] );
			scanf( "%d%d", &d, &w );
			AddEdge( s, i, d );
			AddEdge( i, s, 0 );
			sum += d, flag = max( flag, w );
			for( int j = 1; j <= w; j ++ )
			{
				for( int k = 0; k < 7; k ++ )
				{
					if( mark[k] )
					{
						int v = j * 7 + k + n;
						AddEdge( i, v, 1 );
						AddEdge( v, i, 0 );
					}
				}
			}
		}
		for( int i = 1; i <= flag; i ++ )
		{
			for( int k = 0; k < 7; k ++ )
			{
				int v = i * 7 + k + n;
				AddEdge( v, t, 1 );
				AddEdge( t, v, 0 );
			}
		}
		if( MaxFlow() == sum )
			printf( "Yes\n" );
		else
			printf( "No\n" );
	}
	return 0;
}
