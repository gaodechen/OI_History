#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;

int n, c, lim, a[10];

inline bool Check()
{
	for( int i = 1; i <= n; i ++ )
		if( a[i] != i )
			return false;
	return true;
}

inline int h()
{
	int res = 0;
	for( int i = 1; i < n; i ++ )
		if( a[i] + 1 != a[i+1] )
			res ++;
	if( a[n] != n )
		res ++;
	return res;
}

bool Search( int dep )
{
	if( dep * 3 + h() > lim * 3 )
		return false;
	if( Check() )
		return true;
	int b[10], t[10];
	memcpy( b, a, sizeof( a ) );
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = i; j <= n; j ++ )
		{
			int cnt = 0;
			for( int k = 1; k <= n; k ++ )
				if( k < i || k > j )
					t[++cnt] = a[k];
			for( int k = 1; k <= cnt + 1; k ++ )
			{
				int cnt_ = 0;
				for( int p = 1; p < k; p ++ )
					a[++cnt_] = t[p];
				for( int p = i; p <= j; p ++ )
					a[++cnt_] = b[p];
				for( int p = k; p <= cnt; p ++ )
					a[++cnt_] = t[p];
				if( Search( dep + 1 ) )
					return true;
				memcpy( a, b, sizeof( b ) );
			}
		}
	}
	return false;
}

int main()
{
	while( scanf( "%d", &n ) && n )
	{
		for( int i = 1; i <= n; i ++ )
			scanf( "%d", &a[i] );
		for( lim = 0; lim <= 5; lim ++ )
		{
			if( Search( 0 ) )
			{
				printf( "Case %d: %d\n", ++ c, lim );
				break ;
			}
		}
	}
	return 0;
}
