#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
typedef	long long	data;
const	int N = 1e5 + 5;

struct Item
{
	data a, b;

	bool operator < ( const Item &k ) const
	{
		return a * k.b <  b * k.a;
	}
} e[N];

int n;

int main()
{
	scanf( "%d", &n );
	for( int i = 0; i < n; i ++ )
		cin >> e[i].a >> e[i].b;
	sort( e, e + n );
	data ans = 0, t = 0;
	for( int i = 0; i < n; i ++ )
		ans += t * e[i].b, t += e[i].a;
	cout << ans * 2 << endl;
	return 0;
}
