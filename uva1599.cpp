#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int INF = 0x7fffffff;
const   int N = 1e5 + 10, M = 2e5 + 10, BUF = 5e6 + 5;

char buf[BUF];
int n, m, tick, head[N], vis[N], dis[N], ans[M], q[N];

struct Edge
{
    int v, w, next;
} e[M*2];

void AddEdge( int u, int v, int w )
{
    e[++tick].v = v, e[tick].w = w;
    e[tick].next = head[u], head[u] = tick;
    return ;
}

int GetInt( char *s, char end )
{
	int res;
	for( res = 0; *s != end; s ++ )
		res = res * 10 + *s - '0';
	return res;
}

void Input()
{
	n = m = tick = 0;
    memset( head, 0, sizeof( head ) );
	memset( ans, 0x3f, sizeof( ans ) );
	fread( buf, 1, BUF, stdin );
	char *p = buf;
	while( *p == ' ' )
		p ++;
	n = GetInt( p, ' ' );
	m = GetInt( p, '\n' );
	for( int i = 0; i < m; i ++ )
	{
		int u = GetInt( p, ' ' );
		int v = GetInt( p, ' ' );
		int w = GetInt( p, '\n' );
		AddEdge( u, v, w );
		AddEdge( v, u, w );
	}
	return ;
}

void BFS()
{
	int h = 0, t = -1;
    memset( vis, 0, sizeof( 0 ) );
    memset( dis, 0x3f, sizeof( dis ) );
    dis[n] = 0, vis[n] = 1;
	q[++t] = n;
    while( h <= t )
    {
        int &u = q[h++];
		for( int i = head[u]; i; i = e[i].next )
        {
            int &v = e[i].v;
            if( !vis[v] )
            {
                vis[v] = 1;
				q[++t] = v;
				dis[v] = dis[u] + 1;
            }
        }
    }
    return ;
}

/*
void DFS( int u )
{
	int tmpD = INF;
	for( int i = head[u]; i; i = e[i].next )
		if( dis[e[i].v] == dis[u] - 1 && e[i].w < tmpD )
			tmpD = e[i].w;
	for( int i = head[u]; i; i = e[i].next )
	{
		if( dis[e[i].v] == dis[u] - 1 && e[i].w == tmpD && vis[e[i].v] )
		{
			DFS( e[i].v );
			ans[dis[u]] = min( ans[dis[u]], e[i].w );
		}
	}
	return ;
}
*/

void BFS_()
{
	int h = 0, t = -1;
	q[++t] = 1;
	memset( vis, 0, sizeof( vis ) );
	while( h <= t )
	{
		int tmpD = INF;
		int u = q[h++];
		for( int i = head[u]; i; i = e[i].next )
		{
			int &v = e[i].v;
			if( dis[v] + 1 == dis[u] && e[i].w < tmpD && !vis[v] )
				tmpD = e[i].w;
		}
		ans[dis[u]] = min( ans[dis[u]], tmpD );
		for( int i = head[u]; i; i = e[i].next )
		{
			int &v = e[i].v;
			if( dis[v] + 1 == dis[u] && e[i].w == tmpD && !vis[v] )
			{
				q[++t] = v;
				vis[v] = 1;
			}
		}
	}
	return ;
}

int main()
{
	freopen( "in_", "r", stdin );
    while( scanf( "%d%d", &n, &m ) == 2 )
    {
        for( int i = 0; i < m; i ++ )
        {
            int u, v, w;
            scanf( "%d%d%d", &u, &v, &w );
            AddEdge( u, v, w );
            AddEdge( v, u, w );
        }
        BFS();
		BFS_();
		printf( "%d\n", dis[1] );
		for( int i = 1; i <= dis[1]; i ++ )
			printf( "%d ", ans[dis[i]] );
    }
    return 0;
}
