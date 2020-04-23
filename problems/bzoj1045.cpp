#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e6 + 5;

int n, a[N];
long long sum;

inline int ABS( int x )
{
    if( x < 0 )
        return -x;
    return x;
}

int main()
{
    scanf( "%d", &n );
    for( int i = 1; i <= n; i ++ )
    {
        scanf( "%d", &a[i] );
        sum += a[i];
    }
    int avg = sum / n;
    for( int i = 2; i <= n; i ++ )
        a[i] += a[i-1];
    for( int i = 1; i <= n; i ++ )
        a[i] = ( i - 1 ) * avg - a[i];
    sort( a + 1, a + n + 1 );
    int mid = a[n/2];
    sum = 0;
    for( int i = 1; i <= n; i ++ )
        sum += ABS( mid - a[i] );
    printf( "%lld\n", sum );
    return 0;
}
