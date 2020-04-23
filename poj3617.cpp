#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 2e3 + 5;

int main()
{
	int n;
	char a[N];
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
		scanf( " %c", &a[i] );
	int l = 1, r = n;
	for( int i = 1; i <= n; i ++ )
	{
		int flag = 1;
		if( a[l] == a[r] )
		{
			for( int j = 1; l + j <= r - j; j ++ )
			{
				if( a[l+j] != a[r-j] )
				{
					flag = a[l+j] > a[r-j];
					break ;
				}
			}
		}
		if( a[l] < a[r] || flag == 0 )
			printf( "%c", a[l++] );
		else if( a[l] > a[r] || flag )
			printf( "%c", a[r--] );
		if( i % 80 == 0 && i != n )
			printf( "\n" );
	}
	return 0;
}
