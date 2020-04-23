#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e5 + 5;
const   int M = 1e6 + 5;
const   int S = 6e6 + 5;
const   int INF = 0x3f3f3f3f;

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

bool mark[M];
int prime[M], g[M][2];
int n, U, tot, a[N], f[M];

void InitTable()
{
    for( int i = 2; i <= U; i ++ )
    {
        if( !mark[i] )
            prime[tot++] = i, f[i] = 1;
        for( int j = 0; j < tot && prime[j] * i <= U; j ++ )
        {
            int t = prime[j] * i;
            mark[t] = 1, f[t] = f[i] + 1;
            if( i % prime[j] == 0 )
                break ;
        }
    }
    return ;
}

inline void Print( int k )
{
    int len = 0;
    char str[11];
    while( k )
    {
        str[++len] = k % 10;
        k /= 10;
    }
    while( len )
        putchar( str[len--] + 48 );
    puts( "" );
    return ;
}  

int main()
{
    int len = fread( buf, 1, S, stdin );
    buf[len] = '\0', s = buf, n = in();
    for( int i = 1; i <= n; i ++ )
    {
        a[i] = in();
        if( a[i] > U )
            U = a[i];
    }
    InitTable();
    f[0] = INF;
    for( int i = 1; i <= n; i ++ )
    {
        for( int j = 1; j * j <= a[i]; j ++ )
        {
            if( a[i] % j )
                continue ;
            int t = 2 - ( j * j == a[i] ), k = j;
            while( t -- )
            {
                if( f[a[g[k][0]]] > f[a[i]] )
                    g[k][1] = g[k][0], g[k][0] = i;
                else if( f[a[g[k][1]]] > f[a[i]] )
                    g[k][1] = i;
                k = a[i] / j;
            }
        }
    }
    for( int i = 1; i <= n; i ++ )
    {
        int pos = INF, val = INF;
        for( int j = 1; j * j <= a[i]; j ++ )
        {
            if( a[i] % j )
                continue ;
            int k = j, t = 2 - ( j * j == a[i] );
            while( t -- )
            {
                int p = ( g[k][0] == i ), q = g[k][p];
                int dat = f[a[q]] + f[a[i]] - f[k] - f[k];
                if( dat < val || ( dat == val && q < pos ) )
                    val = dat, pos = q;
                k = a[i] / j;
            }
        }
        Print( pos );
    }
    return 0;
}
