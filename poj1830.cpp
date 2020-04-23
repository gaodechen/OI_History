#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<cmath>

using	namespace	std;
const	int N = 31;

int t, n, a[N][N];

void Gauss()
{
	for(int i = 0, k; i < n; i ++)
	{
		for(k = i; k < n; k ++)
			if(a[k][i])
				break ;
		if(k == n) continue ;
		if(k != i) for(int j = 0; j <= n; j ++)
			swap(a[k][j], a[i][j]);
		for(int j = 0; j < n; j ++)
			if(i != j && a[j][i])
				for(k = 0; k <= n; k ++)
					a[j][k] ^= a[i][k];
	}
	return ;
}

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d", &n );
		memset( a, 0, sizeof( a ) );
		for( int i = 0; i < n; i ++ )
			scanf( "%d", &a[i][n] );
		for( int i = 0, x; i < n; i ++ )
		{
			scanf( "%d", &x );
			a[i][n] ^= x;
		}
		int u, v;
		for( int i = 0; i < n; i ++ )
			a[i][i] = 1;
		// Row vector a[i] represents the lights that can influence i
		while( scanf( "%d%d", &u, &v ) && u )
			a[v-1][u-1] = 1;
		Gauss();
		int cnt = 0;
		bool flag = true;
		for( int i = 0; i < n; i ++ )
		{
			int sum = 0;
			for( int j = 0; j < n; j ++ )
				sum += a[i][j];
			if( sum == 0 && a[i][n] )
			{
				flag = false;
				break ;
			}
			if( a[i][n] == 0 && sum == 0 )
				cnt ++;
		}
		if( flag )
			cout << (1LL << (long long) cnt) << endl;
		else
			cout << "Oh,it's impossible~!!" << endl;
	}
	return 0;
}
