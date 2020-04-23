#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<vector>

#define		set(p, k)		memset(p, k, sizeof(p))

using	namespace	std;
const	int N = 5001;

struct SCC
{
	bool vis[N];
	int n, m, top, ont, index;
	int mark[N], dfn[N], stack[N], low[N], out[N];
	vector< int > e[N];

	inline void Init( int n_, int m_ )
	{
		n = n_, m = m_;
		for( int i = 1; i <= n; i ++ )
			e[i].clear();
		for( int i = 0; i < m; i ++ )
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			e[u].push_back( v );
		}
		top = ont = index = 0;
		set( vis, 0 ), set( dfn, 0 );
		set( low, 0 ), set( mark, 0 );
		set( out, 0 ), set( stack, 0 );
		return ;
	}

	void DFS( int u )
	{
		dfn[u] = low[u] = ++ index;
		stack[++top] = u, vis[u] = 1;
		for( int i = 0; i < ( int )e[u].size(); i ++ )
		{
			int &v = e[u][i];
			if( !dfn[v] )
			{
				DFS( v );
				low[u] = min( low[u], low[v] );
			}
			else if( vis[v] )
				low[u] = min( low[u], dfn[v] );
		}
		if( dfn[u] == low[u] )
		{
			int v;
			ont ++;
			do
			{
				v = stack[top--];
				vis[v] = 0;
				mark[v] = ont;
			}
			while( u != v && top );
		}
		return ;
	}

	void Tarjan()
	{
		for( int i = 1; i <= n; i ++ )
			if( !dfn[i] )
				DFS( i );
		return ;
	}

	void Interface()
	{
		int tmp[N];
		set(tmp, 0);
		for(int i = 1; i <= n; i ++)
			for( int j = 0; j < (int) e[i].size(); j ++ )
				if( mark[i] != mark[e[i][j]] )
					out[mark[i]] ++;
		for( int i = 1; i <= ont; i ++ )
			if( out[i] == 0 )
				tmp[i] = 1;
		for( int i = 1; i <= n; i ++ )
			if( tmp[mark[i]] )
				printf( "%d ", i );
		printf( "\n" );
		return ;
	}

} g;

int main(int argc, char **argv)
{
	int n, m;
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		g.Init( n, m );
		g.Tarjan();
		g.Interface();
	}
	return 0;
}
