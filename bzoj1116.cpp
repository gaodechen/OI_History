#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 1e5 + 5;
const	int BUF = 1024 * 1024 * 60;

int pre[N];
bool mark[N];
char buf[BUF], *s;

inline int Cin()
{
	int res = 0;
	while( *s > '9' || *s < '0' )
		s ++;
	while( *s <= '9' && *s >= '0' )
	{
		res = res * 10 + *s - '0';
		s ++;
	}
	return res;
}

int Find( int x )
{
	if( x != pre[x] )
		pre[x] = Find( pre[x] );
	return pre[x];
}

inline void Union( int u, int v )
{
	u = Find( u );
	v = Find( v );
	if( mark[u] || mark[v] )
		mark[u] = 1;
	pre[v] = u;
	return ;
}

int main()
{
	int len = fread( buf, 1, BUF, stdin );
	s = buf, buf[len] = '\0';
	int n = Cin(), m = Cin();
	for( int i = 1; i <= n; i ++ )
		pre[i] = i;
	for( int i = 0; i < m; i ++ )
	{
		int u = Find( Cin() );
		int v = Find( Cin() );
		if( u == v )
			mark[u] = 1;
		else
			Union( u, v );
	}
	bool flag = true;
	for( int i = 1; i <= n; i ++ )
	{
		if( !mark[Find(i)] )
		{
			flag = false;
			break ;
		}
	}
	if( flag )
		printf( "TAK\n" );
	else
		printf( "NIE\n" );
	return 0;
}
