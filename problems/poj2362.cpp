#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 100;

int t, n, len[N], mark[N], sum, side;

bool DFS( int k, int l, int p )
{
	if( k == 3 )
		return true;
	for( int i = p; i <= n; i ++ )
	{
		if( mark[i] )
			continue ;
		mark[i] = 1;
		if( l + len[i] < side && DFS( k, l + len[i], i + 1 ) )
			return true;
		else if( l + len[i] == side && DFS( k + 1, 0, 1 ) )
			return true;
		mark[i] = 0;
	}
	return false;
}

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		sum = 0;
		memset( mark, 0, sizeof( mark ) );
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%d", &len[i] );
			sum += len[i];
		}
		side = sum / 4;
		sort( len + 1, len + n + 1, greater< int >() );
		if( sum % 4 || n < 4 || len[1] > side || !DFS( 0, 0, 1 ) )
			printf( "no\n" );
		else
			printf( "yes\n" );
	}
	return 0;
}
