#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
const	int BUF = 1024 * 1024 * 30;
const	int N = 101, INF = 0x3f3f3f3f;

int len;
char buf[BUF], *s;

inline int Cin()
{
	int res = 0, op = 1;
	while( *s > '9' || *s < '0' )
	{
		if( *s == '-' )
			op = -1;
		s ++;
	}
	while( *s <= '9' && *s >= '0' )
	{
		res = res * 10 + *s - '0';
		s ++;
	}
	return res * op;
}

int t, n, m, pre[N], rank[N];

int Find( int u )
{
	if( u != pre[u] )
	{
		int t = pre[u];
		pre[u] = Find( t );
		rank[u] += rank[t];
	}
	return pre[u];
}

inline bool Union( int u, int v, int d )
{
	int x = Find( u );
	int y = Find( v );
	if( x == y )
		return rank[v] - rank[u] == d;
	pre[y] = x;
	rank[y] = rank[u] - rank[v] + d;
	return true;
}

int main()
{
	len = fread( buf, 1, BUF, stdin );
	s = buf, buf[len] = '\0';
	t = Cin();
	while( t -- )
	{
		n = Cin(), m = Cin();
		for( int i = 0; i <= n; i ++ )
			pre[i] = i, rank[i] = 0;
		bool flag = true;
		for( int i = 0; i < m; i ++ )
		{
			int u, v, w;
			u = Cin() - 1, v = Cin(), w = Cin();
			if( !Union( u, v, w ) )
				flag = false;
		}
		printf( "%s\n", flag ? "true" : "false" );
	}
	return 0;
}
