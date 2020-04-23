#include    <cstdio>
#include    <cstring>
#include    <sstream>
#include    <iostream>
#include    <map>

using   namespace   std;
const   int N = 5e2 + 5;
const   int INF = 0x3f3f3f3f;

map< string, int > strMap;
int n, m, cost[N], pre[N], G[N][N], d[N][N];

int GetIndex( const string &s )
{
    if( !strMap.count( s ) )
        strMap[s] = strMap.size();
    return strMap[s];
}

int DFS( int u, int f )
{
    int sum = 1;
    d[u][0] = 0;
    for( int v = 1; v <= n; v ++ )
    {
        if( !G[u][v] || v == f )
            continue ;
        int num = DFS(v, u);
        sum += num;
        for( int i = sum; i; i -- )
            for( int j = 0; j <= i && j <= num; j ++ )
                d[u][i] = min( d[u][i], d[u][i-j] + d[v][j] );
    }
    d[u][sum] = cost[u];
    return sum;
}

int main()
{
    char t[N*10];
    while( fgets( t, N * 10, stdin ) && t[0] != '#' )
    {
        strMap.clear();
        cost[0] = INF;
        memset( G, 0, sizeof( G ) );
        memset( pre, 0, sizeof( pre ) );
        memset( d, INF, sizeof( d ) );
        sscanf( t, "%d%d", &n, &m );
        for( int i = 1, w; i <= n; i ++ )
        {
            char str[N*10], buf[N*10];
            scanf( "%s%d", str, &w );
            int u = GetIndex( str );
            cost[u] = w;
            fgets( str, N * 10, stdin );
            stringstream s( str );
            while( s >> buf )
            {
                int v = GetIndex( buf );
                G[u][v] = G[v][u] = 1;
                pre[v] = u;
            }
        }
        for( int i = 1; i <= n; i ++ )
            if( !pre[i] )
                G[0][i] = G[i][0] = 1;
        DFS( 0, 0 );
        int ans = INF;
        for( int i = m; i <= n; i ++ )
            ans = min( ans, d[0][i] );
        printf( "%d\n", ans );
    }
    return 0;
}
