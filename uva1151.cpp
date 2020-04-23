#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1.5e3, M = 1e7;

struct Set
{
	int pre[N];

	inline void Init()
	{
		for( int i = 1; i < N; i ++ )
			pre[i] = i;
		return ;
	}

	int Find( int u )
	{
		if( u != pre[u] )
			pre[u] = Find( pre[u] );
		return pre[u];
	}

	void Union( int u, int v )
	{
		pre[Find(v)] = Find( u );
		return ;
	}
} set;

struct Edge
{
	int u, v, w;

	bool operator < ( const Edge &b ) const
	{
		return w < b.w;
	}
} e[M], f[M];

int t, n, q, sig, num, ans, group[8][N], cost[N], x[N], y[N];

int Kruskal( int mask )
{
	set.Init();
	int num_ = 0, sum_ = 0;
	for( int j = 0; j < q; j ++ )
	{
		if( mask & ( 1 << j ) )
		{
			sum_ += cost[j];
			for( int i = 1; i < group[j][0]; i ++ )
			{
				int u = set.Find( group[j][i] );
				int v = set.Find( group[j][i+1] );
				if( u != v )
				{
					set.Union( u, v );
					num_ ++;
				}
			}
		}
	}
	for( int i = 1; i <= num; i ++ )
	{
		int u = set.Find( f[i].u );
		int v = set.Find( f[i].v );
		if( u != v )
		{
			set.Union( u, v );
			sum_ += f[i].w;
			num_ ++;
		}
		if( num_ == n - 1 )
			break ;
	}
	return sum_;
}

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		num = ans = sig = 0;
		scanf( "%d%d", &n, &q );
		for( int i = 0; i < q; i ++ )
		{
			scanf( "%d%d", &group[i][0], &cost[i] );
			for( int j = 1; j <= group[i][0]; j ++ )
				scanf( "%d", &group[i][j] );
		}
		for( int i = 1; i <= n; i ++ )
			scanf( "%d%d", &x[i], &y[i] );
		for( int i = 1; i <= n; i ++ )
		{
			for( int j = i + 1; j <= n; j ++ )
			{
				int d1 = x[i] - x[j];
				int d2 = y[i] - y[j];
				e[++sig].u = i, e[sig].v = j;
				e[sig].w = d1 * d1 + d2 * d2;
			}
		}
		sort( e + 1, e + sig + 1 );
		set.Init();
		for( int i = 1; i <= sig; i ++ )
		{
			int u = set.Find( e[i].u );
			int v = set.Find( e[i].v );
			if( u != v )
			{
				set.Union( u, v );
				f[++num] = e[i];
				ans += e[i].w;
			}
			if( num == n - 1 )
				break ;
		}
		for( int i = 0; i < ( 1 << q ); i ++ )
			ans = min( Kruskal( i ), ans );
		printf( "%d\n", ans );
		if( t )
			printf( "\n" );
	}
	return 0;
}
