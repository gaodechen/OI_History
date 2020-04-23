#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e5 + 5;
const   int M = 2e6 + 5;
const   int K = 17;

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
} dic[N];

struct Edge
{
    int v, next;
} e[N+N];

int sig, head[N];

inline void AddEdge(int u, int v)
{
    e[++ sig].v = v, e[sig].next = head[u], head[u] = sig;
}

struct Node
{
    int val;
    Node *lson, *rson;
} *root[N];

inline Node *NewNode(int k, Node *a, Node *b)
{
    static Node pool[M], *tail = pool;
    tail -> val = k, tail -> lson = a, tail -> rson = b;
    return tail ++;
}

Node *Insert(Node *a, int l, int r, int k)
{
    Node *p = NewNode(a -> val + 1, a -> lson, a -> rson);
    if(l != r)
    {
        int mid = (l + r) >> 1;
        if(k <= mid)
            p -> lson = Insert(a -> lson, l, mid, k);
        else
            p -> rson = Insert(a -> rson, mid + 1, r, k);
    }
    return p;
}

int n, n_, m, w[N], h[N], dep[N], pre[N][K];

inline void BFS()
{
    root[0] = NewNode(0, NULL, NULL);
    root[0] -> lson = root[0] -> rson = root[0];
    int q[N], front, tail;
    q[front = tail = 1] = dep[1] = 1;
    root[1] = Insert(root[0], 1, n, w[1]);
    while(front <= tail)
    {
        int u = q[front ++];
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(!dep[v])
            {
                q[++ tail] = v, dep[v] = dep[u] + 1, pre[v][0] = u;
                root[v] = Insert(root[u], 1, n, w[v]);
                for(int i = 1; i < K; i ++)
                    pre[v][i] = pre[pre[v][i-1]][i-1];
            }
        }
    }
    return ;
}

int LCA(int u, int v)
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

int Query(Node *u, Node *v, Node *a, Node *b, int l, int r, int k)
{
#define     L(u)        u -> lson
#define     R(u)        u -> rson
#define     Q(u)        u -> lson -> val
    if(l == r)
        return l;
    int mid = (l + r) >> 1, size = Q(u) + Q(v) - Q(a) - Q(b), ans;
    if(size >= k)
        ans = Query(L(u), L(v), L(a), L(b), l, mid, k);
    else
        ans = Query(R(u), R(v), R(a), R(b), mid + 1, r, k - size);
    return ans;
}

int main(int argc, char **argv)
{
    n_ = in(), m = in();
    dic[0].x = -1;
    for(int i = 1; i <= n_; i ++)
        dic[i] = (Item) {in(), i};
    sort(dic + 1, dic + n_ + 1);
    for(int i = 1; i <= n_; i ++)
    {
        if(dic[i].x != dic[i-1].x)
            h[++ n] = dic[i].x;
        w[dic[i].p] = n;
    }
    for(int i = 1; i < n_; i ++)
    {
        int u = in(), v = in();
        AddEdge(u, v), AddEdge(v, u);
    }
    BFS();
    int r = 0;
    while(m --)
    {
        int u = in() ^ r, v = in(), k = in(), p = LCA(u, v);
        r = Query(root[u], root[v], root[p], root[pre[p][0]], 1, n, k);
        printf("%d", r = h[r]);
        if(m) puts("");
    }
    return 0;
}
