#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 105;

int n, m, s, tick;
double V, dis[N];

struct Edge
{
	int u, v;
	double r, c;
} e[N*2];

void AddEdge( int u, int v, double r, double c )
{
	e[++tick].u = u, e[tick].v = v;
	e[tick].r = r, e[tick].c = c;
	return ;
}

bool Relax( int k )
{
	int &u = e[k].u, &v = e[k].v;
	double t = ( dis[u] - e[k].c ) * e[k].r;
	if( t > dis[v] )
	{
		dis[v] = t;
		return true;
	}
	return false;
}

bool BellmanFord()
{
	bool flag;
	dis[s] = V;
	for( int i = 1; i < n; i ++ )
	{
		flag = false;
		for( int j = 1; j <= tick; j ++ )
			if( Relax( j ) )
				flag = true;
		if( dis[s] > V )
			return true;
		if( !flag )
			return false;
	}
	for( int i = 1; i <= tick; i ++ )
		if( Relax( i ) )
			return true;
	return false;
}

int main()
{
	scanf( "%d%d%d%lf", &n, &m, &s, &V );
	for( int i = 1; i <= m; i ++ )
	{
		int u, v; double r, c;
		scanf( "%d%d%lf%lf", &u, &v, &r, &c );
		AddEdge( u, v, r, c );
		scanf( "%lf%lf", &r, &c );
		AddEdge( v, u, r, c );
	}
	printf( "%s\n", BellmanFord() ? "YES" : "NO" );
	return 0;
}
