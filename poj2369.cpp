#include    <cstdio>
#include    <iostream>

using   namespace   std;
const   int N = 1e3 + 5;

int n, a[N], vis[N];

int gcd( int a, int b )
{
    return b ? gcd( b, a % b ) : a;
}

int main()
{
    scanf( "%d", &n );
    for( int i = 1; i <= n; i ++ )
        scanf( "%d", &a[i] );
    int ans = 1;
    for( int i = 1; i <= n; i ++ )
    {
        if( vis[i] )
            continue ;
        int p = i, cnt = 0;
        while( true )
        {
            if( vis[p] )
                break ;
            vis[p] = 1;
            p = a[p];
            cnt ++;
        }
        ans *= cnt / gcd( ans, cnt );
    }
    printf( "%d\n", ans );
    return 0;
}
