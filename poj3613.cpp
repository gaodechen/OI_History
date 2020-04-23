#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const   int N = 3e2 + 5;
const   int M = 1e4 + 5;
const	int INF = 0x3f3f3f3f;

int s, t, k, m, ind;
int G[N][N], ans[N][N], mark[M];

inline int Hash( int x )
{
    if( !mark[x] )
        mark[x] = ++ ind;
    return mark[x];
}

inline void Mul( int c[][N], int a[][N], int b[][N] )
{
    int tmp[N][N];
    set( tmp, INF );
    for( int p = 1; p <= ind; p ++ )
        for( int i = 1; i <= ind; i ++ )
            for( int j = 1; j <= ind; j ++ )
                if( tmp[i][j] > a[i][p] + b[p][j] )
                    tmp[i][j] = a[i][p] + b[p][j];
    cpy( c, tmp );
    return ;
}

inline void Pow( int p )
{
    while( p )
    {
        if( p & 1 )
            Mul( ans, ans, G );
        Mul( G, G, G );
        p >>= 1;
    }
    return ;
}

int main()
{
    scanf( "%d%d%d%d", &k, &m, &s, &t );
    set( ans, INF ), set( G, INF );
    for( int i = 0; i < N; i ++ )
        ans[i][i] = 0;
    for( int i = 0; i < m; i ++ )
    {
        int u, v, w;
        scanf( "%d%d%d", &w, &u, &v );
        u = Hash( u ), v = Hash( v );
        G[u][v] = G[v][u] = w;
    }
    Pow( k );
    s = mark[s], t = mark[t];
    printf( "%d\n", ans[s][t] );
    return 0;
}
