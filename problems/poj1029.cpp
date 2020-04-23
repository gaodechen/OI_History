#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e3 + 5;

char buf[2];
int n, k, a, s[N], x[N], y[N], t[N];

int main()
{
	scanf( "%d%d", &n, &k );
	while( k -- )
	{
		scanf( "%d", &a );
		for( int i = 0; i < a; i ++ )
			scanf( "%d", &x[i] );
		for( int i = 0; i < a; i ++ )
			scanf( "%d", &y[i] );
		scanf( "%s", buf );
		if( buf[0] == '=' )
		{
			for( int i = 0; i < a; i ++ )
				s[x[i]] = s[y[i]] = 1;
		}
		else if( buf[0] == '<' )
		{
			memcpy( t, s, sizeof( s ) );
			for( int i = 1; i <= n; i ++ )
				s[i] = 1;
			for( int i = 0; i < a; i ++ )
				s[x[i]] = 2, s[y[i]] = 3;
			for( int i = 1; i <= n; i ++ )
				if( t[i] >= 1 && t[i] != s[i] )
					s[i] = 1;
		}
		else
		{
			memcpy( t, s, sizeof( t ) );
			for( int i = 1; i <= n; i ++ )
				s[i] = 1;
			for( int i = 0; i < a; i ++ )
				s[x[i]] = 3, s[y[i]] = 2;
			for( int i = 1; i <= n; i ++ )
				if( t[i] >= 1 && t[i] != s[i] )
					s[i] = 1;
		}
	}
	int flag = 0, p = -1;
	for( int i = 1; i <= n; i ++ )
		if( s[i] != 1 )
			flag ++, p = i;
	if( flag != 1 )
		printf( "0\n" );
	else
		printf( "%d\n", p );
	return 0;
}

