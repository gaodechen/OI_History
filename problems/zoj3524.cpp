#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>
#include	<vector>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 6e2 + 5;
const	int M = 2e3 + 5;

struct Edge
{
	int v, w;

	Edge( int v = 0, int w = 0 ): v( v ), w( w )
	{
	}
};

bool vis[N];
vector< Edge > G[N];
int d[N][M], p[N][M], list[N];
int n, m, w, s, tot, c[N], v[N], in[N];

void TopoSort()
{
	queue< int > q;
	for( int i = 1; i <= n; i ++ )
		if( in[i] == 0 )
			q.push( i );
	while( !q.empty() )
	{
		int u = q.front(); q.pop();
		list[++tot] = u;
		for( int i = 0; i < ( int ) G[u].size(); i ++ )
		{
			int v = G[u][i].v;
			if( -- in[v] == 0 )
				q.push( v );
		}
	}
	return ;
}

int main()
{
	while( scanf( "%d%d%d%d", &n, &m, &w, &s ) == 4 )
	{
		for( int i = 1; i <= n; i ++ )
			G[i].clear();
		tot = 0;
		set( d, 0 ), set( p, 0 );
		set( in, 0 ), set( vis, 0 );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d%d", &c[i], &v[i] );
		for( int i = 0; i < m; i ++ )
		{
			int u, v, w;
			scanf( "%d%d%d", &u, &v, &w );
			G[u].push_back( Edge( v, w ) );
			in[v] ++;
		}
		TopoSort();
		vis[s] = 1;
		int val = -0x3f3f3f3f, cost = 0;
		for( int i = 1; i <= tot; i ++ )
		{
			int u = list[i];
			if( !vis[u] )
				continue ;
			for( int j = 0; j <= w; j ++ )
			{
				if( j >= c[u] )
				{
					int tmp = d[u][j-c[u]] + v[u];
					if( d[u][j] < tmp )
						d[u][j] = tmp, p[u][j] = p[u][j-c[u]];
					else if( d[u][j] == tmp )
						p[u][j] = min( p[u][j], p[u][j-c[u]] );
				}
				for( int k = 0; k < ( int ) G[u].size(); k ++ )
				{
					int v = G[u][k].v;
					vis[v] = 1;
					if( d[u][j] > d[v][j] )
						d[v][j] = d[u][j], p[v][j] = p[u][j] + G[u][k].w * j;
					else if( d[u][j] == d[v][j] )
						p[v][j] = min( p[v][j], p[u][j] + G[u][k].w * j );
				}
				if( d[u][j] > val )
					val = d[u][j], cost = p[u][j];
				else if( d[u][j] == val )
					cost = min( p[u][j], cost );
			}
		}
		printf( "%d\n", cost );
	}
	return 0;
}
