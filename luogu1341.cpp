#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 52, M = 1001;

inline int h( char x )
{
	if( x >= 'A' && x <= 'Z' )
		return x - 'A';
	return x - 'a' + 26;
}

inline void Print( int x )
{
	if( x < 26 )
		putchar( x + 'A' );
	else
		putchar( x + 'a' - 26 );
	return ;
}

bool G[N][N], flag;
int n, deg[N], list[M];

void DFS( int u, int k )
{
	list[k] = u;
	if( k == n )
	{
		flag = true;
		return ;
	}
	for( int v = 0; v < N; v ++ )
	{
		if( G[u][v] )
		{
			G[u][v] = G[v][u] = 0;
			DFS( v, k + 1 );
			if( flag )
				break ;
			G[u][v] = G[v][u] = 1;
		}
	}
	return ;
}

int main()
{
	scanf( "%d", &n );
	for( int i = 0; i < n; i ++ )
	{
		char s[2];
		scanf( "%s", s );
		int u = h( s[0] );
		int v = h( s[1] );
		if( !G[u][v] )
		{
			deg[u] ++, deg[v] ++;
			G[u][v] = G[v][u] = 1;
		}
	}
	int s, s1, s2, cnt;
	s1 = s2 = N, cnt = 0;
	for( int i = 0; i < N; i ++ )
	{
		if( deg[i] )
		{
			s2 = min( s2, i );
			if( deg[i] & 1 )
				s1 = min( s1, i ), cnt ++;
		}
	}
	if( cnt != 0 && cnt != 2 )
	{
		printf( "No Solution\n" );
		return 0;
	}
	if( cnt == 0 )
		s = s2;
	else
		s = s1;
	DFS( s, 0 );
	for( int i = 0; i <= n; i ++ )
		Print( list[i] );
	return 0;
}
