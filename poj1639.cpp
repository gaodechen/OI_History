#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <map>

using   namespace   std;
const   int INF = 0x3f3f3f3f;
const   int N = 55, M = 2500;

bool used[M];
map<string, int> nameID;
int pre[N], head[N];
int n, m, K, sig, comCnt;

struct Edge
{
    int u, v, w, d, next;

    bool operator < (const Edge &b) const
    {
        return w < b.w;
    }
} g[M], e[M];

inline void AddEdge(int u, int v, int w, int d)
{
    e[++sig].v = v, e[sig].w = w, e[sig].d = d;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

inline int GetID(string s)
{
    if(!nameID.count(s))
        nameID[s] = nameID.size();
    return nameID[s];
}

inline int Find(int u)
{
    if(pre[u] != u)
        pre[u] = Find(pre[u]);
    return pre[u];
}

inline void Union(int u, int v)
{
    return (void) (pre[Find(v)] = Find(u));
}

int pos[N];

void DFS(int u, int p, int d)
{
    pos[u] = d;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == p || !used[e[i].d])
            continue ;
        if(u == 1 || e[i].w <= g[d].w)
            DFS(v, u, d);
        else
            DFS(v, u, e[i].d);
    }
    return ;
}

int main()
{
    scanf("%d", &m);
    nameID["Park"] = 1;
    for(int i = 1, w; i <= m; i ++)
    {
        string s1, s2;
        cin >> s1 >> s2 >> w;
        int u = GetID(s1), v = GetID(s2);
        g[i].u = u, g[i].v = v, g[i].w = w;
    }
    n = nameID.size();
    for(int i = 1; i <= n; i ++)
        pre[i] = i;
    scanf("%d", &K);
    sort(g + 1, g + m + 1);
    for(int i = 1; i <= m; i ++)
    {
        int u = g[i].u, v = g[i].v;
        if(u == 1 || v == 1)
            continue ;
        if(Find(u) != Find(v))
        {
            Union(u, v);
            comCnt ++;
            used[i] = 1;
        }
    }
    comCnt = n - comCnt - 1;
    for(int i = m; i; i --)
    {
        int u = g[i].u, v = g[i].v, w = g[i].w;
        AddEdge(u, v, w, i), AddEdge(v, u, w, i);
    }
    for(int i = head[1]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(Find(1) != Find(v))
        {
            Union(1, v);
            used[e[i].d] = 1;
        }
    }
    if(K < comCnt)
        goto Print;
    g[0].w = -INF;
    DFS(1, 0, 0);
    for(int c = 0; c < K - comCnt; c ++)
    {
        int tmp = INF, edge = -1, edge_;
        for(int i = head[1]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(used[e[i].d])
                continue ;
            if(e[i].w - g[pos[v]].w < tmp)
            {
                tmp = e[i].w - g[pos[v]].w;
                edge = pos[v], edge_ = e[i].d;
            }
        }
        if(edge == -1 || tmp > 0)
            break ;
        used[edge] = 0;
        used[edge_] = 1;
        DFS(1, 0, 0);
    }
Print:
    int sum = 0;
    for(int i = 1; i <= m; i ++)
        if(used[i])
            sum += g[i].w;
    printf("Total miles driven: %d\n", sum);
    return 0;
}
