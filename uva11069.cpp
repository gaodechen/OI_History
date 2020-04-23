#include	<cstdio>

const	int N = 80;
int		d[N], q;

int main()
{
	d[1] = 1, d[2] = d[3] = 2;
	for( int i = 4; i < N; i ++ )
		d[i] = d[i-2] + d[i-3];
	while( scanf( "%d", &q ) == 1 )
		printf( "%d\n", d[q] );
	return 0;
}
