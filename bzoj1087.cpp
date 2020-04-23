#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long   data;
const	int N = 10, M = 100;
const	int INF = 0x3f3f3f3f;

bool G[M][M];
data d[N][M][M];
int n, k, p, state[M], cnt[M];

inline int Count( int i )
{
    int res = 0;
    while( i )
    {
        i &= ( i - 1 );
        res ++;
    }
    return res;
}

inline bool Check( int i, int j )
{
    if( i & j )
        return false;
    if( i & ( j << 1 ) )
        return false;
    if( i & ( j >> 1 ) )
        return false;
    return true;
}

int main()
{
    int n, k;
    scanf( "%d%d", &n, &k );
    for( int i = 0; i < ( 1 << n ); i ++ )
    {
        if( !( i & ( i << 1 ) ) && !( i & ( i >> 1 ) ) )
        {
            cnt[p] = Count( i );
            state[p++] = i;
        }
    }
    for( int i = 0; i < p; i ++ )
        for( int j = 0; j < p; j ++ )
            if( Check( state[i], state[j] ) )
                G[i][j] = 1;
    for( int i = 0; i < p; i ++ )
        d[1][cnt[i]][i] = 1LL;
    for( int q = 2; q <= n; q ++ )
    {
        for( int a = 0; a <= k; a ++ )
        {
            for( int i = 0; i < p; i ++ )
            {
                if( a < cnt[i] )
                    continue ;
                for( int j = 0; j < p; j ++ )
                    if( G[i][j] )
                        d[q][a][i] += d[q - 1][a - cnt[i]][j];
            }
        }
    }
    data res = 0;
    for( int i = 0; i < p; i ++ )
        res += d[n][k][i];
    printf( "%lld\n", res );
    return 0;
}
