#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int N = 10001;
const	int INF = 0x3f3f3f3f;

data ans;
int n, s, c, q, m = INF;

int main()
{
	scanf( "%d%d", &n, &s );
	for( int i = 0; i < n; i ++ )
	{
		scanf( "%d%d", &c, &q );
		m = min( m + s, c );
		ans += m * q;
	}
	cout << ans << endl;
	return 0;
}
