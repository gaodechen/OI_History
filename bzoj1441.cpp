#include	<cstdio>

int gcd( int a, int b )
{
	return b ? gcd( b, a % b ) : a;
}

int main()
{
	int n, a, d = 0;
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
	{
		scanf( "%d", &a );
		d = gcd( a, d );
	}
	d = d > 0 ? d : -d;
	printf( "%d\n", d );
	return 0;
}
