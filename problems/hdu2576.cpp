#include	<cstdio>

typedef	long long data;
const data M = 20090524;

int main()
{
	int t;
	data n, ans;
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%lld", &n );
		ans = n * ( n + 1 ) % ( M * 6 );
		ans = ( ans * ( n + 2 ) / 6 ) % M;
		printf( "%lld\n", ans );
	}
	return 0;
}
