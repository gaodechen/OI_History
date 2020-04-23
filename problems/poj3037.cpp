#include	<cmath>
#include	<cstring>
#include	<cstdio>
#include	<iostream>
#include	<queue>

using	namespace	std;
const	int N = 1e2 + 3;
const	double INF = 9999999999;

int n, m, h0, h, vis[N][N];
double V, dis[N][N], v[N][N];
int next[][2] = { { 0, 1 }, { 0, -1 }, { -1, 0 }, { 1, 0 } };

struct Point
{
	int x, y;
	Point( int x, int y ): x( x ), y( y )
	{
	}
	inline bool CheckPos()
	{
		return x >= 1 && y >= 1 && x <= n && y <= m;
	}
};

void SPFA( Point s )
{
	queue< Point > Q;
	Q.push( s );
	dis[1][1] = 0, vis[1][1] = 1;
	while( !Q.empty() )
	{
		Point p = Q.front(); Q.pop();
		vis[p.x][p.y] = 0;
		for( int d = 0; d < 4; d ++ )
		{
			Point q( p.x + next[d][0], p.y + next[d][1] );
			if( !q.CheckPos() )
				continue ;
			if( dis[p.x][p.y] + v[p.x][p.y] < dis[q.x][q.y] )
			{
				dis[q.x][q.y] = dis[p.x][p.y] + v[p.x][p.y];
				if( !vis[q.x][q.y] )
				{
					vis[q.x][q.y] = 1;
					Q.push( q );
				}
			}
		}
	}
	return ;
}

int main()
{
	scanf( "%lf%d%d", &V, &n, &m );
	scanf( "%d", &h0 );
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = 1; j <= m; j ++ )
		{
			if( i == 1 && j == 1 )
				continue ;
			scanf( "%d", &h );
			dis[i][j] = INF;
			v[i][j] = 1.0 / ( V * pow( 2.0, h0 - h ) );
		}
	}
	v[1][1] = 1.0 / V;
	SPFA( Point( 1, 1 ) );
	printf( "%.2lf\n", dis[n][m] );
	return 0;
}
