#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 1e4 + 5;

struct Edge
{
    int v, w, next;
} e[N+N];

int n, m, sig, head[N];
int d1[N], d2[N], d[N], node[N];

inline void AddEdge(int u, int v, int w)
{
    e[++sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

void DFS1(int u, int p)
{
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v, w = e[i].w;
        if(v != p)
        {
            DFS1(v, u);
            if(d1[u] <= d1[v] + w)
            {
                d2[u] = d1[u], d1[u] = d1[v] + w;
                node[u] = v;
            }
            else if(d2[u] < d1[v] + w)
                d2[u] = d1[v] + w;
        }
    }
    return ;
}

void DFS2(int u, int p)
{
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v, w = e[i].w;
        if(v != p)
        {
            d[v] = max(d[u], node[u] == v ? d2[u] : d1[u]) + w;
            DFS2(v, u);
        }
    }
    return ;
}

int main()
{
    scanf("%d", &n);
    for(int i = 2; i <= n; i ++)
    {
        int p, w;
        scanf("%d%d", &p, &w);
        AddEdge(p, i, w);
        AddEdge(i, p, w);
    }
    DFS1(1, 0), DFS2(1, 0);
    for(int i = 1; i <= n; i ++)
        printf("%d\n", max(d1[i], d[i]));
    return 0;
}
