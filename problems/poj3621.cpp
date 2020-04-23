#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 1e3 + 5;
const   int M = 1e4 + 5;

bool vis[N];
double dis[N], mid;
int n, m, sig, head[N], val[N];

struct Edge
{
    int v, w, next;
} e[M];

inline void AddEdge(int u, int v, int w)
{
    e[++sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

bool DFS(int u)
{
    vis[u] = 1;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        // Be careful here!
        double w = (double) e[i].w * mid - val[u];
        if(dis[v] > dis[u] + w)
        {
            dis[v] = dis[u] + w;
            if(vis[v])
                return true;
            if(DFS(v))
                return true;
        }
    }
    vis[u] = 0;
    return false;
}

inline bool SPFA()
{
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n; i ++)
        if(DFS(i))
            return true;
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &val[i]);
    while(m --)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        AddEdge(u, v, w);
    }
    double l = 0, r = 1000;
    while(r - l > 1e-4)
    {
        mid = (l + r) / 2.0;
        if(SPFA())
            l = mid;
        else
            r = mid;
    }
    printf("%.2f\n", l);
    return 0;
}
