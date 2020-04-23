#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<vector>

using	namespace	std;
const	int N = 1e2 + 5;
const	int INF = 0x3f3f3f3f;

int G[N][N], n, res;
int vis[N], dis[N], mark[N];
vector< pair< int, int > > ans;

void Prim()
{
	dis[1] = 0, vis[1] = 1;
	for( int i = 2; i <= n; i ++ )
	{
		dis[i] = G[1][i];
		mark[i] = 1;
	}
	while( 1 )
	{
		int v = -1;
		for( int i = 2; i <= n; i ++ )
			if( !vis[i] && ( v == -1 || dis[i] < dis[v] ) )
				v = i;
		if( v == -1 )
			break ;
		vis[v] = 1;
		res += dis[v];
		ans.push_back( make_pair( v, mark[v] ) );
		for( int i = 1; i <= n; i ++ )
		{
			if( G[v][i] < dis[i] )
			{
				dis[i] = G[v][i];
				mark[i] = v;
			}
		}
	}
	return ;
}

int main()
{
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= n; j ++ )
			scanf( "%d", &G[i][j] );
	Prim();
	int num = 0;
	for( int i = 0; i < ( int )ans.size(); i ++ )
	{
		int &a = ans[i].first, &b = ans[i].second;
		if( a > b )
			swap( a, b );
		if( G[a][b] )
			num ++;
	}
	printf( "%d\n", num );
	for( int i = 0; i < ( int )ans.size(); i ++ )
		if( G[ans[i].first][ans[i].second] )
			printf( "%d %d\n", ans[i].first, ans[i].second );
	printf( "%d\n", res );
	return 0;
}
