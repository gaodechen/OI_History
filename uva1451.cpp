#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e5 + 5;

char s[N];
int n, L, t, sum[N], p[N];

inline int cmp( int a, int b, int x, int y )
{
	return ( sum[b] - sum[a-1] ) * ( y - x + 1 ) - ( sum[y] - sum[x-1] ) * ( b - a + 1 );
}

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		sum[0] = 0;
		scanf( "%d%d%s", &n, &L, s + 1 );
		for( int i = 1; i <= n; i ++ )
			sum[i] = sum[i-1] + s[i] - '0';
		int ansL = 1, ansR = L;
		int l = 0, r = 0;
		for( int t = L; t <= n; t ++ )
		{
			while( r - l > 1 && cmp( p[r-2], t - L, p[r-1], t - L ) >= 0 )
				r --;
			p[r++] = t - L + 1;
			while( r - l > 1 && cmp( p[l], t, p[l+1], t ) <= 0 )
				l ++;
			int c = cmp( p[l], t, ansL, ansR );
			if( c > 0 || ( c == 0 && t - p[l] < ansR - ansL ) )
				ansL = p[l], ansR = t;
		}
		printf( "%d %d\n", ansL, ansR );
	}
	return 0;
}
