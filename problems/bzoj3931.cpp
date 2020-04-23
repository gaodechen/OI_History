#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <queue>

#define     set(p, k)       memset(p, k, sizeof(p))
#define     cpy(p, q)       memcpy(p, q, sizeof(q))

using   namespace   std;
typedef long long   data;
const   int N = 1005, M = 200005;
const   data INF = 0x3f3f3f3f3f3f3f3f;

inline int in()
{
    int k = 0, c = '\0';
    for(; c > '9' || c < '0';)
        c = getchar();
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return k;
}

struct Edge
{
    struct Item
    {
        data w;
        int v, next;
    } e[M];

    int sig, head[N];

    Edge()
    {
        sig = 0, set(head, 0);
    }

    inline void Emit(int u, int v, data w)
    {
        e[++sig].v = v, e[sig].w = w;
        e[sig].next = head[u], head[u] = sig;
    }

    inline void AddEdge(int u, int v, data w)
    {
        Emit(u, v, w), Emit(v, u, 0);
    }
} g1, g;

struct Item
{
    int u; data d;

    Item(int u = 0, int d = 0): u(u), d(d)
    {
    }

    bool operator < (const Item &b) const
    {
        return d > b.d;
    }
};

int n, m, S, T;
data d1[501], d2[501];

inline void Dijkstra(int s, int t, Edge &E, data *d)
{
    bool vis[N] = {0};
    for(int i = 1; i <= n; i ++)
        d[i] = INF;
    priority_queue<Item> q;
    q.push(Item(s, 0)), d[s] = 0;
    while(!q.empty())
    {
        int u = q.top().u; q.pop();
        if(vis[u] || d[u] == INF)
            continue ;
        vis[u] = 1;
        for(int i = E.head[u]; i; i = E.e[i].next)
        {
            int v = E.e[i].v;
            if(d[v] > d[u] + E.e[i].w)
            {
                d[v] = d[u] + E.e[i].w;
                q.push(Item(v, d[v]));
            }
        }
    }
    return ;
}

struct Network
{
    int s, t, cur[N], pre[N], d[N], gap[N];

    inline void Init(int s, int t)
    {
        this -> s = s, this -> t = t;
    }

    inline int f(int x)
    {
        return ((x + 1) ^ 1) - 1;
    }

    inline void BFS()
    {
        queue<int> q;
        set(d, -1), set(gap, 0);
        q.push(t), d[t] = 0;
        while(!q.empty())
        {
            int u = q.front(); q.pop();
            gap[d[u]] ++;
            for(int i = g.head[u]; i; i = g.e[i].next)
            {
                int v = g.e[i].v;
                if(d[v] == -1 && g.e[f(i)].w > 0)
                {
                    d[v] = d[u] + 1;
                    q.push(g.e[i].v);
                }
            }
        }
        return ;
    }

    inline int Augment()
    {
        data sur = INF; int u = t;
        while(u != s)
        {
            sur = min(sur, g.e[pre[u]].w);
            u = g.e[f(pre[u])].v;
        }
        u = t;
        while(u != s)
        {
            g.e[pre[u]].w -= sur;
            g.e[f(pre[u])].w += sur;
            u = g.e[f(pre[u])].v;
        }
        return sur;
    }

    inline bool Advance(int &u)
    {
        bool r = false;
        for(int &i = cur[u]; i; i = g.e[i].next)
        {
            int v = g.e[i].v;
            if(d[v] + 1 == d[u] && g.e[i].w > 0)
            {
                pre[v] = i, u = v, r = true;
                break ;
            }
        }
        return r;
    }

    inline void Retreat(int &u)
    {
        int k = t - 1;
        for(int i = g.head[u]; i; i = g.e[i].next)
            if(g.e[i].w > 0)
                k = min(k, d[g.e[i].v]);
        d[u] = k + 1;
        gap[d[u]] ++;
        cur[u] = g.head[u];
        if(u != s)
            u = g.e[f(pre[u])].v;
        return ;
    }

    inline data MaxFlow()
    {
        BFS(), cpy(cur, g.head);
        int u = s; data flow = 0;
        while(d[s] < t)
        {
            if(u == t)
                flow += Augment(), u = s;
            if(!Advance(u))
            {
                if(-- gap[d[u]] == 0)
                    break ;
                Retreat(u);
            }
        }
        return flow;
    }
} net;

data G[501][501];

int main()
{
    n = in(), m = in();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            G[i][j] = INF;
    for(int i = 0; i < m; i ++)
    {
        int u = in(), v = in(), w = in();
        if(w < G[u][v])
            G[u][v] = G[v][u] = w;
    }
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            if(G[i][j] < INF)
                g1.Emit(i, j, G[i][j]);
    Dijkstra(1, n, g1, d1);
    Dijkstra(n, 1, g1, d2);
    for(int i = 1; i <= n; i ++)
        g.AddEdge(i, i + n, in());
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            if(G[i][j] < INF && d1[i] + G[i][j] + d2[j] == d1[n])
                g.AddEdge(i + n, j, INF);
    net.Init(S = n + 1 + 1, T = n + n + 2);
    g.AddEdge(S, n + 1, INF), g.AddEdge(n, T, INF);
    data ans = net.MaxFlow();
    printf("%lld\n", ans);
    return 0;
}
