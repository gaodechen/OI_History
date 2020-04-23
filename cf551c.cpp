#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
typedef long long	Data;
const	int N = 1e5 + 5;

int n, m, a[N], b[N];

bool Check( Data t )
{
	Data k = n;
	memcpy( b, a, sizeof( a ) );
	for( int i = 1; i <= m; i ++ )
	{
		while( k && b[k] == 0 )
			k --;
		if( k == 0 )
			return true;
		Data tmp = k;
		while( k && b[k] + tmp <= t )
		{
			tmp += b[k];
			b[k--] = 0;
		}
		if( k == 0 )
			return true;
		b[k] -= ( t - tmp );
	}
	return false;
}

int main()
{
	Data sum = 0;
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ )
	{
		scanf( "%d", &a[i] );
		sum += i + a[i];
	}
	Data l = 0, r = sum;
	while( l < r )
	{
		Data mid = ( l + r ) >> 1;
		if( Check( mid ) )
			r = mid;
		else
			l = mid + 1;
	}
	cout << l << endl;
	return 0;
}
