#include    <cstdio>
#include    <iostream>

using   namespace   std;
const   int N = 1e3 + 5;

int n, a[N];

int main()
{
    scanf( "%d", &n );
    int sum = 0, k = 0;
    for( int i = 2; ; i ++ )
    {
        sum += i;
        a[++k] = i;
        if( sum + i + 1 > n )
            break ;
    }
    int tmp = n - sum;
    while( tmp )
        for( int i = k; i >= 1 && tmp; i -- )
            a[i] ++, tmp --;
    printf( "%d", a[1] );
    for( int i = 2; i <= k; i ++ )
        printf( " %d", a[i] );
    printf( "\n" );
    return 0;
}
