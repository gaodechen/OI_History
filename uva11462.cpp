#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;

char buf[3];
int a[101], n;

inline int GetInt()
{
	int c = getchar();
	while( !isdigit( c ) )
		c = getchar();
	int x = 0;
	while( isdigit( c ) )
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x;
}

void PutInt( int k )
{
	int p = 0;
	if( k == 0 )
		p ++;
	else while( k )
	{
		buf[p++] = k % 10;
		k /= 10;
	}
	for( int i = p - 1; i >= 0; i -- )
		printf( "%c", buf[i] + '0' );
}

int main()
{
	while( ( n = GetInt() ) )
	{
		bzero( a, sizeof( a ) );
		for( int i = 1; i <= n; i ++ )
			a[GetInt()] ++;
		int t = 1;
		for( int i = 1; i <= 100; i ++ )
			for( int j = 1; j <= a[i]; j ++ )
			{
				if( !t )
					printf( " " );
				PutInt( i );
				t = 0;
			}
		printf( "\n" );
	}
	return 0;
}
