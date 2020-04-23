#include	<cstdio>
#include	<iostream>
#include	<map>

using	namespace	std;
typedef	long long	data;
const	int N = 1e6 + 5;

int cur, t;
char exp[N];
map< data, int > tick;

void DFS( int dep )
{
	if( isdigit( exp[cur] ) )
	{
		data a = 0;
		while( isdigit( exp[cur] ) )
			a = a * 10 + exp[cur++] - '0';
		tick[a<<dep] ++;
	}
	else
	{
		cur ++, DFS( dep + 1 );
		cur ++, DFS( dep + 1 );
		cur ++;
	}
	return ;
}

int main()
{
	scanf( "%d", &t );
	while( cur = 0, tick.clear(), t -- )
	{
		scanf( "%s", exp );
		DFS( 0 );
		int sum = 0, ans = 0;
		for( map< data, int >::iterator i = tick.begin(); i != tick.end(); i ++ )
		{
			sum += i -> second;
			ans = max( ans, i -> second );
		}
		printf( "%d\n", sum - ans );
	}
	return 0;
}
