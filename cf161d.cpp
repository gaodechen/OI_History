#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <vector>

using   namespace   std;
const   int N = 50005, K = 505;

vector< int > e[N];
int n, k, d[N][K], sum;

void DFS( int u, int p )
{
    d[u][0] = 1;
    for( int t = 0; t < ( int ) e[u].size(); t ++ )
    {
        int v = e[u][t];
        if( v == p )
            continue ;
        DFS( v, u );
        for( int i = 0; i < k; i ++ )
            sum += d[u][i] * d[v][k-i-1];
        for( int i = 1; i <= k; i ++ )
            d[u][i] += d[v][i-1];
    }
    return ;
}

int main()
{
    scanf( "%d%d", &n, &k );
    for( int i = 1; i < n; i ++ )
    {
        int u, v;
        scanf( "%d%d", &u, &v );
        e[u].push_back( v );
        e[v].push_back( u );
    }
    DFS( 1, 0 );
    printf( "%d\n", sum );
    return 0;
}

