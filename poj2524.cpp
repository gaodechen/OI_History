#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 5e4 + 5;
const	int BUF = 1024 * 1024 * 60;

char buf[BUF], *p;
int father[N], n, m, tick;

inline int Find( int a )
{
	while( a != father[a] )
	{
		father[a] = father[father[a]];
		a = father[a];
	}
	return father[a];
}

inline int GetInt()
{
	int res;
	while( *p == ' ' || *p == '\n' )
		p ++;
	for( res = 0; *p != ' ' && *p != '\n' && *p != '\0'; p ++ )
		res = res * 10 + *p - '0';
	return res;
}

int main()
{
	int len = fread( buf, 1, BUF, stdin );
	buf[len] = '\0', p = buf;
	while( 1 )
	{
		n = GetInt();
		m = GetInt();
		if( !n )
			break ;
		for( int i = 1; i <= n; i ++ )
			father[i] = i;
		for( int i = 1; i <= m; i ++ )
		{
			int a = GetInt();
			int b = GetInt();
			a = Find( a ), b = Find( b );
			if( a != b )
				father[b] = a, n --;
		}
		printf( "Case %d: %d\n", ++ tick, n );
	}
	return 0;
}
