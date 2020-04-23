#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <cmath>
#include    <vector>

using   namespace   std;
const   int N = 51, INF = 0x3f3f3f3f;

struct Point
{
    int x, y;
} e[N];

double dis[N][N];
vector< double > list;
int G[N][N], tmp[N], mark[N], ans, q, k;

bool DFS( int u, int ans_ )
{
    for( int i = u + 1; i <= q; i ++ )
    {
        if( mark[i] + ans_ <= ans )
            return 0;
        if( G[u][i] )
        {
            int j;
            for( j = 0; j < ans_; j ++ )
                if( !G[i][tmp[j]] )
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
        ans = ans_;
        return 1;
    }
    return 0;
}

int MaxClique( double lim )
{
    memset( G, 0, sizeof( G ) );
    memset( mark, 0, sizeof( mark ) );
    for( int i = 1; i <= q; i ++ )
        for( int j = 1; j <= q; j ++ )
            if( dis[i][j] >= lim )
                G[i][j] = 1;
    ans = 0;
    for( int i = q; i; i -- )
    {
        tmp[0] = i;
        DFS( i, 1 );
        mark[i] = ans;
    }
    return ans;
}

int main()
{
    while( scanf( "%d%d", &q, &k ) == 2 )
    {
        list.clear();
        for( int i = 1; i <= q; i ++ )
            scanf( "%d%d", &e[i].x, &e[i].y );
        for( int i = 1; i <= q; i ++ )
        {
            for( int j = i + 1; j <= q; j ++ )
            {
                int d1 = e[i].x - e[j].x;
                int d2 = e[i].y - e[j].y;
                dis[i][j] = dis[j][i] = sqrt( d1 * d1 + d2 * d2 );
                list.push_back( dis[i][j] );
            }
        }
        sort( list.begin(), list.end() );
        unique( list.begin(), list.end() );
        int l = 0, r = list.size() - 1;
        while( l < r )
        {
            int mid = ( l + r + 1 ) >> 1;
            if( MaxClique( list[mid] ) >= k )
                l = mid;
            else
                r = mid - 1;
        }
        printf( "%.2lf\n", list[l] );
    }
    return 0;
}
