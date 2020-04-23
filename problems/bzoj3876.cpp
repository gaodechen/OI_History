#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <queue>

using   namespace   std;
const   int N = 3e2 + 5;
const   int M = 3e4 + 5;
const   int INF = 0x3f3f3f3f;

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

struct Item
{
    int u, d;

    Item(int u = 1, int d = 0): u(u), d(d)
    {
    }

    bool operator < (const Item &b) const
    {
        return d > b.d;
    }
};

bool inq[N];
int n, s, t, sig;
int head[N], pre[N], dis[N], h[N];

struct Edge
{
    int v, cap, cost, next;
} e[M];

inline void Emit(int u, int v, int cap, int cost)
{
    e[++sig].v = v, e[sig].cap = cap, e[sig].cost = cost;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

inline void AddEdge(int u, int v, int cap, int cost)
{
    Emit(u, v, cap, cost), Emit(v, u, 0, -cost);
    return ;
}

inline int F(int x)
{
    return ((x - 1) ^ 1) + 1;
}

inline bool Dijkstra()
{
    memset(inq, 0, sizeof(inq));
    memset(dis, INF, sizeof(dis));
    priority_queue<Item> q;
    q.push(Item(s, 0)), dis[s] = 0;
    while(!q.empty())
    {
        int u = q.top().u; q.pop();
        if(inq[u])
            continue ;
        inq[u] = 1;
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v, w = e[i].cost;
            if(dis[v] > dis[u] + w + h[v] - h[u] && e[i].cap > 0)
            {
                dis[v] = dis[u] + w + h[v] - h[u];
                q.push(Item(v, dis[v]));
                pre[v] = i;
            }
        }
    }
    return dis[t] < INF;
}

inline int Compute()
{
    int cost = 0;
    while(Dijkstra())
    {
        int sur = INF, u = t;
        while(u != s)
        {
            sur = min(sur, e[pre[u]].cap);
            u = e[F(pre[u])].v;
        }
        u = t;
        cost += sur * (dis[t] - h[t]);
        while(u != s)
        {
            e[pre[u]].cap -= sur;
            e[F(pre[u])].cap += sur;
            u = e[F(pre[u])].v;
        }
        for(int i = 1; i <= t; i ++)
            h[i] -= dis[i];
    }
    return cost;
}

int main()
{
    n = in();
    s = n + 1, t = n + 2;
    for(int i = 1; i <= n; i ++)
    {
        int k = in();
        for(int q = 1; q <= k; q ++)
        {
            int j = in(), cost = in();
            AddEdge(s, j, 1, cost);
            AddEdge(i, j, INF, cost);
        }
        AddEdge(i, t, k, 0);
        if(i != 1)
            AddEdge(i, 1, INF, 0);
    }
    printf("%d\n", Compute());
    return 0;
}
