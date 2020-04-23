#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 2e5 + 5;

int father[N], val[N];

int Find( int a )
{
	if( a != father[a] )
	{
		int pre = father[a];
		father[a] = Find( father[a] );
		val[a] += val[pre];
	}
	return father[a];
}

bool Union( int a, int b, int c )
{
	int a_ = Find( a );
	int b_ = Find( b );
	if( a_ == b_ )
	{
		if( val[b] - val[a] == c )
			return 1;
		return 0;
	}
	father[b_] = a_;
	val[b_] = val[a] - val[b] + c;
	return true;
}

int main()
{
	int n, m;
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		int ans = 0;
		for( int i = 0; i <= n; i ++ )
			father[i] = i, val[i] = 0;
		for( int i = 1; i <= m; i ++ )
		{
			int a, b, c;
			scanf( "%d%d%d", &a, &b, &c );
			if( Union( a - 1, b, c ) == 0 )
				ans ++;
		}
		printf( "%d\n", ans );
	}
	return 0;
}
