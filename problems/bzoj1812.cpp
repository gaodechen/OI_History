#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <vector>

using   namespace   std;
const   int N = 101, M = 51;
const   int INF = 0x3f3f3f3f;

struct Node
{
    int ind;
    Node *lson, *rson;

    Node( Node *lson = NULL, Node *rson = NULL )
    {
    }
} *node[N];

struct Edge
{
    int v, d;

    Edge( int v, int d ): v( v ), d( d )
    {
    }
};

vector< Edge > e[N];
int n, K, w[N], f[N][N][M], dis[N];

inline void AddNode( Node *p, int x )
{
    while( p -> rson != NULL )
        p = p -> rson;
    p -> rson = node[x];
    return ;
}

void DFS( int u )
{
    for( int i = 0; i < ( int ) e[u].size(); i ++ )
    {
        int v = e[u][i].v;
        dis[v] = dis[u] + e[u][i].d;
        DFS( v );
    }
    return ;
}

int DP( Node *u, int p, int k )
{
    if( !u )
        return 0;
    int ind = u -> ind;
    if( f[ind][p][k] != -1 )
        return f[ind][p][k];
    int ans = INF, tmp;
    for( int k_ = 0; k_ <= k; k_ ++ )
    {
        tmp = DP( u -> lson, p, k_ ) + DP( u -> rson, p, k - k_ );
        tmp += ( dis[ind] - dis[p] ) * w[ind];
        ans = min( ans, tmp );
    }
    for( int k_ = 0; k_ < k; k_ ++ )
    {
        tmp = DP( u -> lson, ind, k_ ) + DP( u -> rson, p, k - k_ - 1 );
        ans = min( ans, tmp );
    }
    return ( f[ind][p][k] = ans );
}

int main()
{
    memset( f, -1, sizeof( f ) );
    scanf( "%d%d", &n, &K );
    for( int i = 0; i <= n; i ++ )
    {
        node[i] = new Node();
        node[i] -> ind = i;
    }
    for( int i = 1; i <= n; i ++ )
    {
        int p, d;
        scanf( "%d%d%d", &w[i], &p, &d );
        e[p].push_back( Edge( i, d ) );
        if( node[p] -> lson )
            AddNode( node[p] -> lson, i );
        else
            node[p] -> lson = node[i];
    }
    DFS( 0 );
    int ans = DP( node[0], 0, K );
    printf( "%d\n", ans );
    return 0;
}
