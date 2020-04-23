#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <vector>

using   namespace   std;
const   int N = 4e5 + 5;
const   int M = 2e5 + 5;

bool mark[N];
vector< int > e[N];
int n, m, q, cnt, pre[N];

struct Item
{
    int u, ans;
} r[M];

int Find( int u )
{
    if( u != pre[u] )
        pre[u] = Find( pre[u] );
    return pre[u];
}

inline void Union( int u, int v )
{
    pre[Find(v)] = Find( u );
    return ;
}

int main()
{
    scanf( "%d%d", &n, &m );
    for( int i = 1; i <= n; i ++ )
        pre[i] = i;
    for( int i = 0; i < m; i ++ )
    {
        int u, v;
        scanf( "%d%d", &u, &v );
        u ++, v ++;
        e[u].push_back( v );
        e[v].push_back( u );
    }
    scanf( "%d", &q );
    for( int i = 1; i <= q; i ++ )
    {
        scanf( "%d", &r[i].u );
        mark[++r[i].u] = 1;
    }
    cnt = n;
    for( int u = 1; u <= n; u ++ )
    {
        if( mark[u] )
        {
            cnt --;
            continue ;
        }
        for( int i = 0; i < ( int ) e[u].size(); i ++ )
        {
            int v = e[u][i];
            if( !mark[v] )
            {
                if( Find( u ) != Find( v ) )
                    cnt --;
                Union( u, v );
            }
        }
    }
    r[q].ans = cnt;
    for( int j = q - 1; j >= 0; j -- )
    {
        int u = r[j+1].u;
        mark[u] = 0, cnt ++;
        for( int i = 0; i < ( int ) e[u].size(); i ++ )
        {
            int v = e[u][i];
            if( mark[v] )
                continue ;
            if( Find( u ) != Find( v ) )
                cnt --;
            Union( u, v );
        }
        r[j].ans = cnt;
    }
    for( int i = 0; i <= q; i ++ )
        printf( "%d\n", r[i].ans );
    return 0;
}
