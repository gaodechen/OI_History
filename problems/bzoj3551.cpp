#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 2e5 + 5;
const   int M = 5e5 + 5;
const   int K = 20;

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

struct Item
{
    int x, p;

    bool operator < (const Item &b) const
    {
        return x < b.x;
    }
} dir[N];

struct Edge
{
    int u, v, w;

    bool operator < (const Edge &b) const
    {
        return w < b.w;
    }
} g[M];

int n, m, Q, V, L, W[N], H[N], ufs[N];

struct FunctionalTree
{
    struct Node
    {
        int Count;
        Node *lson, *rson;
    } *root[N];

    inline void Initialize()
    {
        root[0] = NewNode(0, NULL, NULL);
        root[0] -> lson = root[0] -> rson = root[0];
        return ;
    }

    inline Node *NewNode(int Count, Node *a, Node *b)
    {
        static Node pool[N * K], *T = pool;
        T -> Count = Count, T -> lson = a, T -> rson = b;
        return T ++;
    }

    Node *Insert(Node *a, int l, int r, int val)
    {
        Node *p = NewNode(a -> Count + 1, a -> lson, a -> rson);
        if(l == r) return p;
        int mid = (l + r) >> 1;
        if(val <= mid)
            p -> lson = Insert(a -> lson, l, mid, val);
        else
            p -> rson = Insert(a -> rson, mid + 1, r, val);
        return p;
    }

    inline int Query(Node *a, Node *b, int l, int r, int k)
    {
        if(b -> Count - a -> Count < k) return -1;
        if(l == r) return r;
        int mid = (l + r) >> 1, size = b -> rson -> Count - a -> rson -> Count;
        if(size >= k) return Query(a -> rson, b -> rson, mid + 1, r, k);
        return Query(a -> lson, b -> lson, l, mid, k - size);
    }
} T;

int Find(int u)
{
    if(u != ufs[u])
        ufs[u] = Find(ufs[u]);
    return ufs[u];
}

int val[N], pre[N][K], lSon[N], rSon[N];
int seq[N], sideL[N], sideR[N], top;
bool vis[N];

void DFS(int u, int p)
{
    pre[u][0] = p, seq[++ top] = u;
    sideL[u] = top, vis[u] = 1;
    for(int i = 1; i < K; i ++)
        pre[u][i] = pre[pre[u][i - 1]][i - 1];
    if(lSon[u]) DFS(lSon[u], u), DFS(rSon[u], u);
    sideR[u] = top;
    return ;
}

inline void Construct()
{
    sort(g, g + m);
    T.Initialize();
    for(int i = 1; i <= n + n; i ++)
        ufs[i] = i;
    for(int i = 0; i < m; i ++)
    {
        int u = Find(g[i].u), v = Find(g[i].v);
        if(u == v) continue ;
        ufs[v] = ufs[u] = ++ V, val[V] = g[i].w;
        lSon[V] = u, rSon[V] = v;
    }
    for(int i = 1; i <= V; i ++)
        if(!vis[Find(i)]) DFS(Find(i), 0);
    for(int i = 1; i <= top; i ++)
        T.root[i] = T.Insert(T.root[i - 1], 0, L, W[seq[i]]);
    return ;
}

inline int Query(int u, int x, int k)
{
    for(int i = K - 1; i >= 0; i --)
        if(pre[u][i] && val[pre[u][i]] <= x)
            u = pre[u][i];
    int r = T.Query(T.root[sideL[u] - 1], T.root[sideR[u]], 0, L, k);
    return (r == -1 || !r) ? -1 : H[r];
}

int main(int argc, char **argv)
{
    n = in(), m = in(), Q = in(), V = n;
    for(int i = 1; i <= n; i ++)
        dir[i].x = in(), dir[i].p = i;
    sort(dir + 1, dir + n + 1);
    dir[0].x = -1;
    for(int i = 1; i <= n; i ++)
    {
        if(dir[i].x != dir[i - 1].x)
            H[++ L] = dir[i].x;
        W[dir[i].p] = L;
    }
    for(int i = 0; i < m; i ++)
        g[i].u = in(), g[i].v = in(), g[i].w = in();
    Construct();
    int last = -1;
    while(Q --)
    {
        int v = in(), x = in(), k = in();
        if(last != -1) v ^= last, x ^= last, k ^= last;
        last = Query(v, x, k);
        if(last == -1) puts("-1");
        else printf("%d\n", last);
    }
    return 0;
}
