#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e2 + 5;

inline int in()
{
	int k = 0, c = '\0';
	for( ; c > '9' || c < '0'; )
		c = getchar();
	for( ; c >= '0' && c <= '9'; )
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

int n, m;
int emit[N];
bool G[N][N], vis[N];

bool Augment( int u )
{
    for( int v = 1; v <= n; v ++ )
    {
        if( !G[u][v] )
            continue ;
        if( !vis[v] )
        {
            vis[v] = 1;
            if( emit[v] == -1 || Augment( emit[v] ) )
            {
                emit[v] = u;
                return true;
            }
        }
    }
    return false;
}

inline int Hungarian()
{
    int sum = 0;
    memset( emit, -1, sizeof( emit ) );
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
    scanf( "%d%d", &n, &m );
    for( int i = 1; i <= m; i ++ )
    {
        int u, v;
        scanf( "%d%d", &u, &v );
        G[u][v] = 1;
    }
    for( int k = 1; k <= n; k ++ )
        for( int i = 1; i <= n; i ++ )
            for( int j = 1; j <= n; j ++ )
                G[i][j] = G[i][j] || ( G[i][k] && G[k][j] );
    int ans = n - Hungarian();
    printf( "%d\n", ans );
    return 0;
}
