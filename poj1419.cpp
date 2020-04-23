#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 105;

int t, n, m, ans, tmp[N], mark[N], group[N], G[N][N];

bool DFS( int u, int ans_ )
{
    for( int i = u + 1; i <= n; i++ )
    {
        if( mark[i] + ans_ <= ans )
            return 0;
        if( G[u][i] )
        {
            int j;
            for( j = 0; j < ans_; j ++ )
                if(!G[i][tmp[j]])
                    break ;
            if( j == ans_ )
            {
                tmp[ans_] = i;
                if( DFS( i, ans_ + 1 ) )
                    return 1;
            }
        }
    }
    if( ans_ > ans )
    {
        for( int i = 0; i < ans_; i ++ )
            group[i] = tmp[i];
        ans = ans_;
        return 1;
    }
    return 0;
}

void MaxClique()
{
    ans = 0;
    for( int i = n; i; i -- )
    {
        tmp[0] = i;
        DFS( i, 1 );
        mark[i] = ans;
    }
    return ;
}

int main()
{
    scanf( "%d", &t );
    while( t -- )
    {
        memset( G, 1, sizeof( G ) );
        scanf( "%d%d", &n, &m );
        for( int i = 0; i < m; i ++ )
        {
            int u, v;
            scanf( "%d%d", &u, &v );
            G[u][v] = G[v][u] = 0;
        }
        for( int i = 1; i <= n; i ++ )
            G[i][i] = 0;
        MaxClique();
        printf( "%d\n", ans );
        for( int i = 0; i < ans; i ++ )
            printf( i == 0 ? "%d" : " %d", group[i] );
        printf( "\n" );
    }
    return 0;
}
