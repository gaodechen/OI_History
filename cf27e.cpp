#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
typedef	unsigned long long data;
const	data INF = 1e18 + 9;

int n; data ans = INF;
data prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void DFS( int k, int p, data s )
{
	if( p > n )
		return ;
	if( p == n && ans > s )
	{
		ans = s;
		return ;
	}
	for( int i = 1; i <= 60; i ++ )
	{
		s *= prime[k];
		if( ans <= s )
			break ;
		DFS( k + 1, p * ( i + 1 ), s );
	}
	return ;
}

int main()
{
	cin >> n;
	DFS( 0, 1, 1 );
	cout << ans << endl;
	return 0;
}
