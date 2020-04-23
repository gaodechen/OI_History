#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 30;

int ans, tmp[N], mark[N], G[N][N];

bool DFS( int u, int ans_ )
{
	for( int i = u + 1; i <= 26; i ++ )
	{
		if( mark[i] + ans_ <= ans )
			return 0;
		if( G[u][i] )
		{
			int j;
			for( j = 0; j < ans_; j ++ )
				if( !G[i][tmp[j]] )
					break ;
			if( j == ans_ )
			{
				tmp[j] = i;
				if( DFS( i, ans_ + 1 ) )
					return 1;
			}
		}
	}
	if( ans_ > ans )
	{
		ans = ans_;
		return 1;
	}
	return 0;
}

int MaxClique()
{
	ans = 0;
	for( int i = 26; i; i -- )
	{
		tmp[0] = i;
		DFS( i, 1 );
		mark[i] = ans;
	}
	return ans;
}

int main()
{
	int q;
	while( scanf( "%d", &q ) && q )
	{
		memset( G, 0, sizeof( G ) );
		memset( mark, 0, sizeof( mark ) );
		for( int i = 1; i <= q; i ++ )
		{
			char buf[N];
			scanf( "%s", buf + 1 );
			int u = buf[1] - 'A' + 1;
			for( int j = 3; j <= ( int )strlen( buf + 1 ); j ++ )
			{
				int v = buf[j] - 'A' + 1;
				G[u][v] = G[v][u] = 1;
			}
		}
		int ans = MaxClique();
		printf( "%d channel%s needed.\n", ans, ans == 1 ? "" : "s" );
	}
	return 0;
}
