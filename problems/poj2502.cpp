#include	<cmath>
#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 205;
const	double INF = 0x3f3f3f3f;

struct Point
{
	double x, y;
} e[N];

int n = 2, t = 2, mark[N];
double cost[N][N], dis[N], x, y;
double v1 = 500.0 / 3.0, v2 = 200.0 / 3.0;

double Distance( Point a, Point b )
{
	double d1 = a.x - b.x, d2 = a.y - b.y;
	return sqrt( d1 * d1 + d2 * d2 );
}

int Dijkstra()
{
	for( int i = 0; i < n; i ++ )
		dis[i] = INF;
	dis[0] = 0;
	for( int i = 1; i < n; i ++ )
		dis[i] = cost[0][i];
	for( int i = 2; i <= n; i ++ )
	{
		int k = -1;
		double d = INF;
		for( int j = 0; j < n; j ++ )
			if( !mark[j] && dis[j] < d )
				k = j, d = dis[j];
		if( k == -1 )
			break ;
		mark[k] = 1;
		for( int j = 0; j < n; j ++ )
			if( !mark[j] && dis[k] + cost[k][j] < dis[j] )
				dis[j] = dis[k] + cost[k][j];
	}
	return ( int )( dis[1] + 0.5 );
}

int main()
{
	scanf( "%lf%lf%lf%lf", &e[0].x, &e[0].y, &e[0].x, &e[0].y );
	for( int i = 0; i < N; i ++ )
	{
		for( int j = 0; j < N; j ++ )
		{
			if( i == j )
				cost[i][j] = 0;
			else
				cost[i][j] = INF;
		}
	}
	while( scanf( "%lf%lf", &e[n].x, &e[n].y ) == 2 )
	{
		if( e[n].x == -1 && e[n].y == -1 )
		{
			t = n;
			continue ;
		}
		if( n != t )
			cost[n][n-1] = cost[n-1][n] = Distance( e[n], e[n-1] ) * 3 / 2000;
		n ++;
	}
	for( int i = 0; i < n; i ++ )
	{
		for( int j = 0; j < n; j ++ )
		{
			if( cost[i][j] == INF )
				cost[i][j] = cost[j][i] = Distance( e[i], e[j] ) * 3 / 500;
		}
	}
	printf( "%d\n", Dijkstra() );
	return 0;
}
