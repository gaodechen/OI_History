#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 2e3 + 5;
const	int INF = 0x3f3f3f3f;

bool G[N][N];
int n, m, sx, sy, vis[N][N][2];
int next[][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

inline int Check( int x, int y )
{
	return x >= 0 && x < n && y >= 0 && y < m;
}

bool DFS( int p, int q )
{
	int x = ( p % n + n ) % n;
	int y = ( q % m + m ) % m;
	if( !G[x][y] )
		return 0;
	if( vis[x][y][0] != -INF )
		return vis[x][y][0] != p || vis[x][y][1] != q;
	vis[x][y][0] = p, vis[x][y][1] = q;
	for( int d = 0; d < 4; d ++ )
		if( DFS( p + next[d][0], q + next[d][1] ) )
			return 1;
	return 0;
}

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		for( int i = 0; i < n; i ++ )
			for( int j = 0; j < m; j ++ )
				vis[i][j][0] = vis[i][j][1] = -INF;
		for( int i = 0; i < n; i ++ )
		{
			char buf[N];
			scanf( "%s", buf );
			for( int j = 0; j < m; j ++ )
			{
				if( buf[j] == 'S' )
					sx = i, sy = j;
				if( buf[j] != '#' )
					G[i][j] = 1;
				else
					G[i][j] = 0;
			}
		}
		if( DFS( sx, sy ) )
			printf( "Yes\n" );
		else
			printf( "No\n" );
	}
	return 0;
}
