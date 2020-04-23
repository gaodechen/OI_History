#include	<cstdio>
#include	<iostream>
#include	<algorithm>
#include	<set>
#include	<map>

using	namespace	std;
const	int N = 1e6 + 5;

int n, a[N];
set< int > numSet;
map< int, int > numMap;

int main()
{
	scanf( "%d", &n );
	for( int i = 0; i < n; i ++ )
	{
		scanf( "%d", &a[i] );
		numSet.insert( a[i] );
	}
	int m = numSet.size();
	int l = 0, r = 0, cnt = 0, ans = n;
	while( l < n )
	{
		while( r < n && cnt < m )
		{
			if( !numMap[a[r]] )
				cnt ++;
			numMap[a[r++]] ++;
		}
		if( cnt < m )
			break ;
		ans = min( ans, r - l );
		if( -- numMap[a[l++]] == 0 )
			cnt --;
	}
	printf( "%d\n", ans );
	return 0;
}
