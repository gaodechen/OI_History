#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const   int N = 13, INF = 0x3f3f3f3f;

int n, d[N][N][N][2], dig[N];

int Search( int p, int pre, int mod, bool flag, bool lim, bool zero )
{
    if( !p )
        return flag && !mod;
    int &t = d[p][pre][mod][flag];
    if( !lim && zero && t != -1 )
        return t;
    int r = 0, last = lim ? dig[p] : 9;
    for( int i = 0; i <= last; i ++ )
    {
        int mod_ = ( 10 * mod + i ) % 13;
        bool flag_ = flag || ( pre == 1 && i == 3 );
        bool lim_ = lim && ( i == dig[p] );
        bool zero_ = zero || i;
        r += Search( p - 1, i, mod_, flag_, lim_, zero_ );
    }
    if( !lim && zero )
        t = r;
    return r;
}

int F( int n )
{
    int len = 0;
    while( n )
    {
        dig[++len] = n % 10;
        n /= 10;
    }
    dig[len+1] = 0;
    return Search( len, 0, 0, 0, 1, 0 );
}

int main()
{
    memset( d, -1, sizeof( d ) );
    while( scanf( "%d", &n ) == 1 )
    {
        int ans = F( n );
        printf( "%d\n", ans );
    }
    return 0;
}
