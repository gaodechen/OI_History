#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>
 
using   namespace   std;
const   int INF = 0x3f3f3f3f;
const   int N = 3700, M = 240000;
 
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
 
struct Edge
{
    int v, cap, cost, next;
} e[M+M];
 
bool inq[N];
int m, n, T[61][10], s, t;
int sig, head[N], pre[N], dis[N], h[N];
 
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
        Item tmp = q.top(); q.pop();
        int u = tmp.u;
        if(inq[u])
            continue ;
        inq[u] = 1;
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(e[i].cap > 0 && dis[v] > dis[u] + e[i].cost + h[v] - h[u])
            {
                dis[v] = dis[u] + e[i].cost + h[v] - h[u];
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
 
inline int H(int i, int j)
{
    return (i - 1) * n + j + n;
}
 
int main(int argc, char **argv)
{
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            scanf("%d", &T[i][j]);
    s = n * m + n + 1, t = s + 1;
    for(int i = 1; i <= n; i ++)
        AddEdge(s, i, 1, 0);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            for(int k = 1; k <= n; k ++)
                AddEdge(i, H(j, k), 1, k * T[i][j]);
    for(int i = 1; i <= m; i ++)
        for(int j = 1; j <= n; j ++)
            AddEdge(H(i, j), t, 1, 0);
    int ans = Compute();
    printf("%.2lf\n", (ans * 1.0) / (1.0 * n));
    return 0;
}
