#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>

#define     set( p, k )     memset( p, k, sizeof( p ) )
#define     cpy( p, k )     memcpy( p, k, sizeof( k ) )

using   namespace   std;
typedef const int & var;
const   int N = 8e2 + 5;
const   int M = 1e4 + 5;
const   int INF = 0x3f3f3f3f, R = 21;

struct Network
{
    int sig, s, t, n, head[N];
    int d[N], gap[N], cur[N], pre[N];

    struct Edge
    {
        int v, cap, next;
    } e[M+M];

    inline void Init( var x, var y, var z )
    {
        n = x, s = y, t = z;
        return ;
    }

    inline void Emit( var u, var v, var w )
    {
        e[++sig].v = v, e[sig].cap = w;
        e[sig].next = head[u], head[u] = sig;
        return ;
    }

    inline void AddEdge( var u, var v, var w )
    {
        Emit( u, v, w ), Emit( v, u, 0 );
        return ;
    }

    inline int F( var i )
    {
        return ( ( i - 1 ) ^ 1 ) + 1;
    }

    inline void BFS()
    {
        set( d, -1 ), set( gap, 0 );
        queue< int > q;
        q.push( t ), d[t] = 0;
        while( !q.empty() )
        {
            int u = q.front(); q.pop();
            gap[d[u]] ++;
            for( int i = head[u]; i; i = e[i].next )
            {
                int v = e[i].v;
                if( d[v] == -1 && e[F(i)].cap > 0 )
                {
                    d[v] = d[u] + 1;
                    q.push( v ); 
                }
            }
        }
        return ;
    }

    inline int Augment()
    {
        int sur = INF, u = t;
        while( u != s )
        {
            sur = min( e[pre[u]].cap, sur );
            u = e[F(pre[u])].v;
        }
        u = t;
        while( u != s )
        {
            e[pre[u]].cap -= sur;
            e[F(pre[u])].cap += sur;
            u = e[F(pre[u])].v;
        }
        return sur;
    }

    inline bool Advance( int &u )
    {
        bool flag = false;
        for( int &i = cur[u]; i; i = e[i].next )
        {
            int v = e[i].v;
            if( d[v] + 1 == d[u] && e[i].cap > 0 )
            {
                pre[v] = i, u = v;
                flag = true;
                break ;
            }
        }
        return flag;
    }

    inline void Retreat( int &u )
    {
        int k = n - 1;
        for( int i = head[u]; i; i = e[i].next )
            if( e[i].cap > 0 )
                k = min( k, d[e[i].v] );
        d[u] = k + 1;
        gap[d[u]] ++;
        cur[u] = head[u];
        if( u != s )
            u = e[F(pre[u])].v;
        return ;
    }

    inline int MaxFlow()
    {
        BFS();
        cpy( cur, head );
        int u = s, flow = 0;
        while( d[s] < n )
        {
            if( u == t )
            {
                flow += Augment();
                u = s;
            }
            if( !Advance( u ) )
            {
                if( -- gap[d[u]] == 0 )
                    break ;
                Retreat( u );
            }
        }
        return flow;
    }

} g;

int ind[R][R];
int n, m, d, tik, cnt;

inline void Emit( int x, int y )
{
    for( int i = 1; i <= n; i ++ )
    {
        for( int j = 1; j <= m; j ++ )
        {
            if( !ind[i][j] )
                continue ;
            int d1 = ( x - i ) * ( x - i );
            int d2 = ( y - j ) * ( y - j );
            if( d * d >= d1 + d2 )
            {
                g.AddEdge( ind[x][y] + 1, ind[i][j], INF );
            }
        }
    }
    return ;
}

int main()
{
    g.sig = 0, set( g.head, 0 );
    scanf( "%d%d%d", &n, &m, &d );
    for( int i = 1; i <= n; i ++ )
    {
        char buf[R];
        scanf( "%s", buf + 1 );
        for( int j = 1; j <= m; j ++ )
        {
            int w = buf[j] - '0';
            if( w )
            {
                ind[i][j] = ++ tik * 2;
                g.AddEdge( ind[i][j], ind[i][j] + 1, w );
            }
        }
    }
    g.Init( tik * 2 + 2, 1, tik * 2 + 2 );
    for( int i = 1; i <= n; i ++ )
    {
        for( int j = 1; j <= m; j ++ )
        {
            if( !ind[i][j] )
                continue ;
            Emit( i, j );
            if( i <= d || j <= d || i > n - d || j > m - d )
                g.AddEdge( ind[i][j] + 1, g.t, INF );
        }
    }
    for( int i = 1; i <= n; i ++ )
    {
        char buf[R];
        scanf( "%s", buf + 1 );
        for( int j = 1; j <= m; j ++ )
        {
            if( buf[j] == 'L' )
            {
                cnt ++;
                g.AddEdge( 1, ind[i][j], 1 );
            }
        }
    }
    int flow = g.MaxFlow();
    printf( "%d\n", cnt - flow );
    return 0;
}
