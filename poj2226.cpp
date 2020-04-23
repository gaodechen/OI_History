#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <vector>

using   namespace   std;
const   int N = 100;

bool vis[N*N];
vector< int > e[N*N];
int r, c, n, a[N][N], link[N*N], mark[2][N][N];

bool Augment( int u )
{
    for( int i = 0; i < ( int )e[u].size(); i ++ )
    {
        int &v = e[u][i];
        if( !vis[v] )
        {
            vis[v] = 1;
            if( link[v] == -1 || Augment( link[v] ) )
            {
                link[v] = u;
                return true;
            }
        }
    }
    return false;
}

int Hungarian()
{
    int sum = 0;
    memset( link, -1, sizeof( link ) );
    for( int i = 1; i <= n; i ++ )
    {
        memset( vis, 0, sizeof( vis ) );
        if( Augment( i ) )
            sum ++;
    }
    return sum;
}

int main()
{
    scanf( "%d%d", &r, &c );
    for( int i = 1; i <= r; i ++ )
    {
        char buf[N];
        scanf( "%s", buf + 1 );
        for( int j = 1; j <= c; j ++ )
            a[i][j] = buf[j] == '*';
    }
    for( int i = 1; i <= r; i ++ )
    {
        for( int j = 1; j <= c; j ++ )
        {
            if( a[i][j] )
            {
                n ++;
                int t = j;
                while( a[i][t] )
                    mark[0][i][t++] = n;
                j = t;
            }
        }
    }
    for( int j = 1; j <= c; j ++ )
    {
        for( int i = 1; i <= r; i ++ )
        {
            if( a[i][j] )
            {
                n ++;
                int t = i;
                while( a[t][j] )
                    mark[1][t++][j] = n;
                i = t;
            }
        }
    }
    for( int i = 1; i <= r; i ++ )
        for( int j = 1; j <= c; j ++ )
            if( mark[0][i][j] && mark[1][i][j] )
                e[mark[0][i][j]].push_back( mark[1][i][j] );
    printf( "%d\n", Hungarian() );
    return 0;
}
