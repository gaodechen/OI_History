#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 1e6 + 5;

int n, m, a, cnt[N];

int main()
{
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
	{
		scanf( "%d", &a );
		m = max( a, m );
		cnt[a] ++;
	}
	// Cannot go backwards!
	// Otherwise, you'll count repeatedly!
	for( int i = m; i + 1; i -- )
	{
		int tmp = 0;
		for( int j = i; j <= m; j += i )
			tmp += cnt[j];
		if( tmp > 1 )
		{
			printf( "%d\n", i );
			break ;
		}
	}
	return 0;
}
