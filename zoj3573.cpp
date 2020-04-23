#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int N = 2e4 + 5;
const	int INF = 0x3f3f3f3f;

int l, v[N];

int main()
{
	while( scanf( "%d", &l ) == 1 )
	{
		int a, b, w;
		memset( v, 0, sizeof( v ) );
		while( scanf( "%d%d%d", &a, &b, &w ) && a != -1 )
			v[a] += w, v[b+1] -= w;
		for( int i = 1; i <= l; i ++ )
			v[i] += v[i-1];
		int max = -INF, p, q;
		for( int i = 1; i <= l; i ++ )
		{
			if( v[i] > max )
			{
				p = q = i;
				max = v[i];
			}
			else if( v[i] == max )
				q = i;
		}
		printf( "%d %d\n", p, q );
	}
	return 0;
}
