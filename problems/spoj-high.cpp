#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
typedef long long   data;
const   int N = 15;

data a[N][N];
int T, n, m, deg[N];

data det()
{
    data r = 1;
    for(int i = 1; i < n; i ++)
    {
        for(int j = i + 1; j < n; j ++)
        {
            while(a[j][i])
            {
                data t = a[i][i] / a[j][i];
                for(int k = i; k < n; k ++)
                    a[i][k] -= a[j][k] * t;
                for(int k = i; k < n; k ++)
                    swap(a[i][k], a[j][k]);
                r = -r;
            }
        }
        if(!a[i][i]) return 0;
        r *= a[i][i];
    }
    if(r < 0) r = -r;
    return r;
}

int main(int argc, char **argv)
{
    scanf( "%d", &T );
    while( T -- )
    {
        scanf( "%d%d", &n, &m );
        memset( a, 0, sizeof( a ) );
        memset( deg, 0, sizeof( deg ) );
        for( int i = 0; i < m; i ++ )
        {
            int u, v;
            scanf( "%d%d", &u, &v );
            u --, v --;
            a[u][v] = a[v][u] = -1;
            deg[u] ++, deg[v] ++;
        }
        for( int i = 0; i < n; i ++ )
            a[i][i] = deg[i];
        printf( "%lld\n", det() );
    }
    return 0;
}
