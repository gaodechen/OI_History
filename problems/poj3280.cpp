#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int M = 3000, N = 30;

char s[M], t[2];
int w[N], d[M][M], n, m;

int main()
{
	scanf( "%d%d%s", &n, &m, s + 1 );
	for( int i = 0, a, b; i < n; i ++ )
	{
		scanf( "%s%d%d", t, &a, &b );
		w[t[0] - 'a'] = min( a, b );
	}
	for( int i = m; i >= 1; i -- )
	{
		for( int j = i + 1; j <= m; j ++ )
		{
			if(s[i] == s[j])
				d[i][j] = d[i + 1][j - 1];
			else
				d[i][j] = min(d[i + 1][j] + w[s[i] - 'a'], d[i][j - 1] + w[s[j] - 'a']);
		}
	}
	printf( "%d\n", d[1][m] );
}
