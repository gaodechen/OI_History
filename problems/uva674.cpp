#include	<cstdio>
#include	<cstring>

const	int N = 8e3;

int m, d[N];
int a[] = { 50, 25, 10, 5, 1 };

int main()
{
	while( scanf( "%d", &m ) == 1 )
	{
		memset( d, 0, sizeof( d ) );
		d[0] = 1;
		for( int i = 0; i < 5; i ++ )
			for( int j = a[i]; j <= m; j ++ )
				d[j] += d[j-a[i]];
		printf( "%d\n", d[m] );
	}
	return 0;
}
