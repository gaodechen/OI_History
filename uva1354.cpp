#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<vector>
#define		SUB( a, b )		( a - 1 ) & b

using	namespace	std;
const	int N = ( 1 << 6 ), K = 6;

struct Node
{
	double l, r;
	Node(): l( 0 ), r( 0 )
	{
	}
};

int t, n;
bool vis[N];
double r, w[K], sum[N];
vector< Node > tree[N];

void DFS( int set )
{
	if( vis[set] )
		return ;
	vis[set] = 1;
	bool flag = 0;
	for( int lSon = SUB( set, set ); lSon; lSon = SUB( lSon, set ) )
	{
		flag = 1;
		int rSon = set ^ lSon;
		double d1 = sum[rSon] / sum[set];
		double d2 = sum[lSon] / sum[set];
		DFS( lSon ), DFS( rSon );
		for( int i = 0; i < ( int )tree[lSon].size(); i ++ )
		{
			for( int j = 0; j < ( int )tree[rSon].size(); j ++ )
			{
				Node p;
				p.l = max( tree[lSon][i].l + d1, tree[rSon][j].l - d2 );
				p.r = max( tree[rSon][j].r + d2, tree[lSon][i].r - d1 );
				if( p.l + p.r < r )
					tree[set].push_back( p );
			}
		}
	}
	if( !flag )
		tree[set].push_back( Node() );
	return ;
}

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		memset( vis, 0, sizeof( vis ) );
		scanf( "%lf%d", &r, &n );
		for( int i = 0; i < n; i ++ )
			scanf( "%lf", &w[i] );
		for( int i = 0; i < ( 1 << n ); i ++ )
		{
			sum[i] = 0;
			tree[i].clear();
			for( int j = 0; j < n; j ++ )
				if( ( 1 << j ) & i )
					sum[i] += w[j];
		}
		int root = ( 1 << n ) - 1;
		DFS( root );
		double ans = -1;
		for( int i = 0; i < ( int )tree[root].size(); i ++ )
			ans = max( ans, tree[root][i].l + tree[root][i].r );
		printf( "%.10lf\n", ans );
	}
	return 0;
}
