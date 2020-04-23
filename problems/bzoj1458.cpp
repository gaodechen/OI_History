#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>

#define     set( p, k )     memset( p, k, sizeof( p ) )
#define     cpy( p, k )     memcpy( p, k, sizeof( k ) )

using   namespace   std;
const   int N = 3e2 + 5;
const   int M = 2e4 + 5;
const   int INF = 0x3f3f3f3f;

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
	int sig, head[N];
	int s, t, d[N], cur[N], gap[N], pre[N];

	struct Edge
	{
		int v, cap, next;
	} e[M];

	inline void Init( int x, int y )
	{
		set( head, 0 );
		s = x, t = y, sig = 0;
		return ;
	}

    inline void Emit(int u, int v, int w)
    {
		e[++sig].v = v, e[sig].cap = w;
		e[sig].next = head[u], head[u] = sig;
		return ;
    }

	inline void AddEdge( int u, int v, int w )
	{
		return (void) (Emit(u, v, w), Emit(v, u, 0));
	}

	inline int F( int i )
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
		bool res = false;
		for( int &i = cur[u]; i; i = e[i].next )
		{
			int &v = e[i].v;
			if( e[i].cap > 0 && d[u] == d[v] + 1 )
			{
				u = v, pre[v] = i, res = true;
				break ;
			}
		}
		return res;
	}

	inline void Retreat( int &u )
	{
		int k = t - 1;
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

	int MaxFlow()
	{
		BFS(), cpy(cur, head);
		int u = s, flow = 0;
		while( d[s] < t )
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

bool G[N][N];
int sum1[N], sum2[N];
int n, m, k, s, t, sum;

int main()
{
    n = in(), m = in(), k = in();
    for(int i = 1; i <= n; i ++)
        sum1[i] = m - in();
    for(int i = 1; i <= m; i ++)
        sum2[i] = n - in();
    for(int i = 1; i <= k; i ++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        G[x][y] = 1;
        if(-- sum1[x] < 0 || -- sum2[y] < 0)
        {
            puts("JIONG!");
            return 0;
        }
    }
    s = n + m + 1, t = n + m + 2;
    g.Init(s, t);
    for(int i = 1; i <= n; i ++)
        g.AddEdge(s, i, sum1[i]);
    for(int i = 1; i <= m; i ++)
        g.AddEdge(i + n, t, sum2[i]);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            if(!G[i][j])
                g.AddEdge(i, j + n, 1);
    printf("%d\n", n * m - k - g.MaxFlow());
    return 0;
}
