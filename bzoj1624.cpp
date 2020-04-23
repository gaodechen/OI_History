#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e2 + 5;
const	int M = 1e4 + 5;

inline int in()
{
	int k = 0, c = '\0';
	for( ; c > '9' || c < '0'; )
		c = getchar();
	for( ; c >= '0' && c <= '9'; )
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

int n, m, G[N][N], seq[M];

int main()
{
	n = in(), m = in();
	for( int i = 1; i <= m; i ++ )
		seq[i] = in();
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j <= n; j ++ )
			G[i][j] = in();
	for( int k = 1; k <= n; k ++ )
		for( int i = 1; i <= n; i ++ )
			for( int j = 1; j <= n; j ++ )
				G[i][j] = min( G[i][j], G[i][k] + G[k][j] );
	int ans = 0;
	for( int i = 2; i <= m; i ++ )
		ans += G[seq[i-1]][seq[i]];
	ans += G[1][seq[1]];
	ans += G[seq[m]][n];
	printf( "%d\n", ans );
	return 0;
}
