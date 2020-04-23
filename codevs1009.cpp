#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;

char buf[31];
bool G[10][10];
int n, k, cnt[10];

int main()
{
	scanf( "%s%d", buf, &k );
	n = strlen( buf );
	for( int i = 0; i < k; i ++ )
	{
		int a, b;
		cin >> a >> b;
		G[a][b] = 1;
	}
	for( int k = 0; k < 10; k ++ )
		for( int i = 0; i < 10; i ++ )
			for( int j = 0; j < 10; j ++ )
				G[i][j] = G[i][j] || ( G[i][k] && G[k][j] );
	for( int i = 0; i < 10; i ++ )
		for( int j = 0; j < 10; j ++ )
			if( G[i][j] || i == j )
				cnt[i] ++;
	unsigned long long ans = 1;
	for( int i = 0; i < n; i ++ )
	{
		int q = buf[i] - '0';
		if( cnt[q] )
			ans *= cnt[q];
	}
	cout << ans << endl;
	return 0;
}
