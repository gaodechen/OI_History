#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e5 + 5;
const   int M = 5e5 + 5;

inline int in()
{
    int k = 0, c = '\0', f = 1;
    for(; c > '9' || c < '0';)
        if((c = getchar()) == '-')
            f = 0;
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return f ? k : -k;
}

struct Edge
{
    int u, v, w;

    bool operator < (const Edge &b) const {
        return w < b.w;
    }
} e[M];

struct Item
{
    int v, x, k, p;

    bool operator < (const Item &b) const {
        return x < b.x;
    }
} q[M];

namespace SplayTree
{
    struct Node
    {
        Node *pre, *son[2];
        int size, val;

        inline bool g() {return pre -> son[1] == this;}
        inline void SetChild(Node *a, int c) {this -> son[c] = a, a -> pre = this;}
        inline void Update() {size = son[0] -> size + son[1] -> size + 1;}
    };

    Node node[N], *Q[N], *null = node;

    inline void Initialize()
    {
        null -> son[0] = null -> son[1] = null -> pre = node;
    }

    inline Node *NewNode(int val)
    {
        static Node *T = node + 1;
        T -> son[0] = T -> son[1] = T -> pre = null;
        T -> size = 1, T -> val = val;
        return T ++;
    }

    inline void Rotate(Node *a)
    {
        Node *p = a -> pre;
        bool g = a -> g();
        p -> pre -> SetChild(a, p -> g());
        p -> SetChild(a -> son[!g], g);
        a -> SetChild(p, !g);
        return (void) (p -> Update());
    }

    inline void Splay(Node *a, Node *target)
    {
        while(a -> pre != target)
        {
            if(a -> pre -> pre == target)
                Rotate(a);
            else
            {
                if(a -> pre -> g() == a -> g())
                    Rotate(a -> pre), Rotate(a);
                else
                    Rotate(a), Rotate(a);
            }
        }
        return (void) (a -> Update());
    }

    int Query(Node *a, int k)
    {
        if(k > a -> size)
            return -1;
        while(a != null)
        {
            if(k <= a -> son[1] -> size)
                a = a -> son[1];
            else if(k == a -> son[1] -> size + 1)
                return a -> val;
            else
                k -= a -> son[1] -> size + 1, a = a -> son[0];
        }
        return -1;
    }

    inline Node *Insert(Node *a, Node *p)
    {
        Node *prev = p -> pre;
        while(p != null)
            prev = p, p = p -> son[p -> val < a -> val];
        a -> son[0] = a -> son[1] = a -> pre = null, a -> size = 1;
        prev -> SetChild(a, prev -> val < a -> val);
        prev -> Update(), Splay(a, null);
        return a;
    }

    void Merge(Node *a, Node *&b)
    {
        int head = 1, tail = 0;
        Q[++ tail] = a;
        while(head <= tail)
        {
            Node *t = Q[head];
            if(t -> son[0] != null) Q[++ tail] = t -> son[0];
            if(t -> son[1] != null) Q[++ tail] = t -> son[1];
            head ++;
        }
        for(head = 1; head <= tail; head ++)
            b = Insert(Q[head], b);
        return ;
    }
};

int n, m, Q, h[N], ans[M];

namespace Operate
{
    using namespace SplayTree;

    Node *root[N];
    int pre[N];

    inline void Initialize()
    {
        for(int i = 1; i <= n; i ++)
            pre[i] = i, root[i] = NewNode(h[i]);
        return ;
    }

    int Find(int x)
    {
        if(x != pre[x])
            pre[x] = Find(pre[x]);
        return pre[x];
    }

    inline void Unite(int u, int v)
    {
        u = Find(u), v = Find(v);
        if(u == v) return ;
        if(root[u] -> size < root[v] -> size)
            Merge(root[u], root[v]), pre[u] = v;
        else
            Merge(root[v], root[u]), pre[v] = u;
        return ;
    }

    inline int QueryKth(int x, int k)
    {
        return Query(root[Find(x)], k);
    }
};

int main(int argc, char **argv)
{
    n = in(), m = in(), Q = in();
    for(int i = 1; i <= n; i ++)
        h[i] = in();
    for(int i = 0; i < m; i ++)
        e[i].u = in(), e[i].v = in(), e[i].w = in();
    for(int i = 0; i < Q; i ++)
        q[i].v = in(), q[i].x = in(), q[i].k = in(), q[i].p = i;
    sort(e, e + m), sort(q, q + Q);
    Operate::Initialize();
    SplayTree::Initialize();
    for(int i = 0, j = 0; i < Q; i ++)
    {
        while(j < m && e[j].w <= q[i].x)
            Operate::Unite(e[j].u, e[j].v), j ++;
        ans[q[i].p] = Operate::QueryKth(q[i].v, q[i].k);
    }
    for(int i = 0; i < Q; i ++)
        printf("%d\n", ans[i]);
    return 0;
}
