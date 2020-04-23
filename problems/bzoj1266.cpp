#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef	const int & var;
const	int INF = 0x3f3f3f3f;
const	int N = 503, M = 124751;

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

struct Network
{
	int sig, s, t, n, head[N];
	int d[N], gap[N], cur[N], pre[N];

	struct Edge
	{
		int v, cap, next;
	} e[M+M];

    inline void Init( var k, var x, var y )
    {
        n = k, s = x, t = y;
        sig = 0, set( head, 0 );
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
        queue< int > q;
        set( d, -1 ), set( gap, 0 );
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
            sur = min( sur, e[pre[u]].cap );
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
            if( d[u] == d[v] + 1 && e[i].cap > 0 )
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
        int u = s, flow = 0;
        cpy( cur, head );
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

int n, m, d[N][N];

struct Item
{
    int u, v, t, c;
} e[M];

int main()
{
    n = in(), m = in();
    set( d, INF );
    for( int i = 1; i <= n; i ++ )
        d[i][i] = 0;
    for( int i = 0; i < m; i ++ )
    {
        int u = in(), v = in();
        int t = in(), c = in();
        e[i].u = u, e[i].v = v;
        e[i].t = t, e[i].c = c;
        d[u][v] = d[v][u] = t;
    }
    for( int k = 1; k <= n; k ++ )
        for( int i = 1; i <= n; i ++ )
            for( int j = 1; j <= n; j ++ )
                if( d[i][k] < INF && d[k][j] < INF )
                    d[i][j] = min( d[i][j], d[i][k] + d[k][j] );
    g.Init( n, 1, n );
    for( int i = 0; i < m; i ++ )
    {
        int u = e[i].u, v = e[i].v;
        int t = e[i].t, c = e[i].c;
        if( d[1][u] + t + d[v][n] == d[1][n] )
            g.AddEdge( u, v, c );
        else if( d[1][v] + t + d[u][n] == d[1][n] )
            g.AddEdge( v, u, c );
    }
    int flow = g.MaxFlow();
    printf( "%d\n%d\n", d[1][n], flow );
    return 0;
}
