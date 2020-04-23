#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>

#define     set( p, k )     memset( p, k, sizeof( p ) )
#define     cpy( p, k )     memcpy( p, k, sizeof( k ) )

using   namespace   std;
const   int N = 1e2 + 5;
const   int M = 1e4 + 5;
const   int INF = 0x3f3f3f3f;

struct Network
{
    int sig, s, t, n, head[N];
    int d[N], gap[N], cur[N], pre[N];

    struct Edge
    {
        int v, cap, next;
    } e[M+M];

    inline void Init(int n_, int s_, int t_)
    {
        n = n_, s = s_, t = t_;
        sig = 0, set(head, 0);
        return ;
    }

    inline void Emit(int u, int v, int w)
    {
        e[++sig].v = v, e[sig].cap = w;
        e[sig].next = head[u], head[u] = sig;
        return ;
    }

    inline void AddEdge(int u, int v, int w)
    {
        Emit( u, v, w ), Emit( v, u, 0 );
        return ;
    }

    inline int F(int i)
    {
        return (( i - 1 ) ^ 1) + 1;
    }

    inline void BFS()
    {
        set(d, -1), set(gap, 0);
        queue< int > q;
        q.push(t), d[t] = 0;
        while(!q.empty())
        {
            int u = q.front(); q.pop();
            gap[d[u]] ++;
            for(int i = head[u]; i; i = e[i].next)
            {
                int v = e[i].v;
                if(d[v] == -1 && e[F(i)].cap > 0)
                {
                    d[v] = d[u] + 1;
                    q.push(v); 
                }
            }
        }
        return ;
    }

    inline int Augment()
    {
        int sur = INF, u = t;
        while(u != s)
        {
            sur = min(e[pre[u]].cap, sur);
            u = e[F(pre[u])].v;
        }
        u = t;
        while(u != s)
        {
            e[pre[u]].cap -= sur;
            e[F(pre[u])].cap += sur;
            u = e[F(pre[u])].v;
        }
        return sur;
    }

    inline bool Advance(int &u)
    {
        bool flag = false;
        for(int &i = cur[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(d[v] + 1 == d[u] && e[i].cap > 0)
            {
                pre[v] = i, u = v;
                flag = true;
                break ;
            }
        }
        return flag;
    }

    inline void Retreat(int &u)
    {
        int k = n - 1;
        for(int i = head[u]; i; i = e[i].next)
            if(e[i].cap > 0)
                k = min(k, d[e[i].v]);
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
        cpy(cur, head);
        int u = s, flow = 0;
        while(d[s] < n)
        {
            if(u == t)
            {
                flow += Augment();
                u = s;
            }
            if(!Advance( u ))
            {
                if(-- gap[d[u]] == 0)
                    break ;
                Retreat(u);
            }
        }
        return flow;
    }
} g;

struct Item
{
    int u, v, w, c, p;

    Item()
    {
    }

    Item(int u, int v, int w, int c, int p): u(u), v(v), w(w), c(c), p(p)
    {
    }
} e[M];

int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    int s = n + 1, t = n + 2;
    g.Init(n + 2, s, t);
    for(int i = 1; i <= m; i ++)
    {
        int u, v, w, c;
        scanf("%d%d%d%d", &u, &v, &w, &c);
        if(c == 0)
        {
            g.AddEdge(u, v, w);
            e[i] = Item(u, v, w, c, g.sig);
        }
        else
        {
            g.AddEdge(s, v, w);
            g.AddEdge(u, t, w);
            e[i] = Item(u, v, w, c, g.sig);
        }
    }
    g.MaxFlow(), g.AddEdge(n, 1, INF), g.MaxFlow();
    bool flag = 0;
    for(int i = g.head[s]; i; i = g.e[i].next)
    {
        if(g.e[i].cap)
        {
            flag = 1;
            break ;
        }
    }
    if(flag)
    {
        puts("Impossible");
        return 0;
    }
    int flow = g.e[g.sig].cap;
    printf("%d\n", flow);
    for(int i = 1; i <= m; i ++)
    {
        if(e[i].c)
            printf("%d ", e[i].w);
        else
            printf("%d ", g.e[e[i].p].cap);
    }
    return 0;
}
