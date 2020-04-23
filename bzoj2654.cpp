#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 5e4 + 1;
const   int M = 1e5 + 1;
const	int S = 1e7 + 5;

char buf[S], *s;

inline int in()
{
	int k = 0;
	while( *s > '9' || *s < '0' )
		s ++;
	while( *s <= '9' && *s >= '0' )
	{
		k = k * 10 + *s - '0';
		s ++;
	}
	return k;
}

int n, m, k, ans, sum;
int pre[N], tmp[N], cnt[2];

struct Edge
{
    int u, v, w, c;

    bool operator < ( const Edge &b ) const
    {
        if( w == b.w )
            return c < b.c;
        return w < b.w;
    }

} e[2][M], g[M];

int Find( int u )
{
    if( u != pre[u] )
        pre[u] = Find( pre[u] );
    return pre[u];
}

inline void MergeEdges( int d )
{
    int a = 1, b = 1, k = 0;
    while( k < m )
    {
        Edge x = e[0][a];
        Edge y = e[1][b];
        x.w += d;
        if( a <= cnt[0] && ( x < y || b > cnt[1] ) )
            g[++k] = x, a ++;
        else
            g[++k] = y, b ++;
    }
    return ;
}

inline int Check( int d )
{
    MergeEdges( d );
    memcpy( pre, tmp, sizeof( tmp ) );
    int tot = 0, cnt = 0; sum = 0;
    for( int i = 1; i <= m; i ++ )
    {
        int u = Find( g[i].u );
        int v = Find( g[i].v );
        if( u == v )
            continue ;
        pre[v] = u;
        sum += g[i].w;
        if( g[i].c == 0 )
            tot ++;
        if( ++ cnt == n - 1 )
            break ;
    }
    return tot;
}

int main()
{
	int len = fread( buf, 1, S, stdin );
    buf[len] = '\0', s = buf;
    n = in(), m = in(), k = in();
    for( int i = 1; i <= n; i ++ )
        tmp[i] = i;
    for( int i = 1; i <= m; i ++ )
    {
        int u = in(), v = in();
        int w = in(), c = in();
        int t = ++ cnt[c];
        e[c][t].w = w, e[c][t].c = c;
        e[c][t].u = ++ u, e[c][t].v = ++ v;
    }
    sort( e[0] + 1, e[0] + cnt[0] + 1 );
    sort( e[1] + 1, e[1] + cnt[1] + 1 );
    int l = -101, r = 101;
    while( l < r )
    {
        int mid = ( l + r + 1 ) >> 1;
        if( Check( mid ) >= k )
        {
            ans = sum - mid * k;
            l = mid;
        }
        else
            r = mid - 1;
    }
    printf( "%d\n", ans );
    return 0;
}
