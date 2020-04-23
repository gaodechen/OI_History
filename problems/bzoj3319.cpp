#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e6 + 5;

int n, q, sig, head[N];

struct Edge
{
    int v, next, ind;
} e[N];

inline void AddEdge(int u, int v, int k)
{
    e[++sig].v = v, e[sig].ind = k;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

int tik, top[N], pos[N];
int size[N], pre[N], dep[N], son[N];

void DFS1(int u, int p)
{
    size[u] = 1, pre[u] = p, dep[u] = dep[p] + 1;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == p)
            continue ;
        DFS1(v, u);
        size[u] += size[v];
        if(size[v] > size[son[u]])
            son[u] = v;
    }
    return ;
}

void DFS2(int u, int t)
{
    top[u] = t, pos[u] = ++ tik;
    if(son[u])
        DFS2(son[u], t);
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == pre[u] || v == son[u])
            continue ;
        DFS2(v, v);
    }
    return ;
}

int main()
{
    scanf("%d%d", &n, &q);
    for(int i = 1; i < n; i ++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        AddEdge(u, v, i);
        AddEdge(v, u, i);
    }
    DFS1(1, 1), DFS2(1, 1);
    return 0;
}
