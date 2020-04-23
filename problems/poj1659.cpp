#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 11;

struct Item
{
	int a, x;

	bool operator < ( const Item &b ) const
	{
		return a > b.a;
	}
} e[N];

bool G[N][N];
int t, n, q, flag;

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		q = flag = 1;
		scanf( "%d", &n );
		memset( G, 0, sizeof( G ) );
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%d", &e[i].a );
			e[i].x = i;
		}
		while( flag )
		{
			sort( e + 1, e + n + 1 );
			int k = e[1].a;
			if( k == 0 )
				break ;
			for( int i = 2; i <= k + 1; i ++ )
			{
				G[e[i].x][e[1].x] = G[e[1].x][e[i].x] = 1;
				if( -- e[i].a < 0 )
					flag = 0;
			}
			e[1].a = 0;
		}
		printf( "%s\n", flag ? "YES" : "NO" );
		if( flag ) for( int i = 1; i <= n; i ++ )
		{
			for( int j = 1; j <= n; j ++ )
				printf( "%d ", G[i][j] );
			printf( "\n" );
		}
		printf( "\n" );
	}
	return 0;
}
