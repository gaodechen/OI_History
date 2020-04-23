#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<queue>
#define		D( a )		( ( a + 1 ) ^ 1 ) - 1

using	namespace	std;
const	int N = 250;
const	int INF = 0x3f3f3f3f;

int head[N], level[N], cur[N];
int n, m, np, nc, s, t, tick;

struct Edge
{
	int v, res, next;
} e[N*N];

void AddEdge( int u, int v, int res )
{
	e[++tick].v = v, e[tick].res = res;
	e[tick].next = head[u], head[u] = tick;
	return ;
}

int BFS()
{
	queue< int > q;
	memset( level, -1, sizeof( level ) );
	q.push( s );
	level[s] = 0;
	while( !q.empty() )
	{
		int u = q.front();
		q.pop();
		for( int i = head[u]; i; i = e[i].next )
		{
			int &v = e[i].v;
			if( e[i].res > 0 && level[v] == -1 )
			{
				q.push( v );
				level[v] = level[u] + 1;
			}
		}
	}
	return level[t] != -1;
}

int DFS(int u, int sur)
{
	if(u == t || sur == 0)
		return sur;
	int flow = 0;
	for(int i = cur[u]; i; i = e[i].next)
	{
		int v = e[i].v, del;
		if(e[i].res && level[v] == level[u] + 1)
		{
			del = DFS(v, min(e[i].res - flow, sur));
			e[i].res -= del, e[D(i)].res += del;
			flow += del, sur -= del;
			if(sur == 0) break ;
		}
		cur[u] = e[i].next;
	}
	return flow;
}

int MaxFlow()
{
	int flow = 0;
	while( BFS() )
	{
		for( int i = 0; i <= t; i ++ )
			cur[i] = head[i];
		flow += DFS( s, INF );
	}
	return flow;
}

int main()
{
    freopen("in", "r", stdin);
	while( scanf( "%d%d%d%d", &n, &np, &nc, &m ) == 4 )
	{
		int u, v, w;
		s = n, t = n + 1, tick = 0;
		memset( head, 0, sizeof( head ) );
		while( m -- )
		{
			scanf( " (%d,%d)%d", &u, &v, &w );
			AddEdge( u, v, w ), AddEdge( v, u, 0 );
		}
		while( np -- )
		{
			scanf( " (%d)%d", &u, &w );
			AddEdge( s, u, w ), AddEdge( u, s, 0 );
		}
		while( nc -- )
		{
			scanf( " (%d)%d", &u, &w );
			AddEdge( u, t, w ), AddEdge( t, u, 0 );
		}
		printf( "%d\n", MaxFlow() );
	}
	return 0;
}
