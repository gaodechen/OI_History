#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <vector>

using   namespace   std;
const   int N = 501;

struct BPG
{
    vector< int > e[N];
    int n, link[N], vis[N], G[N][N];

    void Init( int n_ )
    {
        n = n_;
        for( int i = 0; i <= n; i ++ )
            e[i].clear();
        memset( G, false, sizeof( G ) );
        return ;
    }

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
} g;

int main()
{
    int n, m;
    while( scanf( "%d%d", &n, &m ) && n )
    {
        g.Init( n );
        for( int i = 0; i < m; i ++ )
        {
            int u, v;
            scanf( "%d%d", &u, &v );
            g.G[u][v] = 1;
        }
        for( int k = 1; k <= n; k ++ )
            for( int i = 1; i <= n; i ++ )
                for( int j = 1; j <= n; j ++ )
                    g.G[i][j] = g.G[i][j] || ( g.G[i][k] && g.G[k][j] );
        for( int i = 1; i <= n; i ++ )
            for( int j = 1; j <= n; j ++ )
                if( g.G[i][j] )
                    g.e[i].push_back( j );
        printf( "%d\n", n - g.Hungarian() );
    }
    return 0;
}
