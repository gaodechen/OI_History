#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
typedef long long   data;
const   int N = 1e5 + 5;
const   int M = 3e5 + 5;
const   data INF = 1e18;
const   int K = 17;

struct Item
{
    int u, v, w;

    bool operator < (const Item &b) const
    {
        return w < b.w;
    }
} g[M];

struct Edge
{
    int v, w, next;
} e[M+M];

bool mark[M];
int pre[N][K], val[N][K], val2[N][K];
int n, m, sig, ufs[N], dep[N], head[N];

inline void AddEdge(int u, int v, int w)
{
    e[++sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

inline int Find(int u)
{
    if(ufs[u] != u)
        ufs[u] = Find(ufs[u]);
    return ufs[u];
}

inline void Union(int u, int v)
{
    return (void) (ufs[Find(v)] = Find(u));
}

void DFS(int u, int p, int w)
{
    pre[u][0] = p, val[u][0] = w, dep[u] = dep[p] + 1;
    for(int i = 1; i < K; i ++)
    {
        pre[u][i] = pre[pre[u][i-1]][i-1];
        val[u][i] = max(val[u][i-1], val[pre[u][i-1]][i-1]);
        if(val[u][i-1] == val[pre[u][i-1]][i-1])
            val2[u][i] = max(val2[u][i-1], val2[pre[u][i-1]][i-1]);
        else
        {
            val2[u][i] = min(val[u][i-1], val[pre[u][i-1]][i-1]);
            val2[u][i] = max(val2[u][i], max(val2[u][i-1], val2[pre[u][i-1]][i-1]));
        }
    }
    for(int i = head[u]; i; i = e[i].next)
        if(e[i].v != p)
            DFS(e[i].v, u, e[i].w);
    return ;
}

inline void Update(int &r1, int &r2, int k, int p)
{
    r1 = max(r1, k);
    if(k > r2 && k != r1)
        r2 = k;
    if(p > r2)
        r2 = p;
    return ;
}

inline int LCA(int u, int v, int k)
{
    if(dep[u] < dep[v])
        swap(u, v);
    int r1 = 0, r2 = 0;
    int del = dep[u] - dep[v];
    for(int i = 0; i < K; i ++)
    {
        if((1 << i) & del)
        {
            Update(r1, r2, val[u][i], val2[u][i]);
            u = pre[u][i];
        }
    }
    if(u == v)
        goto Mark;
    for(int i = K - 1; i >= 0; i --)
    {
        if(pre[u][i] != pre[v][i])
        {
            Update(r1, r2, val[u][i], val2[u][i]);
            Update(r1, r2, val[v][i], val2[v][i]);
            u = pre[u][i], v = pre[v][i];
        }
    }
    Update(r1, r2, val[u][0], val2[u][0]);
    Update(r1, r2, val[v][0], val2[u][0]);
Mark:
    if(r1 != k)
        return k - r1;
    return k - r2;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
        ufs[i] = i;
    for(int i = 1; i <= m; i ++)
        scanf("%d%d%d", &g[i].u, &g[i].v, &g[i].w);
    sort(g + 1, g + m + 1);
    int cnt = 0;
    data sum = 0;
    for(int i = 1; i <= m; i ++)
    {
        int u = g[i].u, v = g[i].v, w = g[i].w;
        if(Find(u) != Find(v))
        {
            Union(u, v);
            mark[i] = 1, sum += w, cnt ++;
            AddEdge(u, v, w), AddEdge(v, u, w);
            if(cnt == n - 1)
                break ;
        }
    }
    DFS(1, 0, 0);
    data ans = INF;
    for(int i = 1; i <= m; i ++)
        if(!mark[i])
            ans = min(ans, sum + LCA(g[i].u, g[i].v, g[i].w));
    printf("%lld\n", ans);
    return 0;
}
