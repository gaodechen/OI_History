#include	<cstdio>

const int N = 1e6 + 5;

int n, tick = 1, f[N];

int main()
{
	for( int i = 2; i < N; i ++ )
	{
		if( !f[i] )
		{
			for( int j = i; j < N; j += i )
				f[j] = tick;
			tick ++;
		}
	}
	while( scanf( "%d", &n ) == 1 )
		printf( "%d\n", f[n] );
	return 0;
}
