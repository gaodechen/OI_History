#include	<cstdio>

int d[31], q;

int main()
{
	d[0] = 1, d[2] = 3;
	for( int i = 4; i <= 30; i += 2 )
		d[i] += d[i-2] * 4 - d[i-4];
	while( scanf( "%d", &q ) && q != -1 )
		printf( "%d\n", d[q] );
	return 0;
}
