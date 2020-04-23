#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>

using   namespace   std;
typedef pair<int, int> item;
const   int INF = 0x3f3f3f3f;
const   int N = 1501, M = N * N / 2;

bool mark[N];
int x1, y1, x2, y2, head[N];
int n, m, q, sig, tik, in[N], d[N];

struct Edge
{
    int u, v, w, next;
} e[M], g[M];

inline void AddEdge(int u, int v, int w)
{
    e[++sig].u = u, e[sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

inline int TopoSort()
{
    int ans = 0;
    queue<int> q;
    for(int i = 1; i <= n; i ++)
        if(!in[i] && mark[i])
            q.push(i);
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        ans = max(ans, d[u]);
        for(int i = head[u]; i; i = g[i].next)
        {
            int v = g[i].v;
            if(!mark[v])
                continue ;
            if(d[v] < d[u] + g[i].w)
                d[v] = d[u] + g[i].w;
            if(-- in[v] == 0)
                q.push(v);
        }
    }
    return ans;
}

inline void Dijkstra(int s, int *d)
{
    memset(d, INF, sizeof(int) * N);
    priority_queue<item> q;
    q.push(item(s, 0)), d[s] = 0;
    while(!q.empty())
    {
        item top = q.top(); q.pop();
        int u = top.first, w = top.second;
        if(d[u] < w)
            continue ;
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(d[v] > d[u] + e[i].w)
            {
                d[v] = d[u] + e[i].w;
                q.push(item(v, d[v]));
            }
        }
    }
    return ;
}

int d1[N], d2[N], d3[N], d4[N];

int main()
{
    scanf("%d%d%d%d%d%d", &n, &m, &x1, &y1, &x2, &y2);
    for(int i = 0; i < m; i ++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        AddEdge(u, v, w);
        AddEdge(v, u, w);
    }
    Dijkstra(x1, d1), Dijkstra(y1, d2);
    Dijkstra(x2, d3), Dijkstra(y2, d4);
    memset(head, 0, sizeof(head));
    for(int i = 1; i <= sig; i ++)
    {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if(d1[u] + w + d2[v] == d1[y1])
        {
            mark[u] = mark[v] = 1;
            if(d3[v] + w + d4[u] == d3[y2])
            {
                g[++tik].v = v, g[tik].w = e[i].w, in[v] ++;
                g[tik].next = head[u], head[u] = tik;
            }
            else if(d3[u] + w + d4[v] == d3[y2])
            {
                g[++tik].v = v, g[tik].w = e[i].w, in[v] ++;
                g[tik].next = head[u], head[u] = tik;
            }
        }
    }
    int ans = TopoSort();
    printf("%d\n", ans);
    return 0;
}
