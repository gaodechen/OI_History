#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
typedef long long   data;
const   int N = 1e5 + 5;

int t, n;
data a[N], b[N];

inline bool Check( data x )
{
    memcpy( b, a, sizeof( a ) );
    b[1] -= x;
    for( int i = 2; i <= n; i ++ )
    {
        if( b[i] > b[i-1] )
        {
            int d = min( b[i] - b[i-1] - 1, x );
            b[i] -= d;
        }
        else
        {
            int d = min( x, b[i-1] - b[i] + 1 );
            b[i] += d;
        }
        if( b[i] <= b[i-1] )
            return false;
    }
    return true;
}

int main()
{
    scanf( "%d", &t );
    for( int c = 1; c <= t; c ++ )
    {
        scanf( "%d", &n );
        for( int i = 1; i <= n; i ++ )
            scanf( "%lld", &a[i] );
        data l = 0, r = 1000000;
        while( l < r )
        {
            data mid = ( l + r ) / 2LL;
            if( Check( mid ) )
                r = mid;
            else
                l = mid + 1;
        }
        printf( "Case #%d:\n%lld\n", c, l );
    }
    return 0;
}
