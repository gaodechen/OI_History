#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
typedef long long   data;
const   int N = 21, M = 1 << 10;

int T, dig[N], k;
data d[N][M][11], a, b;

inline int Merge( int mask, int i )
{
    if( mask & ( 1 << i ) )
        return mask;
    if( mask < ( 1 << i ) )
        return mask | ( 1 << i );
    mask |= ( 1 << i );
    for( int j = i + 1; j < 10; j ++ )
        if( mask & ( 1 << j ) )
            return mask ^ ( 1 << j );
    return 0;
}

inline int Count( int n )
{
    int r = 0;
    while( n )
    {
        n &= ( n - 1 );
        r ++;
    }
    return r;
}

data Search( int x, int mask, int lim )
{
    if( !x )
        return Count( mask ) == k;
    if( !lim && d[x][mask][k] != -1 )
        return d[x][mask][k];
    int last = lim ? dig[x] : 9;
    data r = 0;
    for( int i = 0; i <= last; i ++ )
        // Leading zeros!
        r += Search( x - 1, mask || i ? Merge( mask, i ) : 0, lim && ( i == last ) );
    if( !lim )
        d[x][mask][k] = r;
    return r;
}

data F( data n )
{
    int len = 0;
    while( n )
    {
        dig[++len] = n % 10;
        n /= 10;
    }
    return Search( len, 0, 1 );
}

int main()
{
    freopen( "in", "r" , stdin );
    memset( d, -1, sizeof( d ) );
    scanf( "%d", &T );
    for( int i = 1; i <= T; i ++ )
    {
        scanf( "%lld%lld%d", &a, &b, &k );
        printf( "Case #%d: ", i );
        printf( "%lld\n", F( b ) - F( a - 1 ) );
    }
    return 0;
}
