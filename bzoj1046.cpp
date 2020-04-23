#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e4 + 5;
const   int S = 2e6 + 5;

char buf[S], *s;

inline int in()
{
    int k = 0;
    while( *s > '9' || *s < '0' )
        s ++;
    while( *s <= '9' && *s >= '0' )
    {
        k = k * 10 + *s - '0';
        s ++;
    }
    return k;
}

int n, m, q, tik;
int a[N], d[N], f[N];

inline void Print( int l )
{
    if( l > q )
    {
        printf( "Impossible\n" );
        return ;
    }
    int last = 0, cur = 1;
    while( l )
    {
        while( a[cur] <= last || d[cur] < l )
            cur ++;
        printf( "%d", a[cur] );
        if( l > 1 )
            printf( " " );
        last = a[cur];
        l --;
    }
    printf( "\n" );
    return ;
}

inline int BinarySearch( int k )
{
    int l = 1, r = tik;
    while( l < r )
    {
        int mid = ( l + r ) >> 1;
        if( f[mid] <= k )
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

int main(int argc, char **argv)
{
    int len = fread( buf, 1, S, stdin );
    buf[len] = '\0', s = buf;
    n = in();
    for( int i = 1; i <= n; i ++ )
        a[i] = in();
    f[++ tik] = a[n], d[n] = 1;
    for( int i = n - 1; i >= 1; i -- )
    {
        int t;
        if( a[i] < f[tik] )
            t = ++ tik;
        else
            t = BinarySearch( a[i] );
        f[t] = a[i], d[i] = t;
        q = max( q, d[i] );
    }
    m = in();
    while( m -- )
        Print( in() );
    return 0;
}
