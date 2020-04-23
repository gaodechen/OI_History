#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
typedef	long long	data;
const	int N = 5e4 + 5, M = 1e4 + 5;

struct Edge
{
	int u, v, w;
	bool operator < ( const Edge &b ) const
	{
		return w > b.w;
	}
} e[N];

int t, n, m, r, father[M];

int Find( int u )
{
	if( u != father[u] )
		father[u] = Find( father[u] );
	return father[u];
}

void Union( int u, int v )
{
	father[Find(v)] = Find( u );
	return ;
}

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d%d%d", &n, &m, &r );
		for( int i = 0; i < M; i ++ )
			father[i] = i;
		for( int i = 0; i < r; i ++ )
		{
			scanf( "%d%d%d", &e[i].u, &e[i].v, &e[i].w );
			e[i].v += n;
		}
		sort( e, e + r );
		data sum = 0;
		for( int i = 0, t = 0; i < r; i ++ )
		{
			if( Find( e[i].u ) != Find( e[i].v ) )
			{
				Union( e[i].u, e[i].v );
				sum += e[i].w;
				t ++;
			}
			if( t == n + m - 1 )
				break ;
		}
		printf( "%lld\n", 10000 * ( data )( n + m ) - sum );
	}
	return 0;
}
