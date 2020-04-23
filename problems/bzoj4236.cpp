#include	<cstdio>
#include	<iostream>
#include	<map>

using	namespace	std;
typedef	pair< int, int > data;
const	int N = 2e5 + 5;

char s[N];
map< data, int > m;
int n, ans, sum[N][3];

int main()
{
	scanf( "%d%s", &n, s + 1 );
	for( int i = 1; i <= n; i ++ )
	{
		switch( s[i] )
		{
			case 'J': sum[i][0] = 1; break ;
			case 'O': sum[i][1] = 1; break ;
			case 'I': sum[i][2] = 1;
		}
	}
	for( int i = 1; i <= n; i ++ )
	{
		sum[i][0] += sum[i-1][0];
		sum[i][1] += sum[i-1][1];
		sum[i][2] += sum[i-1][2];
	}
	m[data(0,0)] = 0;
	for( int i = 1; i <= n; i ++ )
	{
		data q = data( sum[i][0] - sum[i][1], sum[i][1] - sum[i][2] );
		if( m.count( q ) == 0 )
			m[q] = i;
		else
			ans = max( ans, i - m[q] );
	}
	printf( "%d\n", ans );
	return 0;
}
