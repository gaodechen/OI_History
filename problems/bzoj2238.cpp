#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>

using   namespace   std;
const   int N = 5e4 + 5;
const   int M = 1e5 + 5;

inline int in()
{
    int k = 0, c = '\0', f = 1;
    for(; c > '9' || c < '0';)
    {
        c = getchar();
        if(c == '-')
            f = 0;
    }
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return f ? k : -k;
}

struct Item
{
    int u, v, w, tik;

    bool operator < (const Item &b) const
    {
        return w < b.w;
    }
} g[M];

struct Edge
{
    int v, w, next, tik;
} e[M+M];

int n, m, q, sig, head[N], W[M];

inline void AddEdge(int u, int v, int w, int k)
{
    e[++sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
    return (void) (e[sig].tik = k);
}

int ufs[N];

int Find(int u)
{
    if(ufs[u] != u)
        ufs[u] = Find(ufs[u]);
    return ufs[u];
}

inline void Union(int u, int v)
{
    return (void) (ufs[Find(v)] = Find(u));
}

bool mark[M];

inline int Kruskal()
{
    for(int i = 1; i <= n; i ++)
        ufs[i] = i;
    int sum = 0, cnt = 0;
    sort(g + 1, g + m + 1);
    for(int i = 1; i <= m; i ++)
    {
        int u = g[i].u, v = g[i].v;
        int w = g[i].w, t = g[i].tik;
        if(Find(u) != Find(v))
        {
            Union(u, v);
            sum += g[i].w, mark[t] = 1, cnt ++;
            AddEdge(u, v, w, t), AddEdge(v, u, w, t);
        }
        if(cnt == n - 1)
            break ;
    }
    return cnt == n - 1 ? sum : -1;
}

int pre[N], dep[N], pointer[N], candidate[M];

inline void InitMST()
{
    queue<int> q;
    q.push(1);
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(v == pre[u])
                continue ;
            pre[v] = u;
            pointer[v] = e[i].tik;
            dep[v] = dep[u] + 1;
            q.push(v);
        }
    }
    return ;
}

inline void InitCandidate()
{
    memset(candidate, -1, sizeof(candidate));
    for(int i = 1; i <= n; i ++)
        ufs[i] = i;
    for(int i = 1; i <= m; i ++)
    {
        if(!mark[g[i].tik])
        {
            int u = Find(g[i].u), v = Find(g[i].v);
            while(u != v)
            {
                if(dep[u] < dep[v])
                    swap(u, v);
                candidate[pointer[u]] = g[i].w;
                ufs[u] = Find(pre[u]);
                u = Find(u);
            }
        }
    }
    return ;
}

int main()
{
    n = in(), m = in();
    for(int i = 1; i <= m; i ++)
    {
        g[i].u = in(), g[i].v = in();
        g[i].w = in(), g[i].tik = i;
        W[i] = g[i].w;
    }
    q = in();
    int mst = Kruskal();
    if(mst == -1)
    {
        while(q --)
            puts("Not connected");
        return 0;
    }
    InitMST();
    InitCandidate();
    while(q --)
    {
        int a = in();
        if(!mark[a])
            printf("%d\n", mst);
        else if(candidate[a] == -1)
            puts("Not connected");
        else
            printf("%d\n", mst - W[a] + candidate[a]);
    }
    return 0;
}
