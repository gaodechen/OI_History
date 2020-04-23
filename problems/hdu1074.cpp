#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<map>

using	namespace	std;
const	int N = 16, M = ( 1 << 15 );

char str[N][100];
int T, n, t[N], c[N], d[M], pre[M], cnt[M];

inline int Count( const int s )
{
	int res = 0;
	for( int i = 0; i < n; i ++ )
		if( s & ( 1 << i ) )
			res += c[i];
	return res;
}

void Print( int s )
{
	if( s == 0 )
		return ;
	Print( s & ~( 1 << pre[s] ) );
	printf( "%s\n", str[pre[s]] );
	return ;
}

int main()
{
	scanf( "%d", &T );
	while( T -- )
	{
		scanf( "%d", &n );
		for( int i = 0; i < n; i ++ )
			scanf( "%s%d%d\n", str[i], &t[i], &c[i] );
		memset( d, 0x3f, sizeof( d ) );
		memset( pre, -1, sizeof( pre ) );
		cnt[0] = d[0] = 0;
		for( int s =  1; s < ( 1 << n ); s ++ )
			cnt[s] = Count( s );
		for( int s = 0; s < ( 1 << n ); s ++ )
		{
			for( int i = 0; i < n; i ++ )
			{
				int k = 1 << i, r = 0;
				if( !( s & k ) )
				{
					if( cnt[s] + c[i] >= t[i] )
						r = cnt[s] + c[i] - t[i];
					if( d[s|k] > d[s] + r )
					{
						d[s|k] = d[s] + r;
						pre[s|k] = i;
					}
				}
			}
		}
		printf( "%d\n", d[(1<<n)-1] );
		Print( ( 1 << n ) - 1 );
	}
	return 0;
}

