#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 6e2 + 5;

bool ans[N][2];
int c, n, p1, p2, ind;
short d[N][N], pre[N], tmp[N][N], cnt[N][2], mark[N], rank[N];

int Find( int u )
{
    if( u != pre[u] )
    {
        int t = pre[u];
        pre[u] = Find( t );
        rank[u] ^= rank[t];
    }
    return pre[u];
}

int main()
{
    while( scanf( "%d%d%d", &c, &p1, &p2 ) == 3 )
    {
        if( c == 0 && p1 == 0 && p2 == 0 )
            break ;
        n = p1 + p2, ind = 0;
        memset( d, 0, sizeof( d ) );
        memset( cnt, 0, sizeof( cnt ) );
        memset( ans, 0, sizeof( ans ) );
        memset( tmp, 0, sizeof( tmp ) );
        memset( mark, 0, sizeof( mark ) );
        memset( rank, 0, sizeof( rank ) );
        for( int i = 1; i <= n; i ++ )
            pre[i] = i;
        for( int i = 0; i < c; i ++ )
        {
            int a, b;
            char buf[3];
            scanf( "%d%d%s", &a, &b, buf );
            int u = Find( a );
            int v = Find( b );
            if( u == v )
                continue ;
            pre[v] = u;
            rank[v] = rank[a] ^ rank[b];
            if( buf[0] == 'n' )
                rank[v] ^= 1;
        }
        for( int i = 1; i <= n; i ++ )
            if( Find( i ) == i )
                mark[i] = ++ ind;
        for( int i = 1; i <= n; i ++ )
        {
            mark[i] = mark[pre[i]];
            cnt[mark[i]][rank[i]] ++;
        }
        d[0][0] = 1;
        for( int i = 1; i <= ind; i ++ )
        {
            for( int j = 0; j <= n; j ++ )
            {
                if( j - cnt[i][0] >= 0 && d[i-1][j-cnt[i][0]] > 0 )
                {
                    d[i][j] += d[i-1][j-cnt[i][0]];
                    tmp[i][j] = cnt[i][0];
                }
                if( j - cnt[i][1] >= 0 && d[i-1][j-cnt[i][1]] > 0 )
                {
                    d[i][j] += d[i-1][j-cnt[i][1]];
                    tmp[i][j] = cnt[i][1];
                }
                if( d[i][j] > 2 )
                    d[i][j] = 2;
            }
        }
        if( d[ind][p1] != 1 )
        {
            printf( "no\n" );
            continue ;
        }
        for( int i = ind, j = p1; i > 0 && j > 0; i -- )
        {
            if( cnt[i][0] == tmp[i][j] )
                ans[i][0] = 1;
            else
                ans[i][1] = 1;
            j -= tmp[i][j];
        }
        for( int i = 1; i <= n; i ++ )
            if( ans[mark[i]][rank[i]] )
                printf( "%d\n", i );
        printf( "end\n" );
    }
    return 0;
}
