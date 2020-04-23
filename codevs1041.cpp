#include	<cmath>
#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

using	namespace	std;
const	int N = 410;

double G[N][N], p, p_;
int Q, n, q, q_, S, T, A, B;

struct Point
{
	int x, y;
	Point( int x = 0, int y = 0 ): x( x ), y( y )
	{
	}
} e[N], t[5];

double Distance( const Point &a, const Point &b )
{
	double d1 = a.x - b.x;
	double d2 = a.y - b.y;
	return sqrt( d1 * d1 + d2 * d2 );
}

double SPFA( int s, int t )
{
	bool vis[N];
	double dis[N];
	int num = 4 * n + 2;
	for( int i = 1; i <= num; i ++ )
		dis[i] = 1.0 / 0.0, vis[i] = 0;
	dis[s] = 0, vis[s] = 1;
	queue< int > Q;
	Q.push( s );
	while( !Q.empty() )
	{
		int u = Q.front(); Q.pop();
		vis[u] = 0;
		for( int v = 1; v <= num; v ++ )
		{
			if( dis[v] > dis[u] + G[u][v] )
			{
				dis[v] = dis[u] + G[u][v];
				if( !vis[v] )
				{
					Q.push( v );
					vis[v] = 1;
				}
			}
		}
	}
	return dis[t];
}

inline bool Check( int a, int b, int c )
{
	return ( t[c].y - t[a].y ) * ( t[b].y - t[a].y ) + ( t[b].x - t[a].x ) * ( t[c].x - t[a].x ) == 0;
}

inline Point F( int a, int b, int c )
{
	return Point( t[c].x - t[a].x + t[b].x, t[c].y - t[a].y + t[b].y );
}

int main()
{
	scanf( "%d", &Q );
	while( Q -- )
	{
		q = q_ = 0;
		for( int i = 0; i < N; i ++ )
			for( int j = 0; j < N; j ++ )
				G[i][j] = 1.0 / 0.0;
		scanf( "%d%lf%d%d", &n, &p, &S, &T );
		for( int i = 1; i <= n; i ++ )
		{
			q_ = q;
			for( int j = 1; j <= 3; j ++ )
				scanf( "%d%d", &t[j].x, &t[j].y );
			scanf( "%lf", &p_ );
			if( Check( 1, 2, 3 ) )
				t[4] = F( 1, 2, 3 );
			else if( Check( 2, 1, 3 ) )
				t[4] = F( 2, 1, 3 );
			else if( Check( 3, 1, 2 ) )
				t[4] = F( 3, 1, 2 );
			for( int j = 1; j <= 4; j ++ )
				e[++q] = t[j];
			for( int x = q - 3; x <= q; x ++ )
				for( int y = q - 3; y <= q; y ++ )
					G[x][y] = G[y][x] = Distance( e[x], e[y] ) * p_;
		}
		for( int i = 1; i <= q; i ++ )
			for( int j = 1; j <= q; j ++ )
				if( G[i][j] == 1.0 / 0.0 )
					G[i][j] = G[j][i] =	Distance( e[i], e[j] ) * p;
		A = q + 1, B = q + 2;
		for( int i = S * 4 - 3; i <= S * 4; i ++ )
			G[A][i] = G[i][A] = 0;
		for( int i = T * 4 - 3; i <= T * 4; i ++ )
			G[i][B] = G[B][i] = 0;
		double res = SPFA( A, B );
		printf( "%.1lf\n", res );
	}
	return 0;
}
