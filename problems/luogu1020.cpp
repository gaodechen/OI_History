#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 30;

int n, ans, len = 1, a[N], d[N];

// lower_bound()
int BinarySearch( int k, int s )
{
    int l = 1, r = s;
    while( l < r )
    {
        int mid = ( l + r ) >> 1;
        if( d[mid] >= k )
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

int main()
{
	while( scanf( "%d", &a[++n] ) == 1 );
	n --;
	for( int i = 1; i <= n; i ++ )
	{
		d[i] = 1;
		for( int j = 1; j < i; j ++ )
			if( a[j] >= a[i] )
				d[i] = max( d[i], d[j] + 1 );
		ans = max( ans, d[i] );
	}
	printf( "%d\n", ans );
	memset( d, 0, sizeof( d ) );
	d[len] = a[1];
	for( int i = 2; i <= n; i ++ )
	{
		int pos;
		if( a[i] > d[len] )
			pos = ++ len;
		else
			// pos = lower_bound( d, d + len + 1, a[i] ) - d;
			pos = BinarySearch( a[i], len );
		d[pos] = a[i];
	}
	printf( "%d\n", len );
	return 0;
}
