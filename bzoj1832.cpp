#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 5e5 + 5;
const   int K = 20, INF = 0x3f3f3f3f;

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
    int v, next;
} e[N+N];

int sig, head[N];
int n, m, dep[N], pre[N][K];

inline void AddEdge(int u, int v)
{
    e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
    return ;
}

void DFS(int u, int p)
{
    pre[u][0] = p, dep[u] = dep[p] + 1;
    for(int i = 1; i < K; i ++)
        pre[u][i] = pre[pre[u][i-1]][i-1];
    for(int i = head[u]; i; i = e[i].next)
        if(e[i].v != p)
            DFS(e[i].v, u);
    return ;
}

inline int LCA(int u, int v)
{
    if(dep[u] < dep[v])
        swap(u, v);
    int del = dep[u] - dep[v];
    if(del) for(int i = 0; i < K; i ++)
        if(del & (1 << i))
            u = pre[u][i];
    if(u == v)
        return u;
    for(int i = K - 1; i >= 0; i --)
        if(pre[u][i] != pre[v][i])
            u = pre[u][i], v = pre[v][i];
    return pre[u][0];
}

inline int abs(int x)
{
    return x > 0 ? x : -x;
}

inline int f(int u, int v, int p)
{
    return dep[u] + dep[v] - (dep[p] << 1);
}

inline void Update(int &k, int &p, int a, int b, int c)
{
    int q1 = LCA(a, b), q2 = LCA(c, q1);
    int t = f(a, b, q1) + f(c, q1, q2);
    if(t < k)
        k = t, p = q1;
    return ;
}

int main()
{
    n = in(), m = in();
    for(int i = 1; i < n; i ++)
    {
        int u = in(), v = in();
        AddEdge(u, v), AddEdge(v, u);
    }
    DFS(1, 1);
    while(m --)
    {
        int a, b, c, p, k = INF;
        a = in(), b = in(), c = in();
        Update(k, p, a, b, c);
        Update(k, p, b, c, a);
        Update(k, p, a, c, b);
        printf("%d %d\n", p, k);
    }
    return 0;
}
