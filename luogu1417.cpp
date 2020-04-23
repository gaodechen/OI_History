#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
typedef	long long	data;
const	int INF = 0x3f3f3f3f;
const	int N = 51, M = 1e5 + 5;

struct Item
{
	int a, b, c;

	bool operator < ( const Item &t ) const
	{
		return ( data ) c * t.b < ( data ) b * t.c;
	}
} e[M];

data d[M];

int main()
{
	int t, n;
	scanf( "%d%d", &t, &n );
	for( int i = 1; i <= n; i ++ )
		cin >> e[i].a;
	for( int i = 1; i <= n; i ++ )
		cin >> e[i].b;
	for( int i = 1; i <= n; i ++ )
		cin >> e[i].c;
	sort( e + 1, e + n + 1 );
	for( int j = 1; j <= t; j ++ )
		d[j] = -INF;
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = t; j >= e[i].c; j -- )
		{
			if( d[j-e[i].c] != -INF )
			{
				data tmp = ( data ) e[i].a - ( data ) j * e[i].b;
				d[j] = max( d[j], d[j-e[i].c] + tmp );
			}
		}
	}
	data ans = 0;
	for( int i = 0; i <= t; i ++ )
		ans = max( ans, d[i] );
	cout << ans << endl;
	return 0;
}
