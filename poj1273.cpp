#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <queue>

using   namespace   std;
const   int N = 2e2 + 5;
const   int INF = 0x3f3f3f3f;

int n, m, cap[N][N], dis[N], vis[N], cur[N];

bool BFS( int s, int t )
{
    queue< int > q;
    q.push( s );
	memset( vis, 0, sizeof( vis ) );
    dis[s] = 0, vis[s] = 1;
    while( !q.empty() )
    {
        int u = q.front();
        q.pop();
        for( int v = 1; v <= n; v ++ )
        {
            if( !vis[v] && cap[u][v] > 0 )
            {
                vis[v] = 1;
                dis[v] = dis[u] + 1;
                q.push( v );
            }
        }
    }
    return vis[t];
}

int DFS( int u, int q )
{
    if( u == n || q == 0 )
        return q;
    int flow = 0;
    for( int v = cur[u]; v <= n; v ++ )
    {
        if( dis[u] + 1 == dis[v] && cap[u][v] > 0 )
        {
            int flow_ = DFS( v, min( q, cap[u][v] - flow ) );
            if( flow_ > 0 )
            {
                cap[u][v] -= flow_;
                cap[v][u] += flow_;
                flow += flow_;
                q -= flow_;
                if( q == 0 )
                    break ;
            }
        }
		cur[u] = v;
    }
    return flow;
}

int MaxFlow()
{
    int flow = 0;
    while( BFS( 1, n ) )
    {
		int del;
		for( int i = 1; i <= n; i ++ )
			cur[i] = 1;
        while( ( del = DFS( 1, INF ) ) )
			flow += del;
    }
    return flow;
}

int main()
{
    while( scanf( "%d%d", &m, &n ) == 2 )
    {
        memset( cap, 0, sizeof( cap ) );
        for( int i = 1; i <= m; i ++ )
        {
            int u, v, f;
            scanf( "%d%d%d", &u, &v, &f );
			cap[u][v] += f;
        }
        printf( "%d\n", MaxFlow() );
    }
    return 0;
}
