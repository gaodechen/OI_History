#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
const	int INF = 0x3f3f3f3f;
const	int N = 101, M = 100001;

int n, m, ans, d[M], val[N], num[N];

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 && n && m )
	{
		for( int i = 1; i <= n; i ++ )
			scanf( "%d", &val[i] );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d", &num[i] );
		set( d, -1 );
		ans = d[0] = 0;
		for( int i = 1; i <= n; i ++ )
		{
			for( int j = 0; j <= m; j ++ )
			{
				if( d[j] >= 0 )
					d[j] = num[i];
				else if( j < val[i] || d[j-val[i]] == -1 )
					d[j] = -1;
				else
					d[j] = d[j-val[i]] - 1;
			}
		}
		for( int i = 1; i <= m; i ++ )
			if( d[i] >= 0 )
				ans ++;
		printf( "%d\n", ans );
	}
	return 0;
}
