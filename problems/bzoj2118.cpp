#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long data;
const int N = 5e5 + 5;
const int M = 1e7 + 5;
const data INF = 1e18;

struct Edge
{
    int v, w, next;
} e[M];

struct Item
{
    int u, d;

    Item(int u, int d): u(u), d(d)
    {
    }

    bool operator < (const Item &b) const
    {
        return d > b.d;
    }
};

bool vis[N];
data L, R, dis[N], k = INF;
int n, p, sig, a[13], head[N];

inline void AddEdge(int u, int v, int w)
{
    e[++sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

inline data Query(data s)
{
    data r = 0;
    for(int i = 0; i < k; i ++)
        if(dis[i] <= s)
            r += (s - dis[i]) / k + 1;
    return r;
}

inline void Dijkstra(int s)
{
    priority_queue<Item> q;
    for(int i = 1; i <= k; i ++)
        dis[i] = INF;
    q.push(Item(s, 0)), dis[s] = 0;
    while(!q.empty())
    {
        int u = q.top().u; q.pop();
        if(vis[u])
            continue ;
        vis[u] = 1;
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(dis[v] > dis[u] + e[i].w)
            {
                dis[v] = dis[u] + e[i].w;
                q.push(Item(v, dis[v]));
            }
        }
    }
    return ;
}

int main(int argc, char **argv)
{
    scanf("%d%lld%lld", &n, &L, &R);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d", &a[i]);
        if(k > a[i])
            k = a[i], p = i;
    }
    for(int i = 0; i < k; i ++)
        for(int j = 1; j <= n; j ++)
            if(j != p)
                AddEdge(i, (i + a[j]) % k, a[j]);
    Dijkstra(0);
    data ans = Query(R) - Query(L - 1);
    printf("%lld\n", ans);
    return 0;
}

