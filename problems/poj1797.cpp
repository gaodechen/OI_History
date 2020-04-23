#include	<cstdio>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e3 + 5;

int t, n, m, father[N];

struct Edge
{
	int u, v, w;
	bool operator < ( const Edge &b ) const
	{
		return w > b.w;
	}
} e[N*100];

inline int Find( int u )
{
	if(u != father[u])
		father[u] = Find(father[u]);
	return father[u];
}

inline void Union(int u, int v)
{
	father[Find(v)] = Find(u);
	return ;
}

int main()
{
	scanf( "%d", &t );
	for( int q = 1; q <= t; q ++ )
	{
		scanf( "%d%d", &n, &m );
		for( int i = 1; i <= n; i ++ )
			father[i] = i;
		for( int i = 1; i <= m; i ++ )
			scanf( "%d%d%d", &e[i].u, &e[i].v, &e[i].w );
		sort( e + 1, e + m + 1 );
		int ans = 0x3f3f3f3f;
		for( int i = 1; i <= m; i ++ )
		{
			Union( e[i].u, e[i].v );
			ans = min( e[i].w, ans );
			if( Find( 1 ) == Find( n ) )
				break ;
		}
		printf( "Scenario #%d:\n", q );
		printf( "%d\n\n", ans );
	}
	return 0;
}
