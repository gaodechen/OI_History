#include	<cstdio>
#include	<iostream>

using	namespace	std;
typedef	unsigned long long data;
const	data INF = ~0ULL;

int T, cnt;
data n, num, prime[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 51, 53 };

void DFS( int k, int tik, data s, int lim )
{
	if( tik > cnt )
		cnt = tik, num = s;
	else if( tik == cnt && num > s )
		num = s;
	for( int i = 1; i <= lim; i ++ )
	{
		double cur = ( double ) s;
		if( cur * prime[k] > n )
			break ;
		s *= prime[k];
		DFS( k + 1, tik * ( i + 1 ), s, i );
	}
	return ;
}

int main()
{
	cin >> T;
	while( T -- )
	{
		cin >> n;
		num = INF, cnt = 0;
		DFS( 0, 1, 1, 60 );
		cout << num << " " << cnt << endl;
	}
	return 0;
}
