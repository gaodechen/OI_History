#include	<stdio.h>
#include	<string.h>
#define		max( a, b )		( a ) > ( b ) ? ( a ) : ( b )

const	int N = 101;
int t, n, sum, val[N];
double k, p[N], d[N*N];

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		sum = 0;
		memset( d, 0, sizeof( d ) );
		scanf( "%lf%d", &k, &n );
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%d%lf", &val[i], &p[i] );
			sum += val[i];
			p[i] = 1.0 - p[i];
		}
		k = 1.0 - k;
		d[0] = 1.0;
		for( int i = 1; i <= n; i ++ )
			for( int j = sum; j >= val[i]; j -- )
				d[j] = max( d[j], d[j-val[i]] * p[i] );
		for( int j = sum; j >= 0; j -- )
		{
			if( d[j] >= k )
			{
				printf( "%d\n", j );
				break ;
			}
		}
	}
	return 0;
}
