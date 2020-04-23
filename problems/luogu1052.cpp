#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e2 + 5;
const	int M = 2e3 + 5;
const	int INF = 0x3f3f3f3f;

bool pos[M];
int l, s, t, m, ans, del, a[N], d[M];

int main()
{
	scanf( "%d%d%d%d", &l, &s, &t, &m );
	for( int i = 1; i <= m; i ++ )
		scanf( "%d", &a[i] );
	if( s == t )
	{
		for( int i = 1; i <= m; i ++ )
			if( a[i] % t == 0 )
				ans ++;
		printf( "%d\n", ans );
		return 0;
	}
	sort( a + 1, a + m + 1 );
	for( int i = 1; i <= m; i ++ )
	{
		if( a[i] - a[i-1] > t )
			del += a[i] - a[i-1] - t;
		pos[a[i]-del] = 1;
	}
	l = a[m] - del;
	for( int i = 1; i <= l + t; i ++ )
	{
		int tmp = INF;
		for( int j = i - s; j >= i - t && j >= 0; j -- )
			if( d[j] < tmp )
				tmp = d[j];
		d[i] = tmp + pos[i];
	}
	int ans = INF;
	for( int i = l; i <= l + t; i ++ )
		if( d[i] < ans )
			ans = d[i];
	printf( "%d\n", ans );
	return 0;
}
