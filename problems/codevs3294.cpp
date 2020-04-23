#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

using	namespace	std;
const	int N = 1001;

int n, m, in[N], d[N], t[N];
bool G[N][N], a[N];

void TopoSort()
{
	queue< int > q;
	for( int i = 1; i <= n; i ++ )
		if( in[i] == 0 )
			q.push( i ), d[i] = 1;
	while( !q.empty() )
	{
		int u = q.front(); q.pop();
		for( int v = 1; v <= n; v ++ )
		{
			if( G[u][v] )
			{
				d[v] = max( d[v], d[u] + 1 );
				if( -- in[v] == 0 )
					q.push( v );
			}
		}
	}
	return ;
}

int main()
{
	scanf( "%d%d", &n, &m );
	for( int i = 0, q; i < m; i ++ )
	{
		scanf( "%d", &q );
		memset( a, 0, sizeof( a ) );
		for( int j = 1; j <= q; j ++ )
		{
			scanf( "%d", &t[j] );
			a[t[j]] = 1;
		}
		for( int j = t[1]; j <= t[q]; j ++ ) if( !a[j] )
			for( int k = 1; k <= q; k ++ ) if( !G[j][t[k]] )
				G[j][t[k]] = 1, in[t[k]] ++;
	}
	TopoSort();
	int ans = 0;
	for( int i = 1; i <= n; i ++ )
		ans = max( ans, d[i] );
	printf( "%d\n", ans );
	return 0;
}
