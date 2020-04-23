#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int INF = 0x3f3f3f3f, N = 25;

int n, m, ans, sx, sy, G[N][N];
int next[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

inline bool CheckIndex( var x, var y )
{
	return x >= 1 && x <= n && y >= 1 && y <= m;
}

void Compute( int i, int j, int dis )
{
	if( dis > 10 || dis > ans )
		return ;
	for( int d = 0; d < 4; d ++ )
	{
		int x = i, y = j, flag = 0;
		while( CheckIndex( x, y ) )
		{
			x += next[d][0];
			y += next[d][1];
			flag ++;
			if( G[x][y] == 3 )
			{
				ans = min( ans, dis + 1 );
				return ;
			}
			if( G[x][y] == 1 )
				break ;
		}
		if( G[x][y] == 1 && flag > 1 )
		{
			G[x][y] = 0;
			Compute( x - next[d][0], y - next[d][1], dis + 1 );
			G[x][y] = 1;
		}
	}
	return ;
}

int main()
{
	while( scanf( "%d%d", &m, &n ) && n && m )
	{
		memset( G, 0, sizeof( G ) );
		for( int i = 1; i <= n; i ++ )
			for( int j = 1; j <= m; j ++ )
				scanf( "%d", &G[i][j] );
		for( int i = 1; i <= n; i ++ )
			for( int j = 1; j <= m; j ++ )
				if( G[i][j] == 2 )
					sx = i, sy = j;
		ans = INF;
		Compute( sx, sy, 0 );
		if( ans <= 10 )
			printf( "%d\n", ans );
		else
			printf( "-1\n" );
	}
	return 0;
}
