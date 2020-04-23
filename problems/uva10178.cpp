#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<map>

using	namespace	std;
const	int N = 100;

int n, m, pre[N];
map< char, int > h;

int Find( int u )
{
	if( u != pre[u] )
		pre[u] = Find( pre[u] );
	return pre[u];
}

inline void Union( int u, int v )
{
	pre[Find(v)] = Find( u );
	return ;
}

inline int Hash( char c )
{
	if( !h.count( c ) )
		h[c] = h.size();
	return h[c];
}

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		h.clear();
		int cnt = n;
		for( int i = 1; i <= n; i ++ )
			pre[i] = i;
		for( int i = 0; i < m; i ++ )
		{
			char s1[1], s2[1];
			scanf( "%s%s", s1, s2 );
			int u = Hash( s1[0] );
			int v = Hash( s2[0] );
			if( Find( u ) != Find( v ) )
			{
				Union( u, v );
				cnt --;
			}
		}
		printf( "%d\n", cnt + m - n + 1 );
	}
	return 0;
}
