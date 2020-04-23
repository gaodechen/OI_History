#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <vector>

using   namespace   std;
const   int N = 1500;

struct BPG
{
    vector< int > e[N];
    int n, link[N], vis[N], G[N][N];

    void Init( int n_ )
    {
        n = n_;
        for( int i = 1; i <= n; i ++ )
            e[i].clear();
        memset( G, 0, sizeof( G ) );
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

struct Point
{
    int x, y;
};

inline int ABS( const int a )
{
    return a > 0 ? a : -a;
}

inline int Distance( const Point &a, const Point &b )
{
    return ABS( a.x - b.x ) + ABS( a.y - b.y );
}

Point s[N], t[N];
int T, m, p[N], q[N];

int main()
{
    scanf( "%d", &T );
    while( T -- )
    {
        scanf( "%d", &m );
        g.Init( m );
        for( int i = 0; i < m; i ++ )
        {
            int a, b;
            scanf( "%d:%d", &a, &b );
            scanf( "%d%d%d%d", &s[i].x, &s[i].y, &t[i].x, &t[i].y );
            int dis = Distance( s[i], t[i] );
            p[i] = a * 60 + b, q[i] = p[i] + dis;
            for( int j = 0; j < i; j ++ )
                if( q[j] + Distance( t[j], s[i] ) < p[i] )
                    g.G[j][i] = 1;
        }
        for( int i = 0; i < m; i ++ )
            for( int j = 0; j < m; j ++ )
                if( g.G[i][j] )
                    g.e[i+1].push_back( j + 1 );
        printf( "%d\n", m - g.Hungarian() );
    }
    return 0;
}
