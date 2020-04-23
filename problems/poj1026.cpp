#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 205;

char s[N], g[N];
int n, k, a[N], w[N];

void Compute()
{
    for( int i = 1; i <= n; i ++ )
    {
        int cnt = 1, p = a[i];
        while( p != i )
        {
            p = a[p];
            cnt ++;
        }
        w[i] = cnt;
    }
    return ;
}

int main()
{
    while( scanf( "%d", &n ) && n )
    {
        for( int i = 1; i <= n; i ++ )
            scanf( "%d", &a[i] );
        Compute();
        while( scanf( "%d", &k ) && k )
        {
            getchar();
            cin.get( s + 1, N );
            int l = strlen( s + 1 );
            for( int i = l + 1; i <= n; i ++ )
                s[i] = ' ';
            s[n+1] = '\0';
            for( int i = 1; i <= n; i ++ )
            {
                int p = i;
                for( int j = 0; j < k % w[i]; j ++ )
                    p = a[p];
                g[p] = s[i];
            }
            g[n + 1] = '\0';
            puts(g + 1);
        }
        puts("");
    }
    return 0;
}
