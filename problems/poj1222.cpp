#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
const	int INF = 0x3f3f3f3f, N = 30;

int t, a[40][40];

void Gauss()
{
	for(int i = 0, k; i < N; i ++)
	{
		for(k = i; k < N; k ++)
			if(a[k][i])
				break ;
		if(k != i) for(int j = 0; j <= N; j ++)
			swap(a[i][j], a[k][j]);
		for(int j = 0; j < N; j ++)
			if(i != j && a[j][i])
				for(k = 0; k <= N; k ++)
					a[j][k] ^= a[i][k];
	}
	return ;
}

int main()
{
	scanf( "%d", &t );
	for(int c = 1; c <= t; c ++)
	{
		for(int i = 0; i < N; i ++)
			scanf("%d", &a[i][N]);
		for(int i = 0; i < N; i ++)
		{
			a[i][i] = 1;
			if(i >= 6) a[i-6][i] = 1;
			if(i < 24) a[i+6][i] = 1;
			if(i % 6) a[i-1][i] = 1;
			if((i + 1) % 6) a[i+1][i] = 1;
		}
		Gauss();
		printf("PUZZLE #%d\n", c);
		for(int i = 0; i < N; i ++)
		{
			printf("%d", a[i][N]);
			if((i + 1) % 6 == 0)
				printf("\n");
			else
				printf(" ");
		}
	}
	return 0;
}
