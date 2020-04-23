#include    <cstdio>
#include    <iostream>
#include    <algorithm>

int t, n, c[301];

int main()
{
    scanf( "%d%d", &t, &n );
    for( int i = 1; i <= n; i ++ )
        scanf( "%d", &c[i] );
    std::sort( c + 1, c + n + 1 );
    int l = 1, r = t, ans = 0;
    for( int i = n; i > 0; i -- )
    {
        ans += ( r - l ) * c[i];
        l ++, r --;
        if( l >= r )
            break ;
    }
    printf( "%d\n", ans );
    return 0;
}
