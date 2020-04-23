#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<set>

using	namespace	std;
const	int N = 2e4 + 5;
const	int Q = 3e5 + 5;
typedef multiset< int > :: iterator data;

int n, m, c, q;
int pre[N], val[N];
multiset< int > G[N], V[N];

struct Operation
{
	int x, y;
	char type[1];
} op[Q];

int Find( int x )
{
	if( x != pre[x] )
		pre[x] = Find( pre[x] );
	return pre[x];
}

inline void Union( int u, int v )
{
	u = Find( u ), v = Find( v );
	if( u == v )
		return ;
	if( u > v )
		swap( u, v );
	pre[u] = v;
	for( data it = V[u].begin(); it != V[u].end(); it ++ )
		V[v].insert( *it );
	return ;
}

int main()
{
	while( scanf( "%d%d%d", &n, &m, &q ) == 3 )
	{
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%d", &val[i] );
			G[i].clear(), V[i].clear();
			pre[i] = i;
		}
		for( int i = 0; i < m; i ++ )
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			if( u > v )
				G[u].insert( v );
			else
				G[v].insert( u );
		}
		for( int i = 0; i < q; i ++ )
		{
			int a, b;
			scanf( "%s%d%d", op[i].type, &a, &b );
			op[i].x = a, op[i].y = b;
			if( op[i].type[0] == 'U' )
			{
				op[i].y = val[a];
				val[a] = b;
			}
			else if( op[i].type[0] == 'E' )
			{
				if( a > b )
					G[a].erase( G[a].find( b ) );
				else
					G[b].erase( G[b].find( a ) );
			}
		}
		for( int i = 1; i <= n; i ++ )
			V[i].insert( val[i] );
		for( int i = 1; i <= n; i ++ )
			for( data it = G[i].begin(); it != G[i].end(); it ++ )
				Union( i, *it );
		int sum = 0, tick = 0;
		for( int i = q - 1; i >= 0; i -- )
		{
			int a = op[i].x, b = op[i].y;
			if( op[i].type[0] == 'F' )
			{
				tick ++, a = Find( a );
				data it = V[a].lower_bound( b );
				if( it != V[a].end() )
					sum += *it;
			}
			else if( op[i].type[0] == 'U' )
			{
				int p = Find( a );
				data it = V[p].find( val[a] );
				V[p].erase( it );
				V[p].insert( b );
				val[a] = b;
			}
			else
				Union( a, b );
		}
		printf( "Case %d: %.3lf\n", ++ c, ( double ) sum / tick );
	}
	return 0;
}
