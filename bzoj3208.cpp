#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 750;

inline int in()
{
	int k = 0, t = 1, c = '\0';
	for( ; c > '9' || c < '0'; )
	{
		c = getchar();
		if( c == '-' )
			t = -1;
	}
	for( ; c >= '0' && c <= '9'; )
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	if( t == -1 )
		return -k;
	return k;
}

bool mark[N][N];
int n, q, G[N][N], d[N][N];
int nextX[] = { 1, -1, 0, 0 };
int nextY[] = { 0, 0, 1, -1 };

int Search( int x, int y )
{
	if( d[x][y] )
		return d[x][y];
	int opt = 0;
	for( int p = 0; p < 4; p ++ )
	{
		int a = x + nextX[p];
		int b = y + nextY[p];
		if( mark[a][b] && G[a][b] < G[x][y] )
		{
			int tmp = Search( a, b );
			if( tmp > opt )
				opt = tmp;
		}
	}
	d[x][y] = opt + 1;
	return d[x][y];
}

int main()
{
	n = in();
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= n; j ++ )
			G[i][j] = in(), mark[i][j] = 1;
	q = in();
	char t = '\0';
	while( q -- )
	{
		char buf[2];
		scanf( "%s", buf );
		if( buf[0] == 'Q' )
		{
			memset( d, 0, sizeof( d ) );
			for( int i = 1; i <= n; i ++ )
				for( int j = 1; j <= n; j ++ )
					if( !d[i][j] && mark[i][j] )
						Search( i, j );
			int ans = 0;
			if( t != 'Q' )
			{
				for( int i = 1; i <= n; i ++ )
					for( int j = 1; j <= n; j ++ )
						ans = max( d[i][j], ans );
			}
			printf( "%d\n", ans );
		}
		else if( buf[0] == 'C' )
		{
			int a, b, c;
			a = in(), b = in(), c = in();
			G[a][b] = c;
		}
		else
		{
			int a, b, c, d;
			bool k = buf[0] == 'B';
			a = in(), b = in(), c = in(), d = in();
			for( int i = a; i <= c; i ++ )
				for( int j = b; j <= d; j ++ )
					mark[i][j] = k;
		}
		t = buf[0];
	}
	return 0;
}
