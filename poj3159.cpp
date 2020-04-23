#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 3e4 + 5;
const	int M = 15e4 + 5;
const	int INF = 0x3f3f3f3f;
const	int BUF = 1024 * 1024 * 60;

char buf[BUF], *p;
int n, m, tick, head[N];
int dis[N], vis[N], q[N];

inline int GetInt()
{
	int res = -1;
	while( *p == ' ' || *p == '\n' )
		p ++;
	for( ; *p != ' ' && *p != '\n' && *p != '\0'; p ++ )
	{
		if( res == -1 )
			res = 0;
		res = res * 10 + *p - '0';
	}
	return res;
}

struct Edge
{
	int v, w, next;
} e[M];

void AddEdge( int u, int v, int w )
{
	e[++tick].v = v, e[tick].w = w;
	e[tick].next = head[u], head[u] = tick;
	return ;
}

int SPFA( int s, int t )
{
	int top = 0;
	q[top++] = s;
	for( int i = 1; i <= n; i ++ )
		vis[i] = 0, dis[i] = INF;
	vis[s] = 1, dis[s] = 0;
	while( top )
	{
		int u = q[--top];
		vis[u] = 0;
		for( int i = head[u]; i; i = e[i].next )
		{
			int &v = e[i].v;
			if( dis[v] > dis[u] + e[i].w )
			{
				dis[v] = dis[u] + e[i].w;
				if( !vis[v] )
				{
					vis[v] = 1;
					q[top++] = v;
				}
			}
		}
	}
	return dis[t];
}

int main()
{
	freopen( "in_", "r", stdin );
	int len = fread( buf, 1, BUF, stdin );
	buf[len] = '\0', p = buf;
	while( ( n = GetInt() ) != -1 && ( m = GetInt() ) != -1 )
	{
		tick = 0;
		memset( head, 0, sizeof( head ) );
		int a, b, c;
		for( int i = 1; i <= m; i ++ )
		{
			a = GetInt(), b = GetInt(), c = GetInt();
			AddEdge( a, b, c );
		}
		printf( "%d\n", SPFA( 1, n ) );
	}
	return 0;
}
