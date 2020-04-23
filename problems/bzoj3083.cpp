#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;

char buf[1 << 15], *S = buf, *T = buf;
#define GetChar() (S == T && (T = (S = buf) + fread(buf, 1, 1 << 15, stdin), S == T) ? 0 : *S ++)

inline int in()
{
    int k = 0, c = '\0';
    for(; c > '9' || c < '0';)
        c = GetChar();
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = GetChar();
    }
    return k;
}

const int N = 1e5 + 5, INF = 0x3f3f3f3f;

struct Edge {int v, next;} e[N + N];

int head[N];

inline void AddEdge(int u, int v)
{
    static int i = 0;
    e[++ i].v = v, e[i].next = head[u], head[u] = i;
    return ;
}

int pre[N], dep[N], son[N], size[N];

void DFS1(int u, int p)
{
    pre[u] = p, dep[u] = dep[p] + 1, size[u] = 1;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == p) continue ;
        DFS1(v, u);
        size[u] += size[v];
        if(size[v] > size[son[u]])
            son[u] = v;
    }
    return ;
}

int tick, top[N], pos[N], last[N];

void DFS2(int u, int t)
{
    pos[u] = ++ tick, top[u] = t;
    if(son[u]) DFS2(son[u], t);
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == son[u] || v == pre[u]) continue ;
        DFS2(v, v);
    }
    last[u] = tick;
    return ;
}

struct SegmentTree
{
    typedef SegmentTree Node;

    int val;
    bool mark;
    Node *lson, *rson;

    inline Node *NewNode()
    {
        static Node pool[N << 1], *T = pool;
        return T ++;
    }

    inline void Update()
    {
        val = min(lson -> val, rson -> val);
    }

    inline void PushDown()
    {
        if(!mark) return ;
        lson -> mark = rson -> mark = 1;
        lson -> val = rson -> val = val;
        return (void) (mark = 0);
    }

    void BuildTree(int l, int r)
    {
        val = INF;
        if(l == r) return ;
        int mid = (l + r) >> 1;
        (lson = NewNode()) -> BuildTree(l, mid);
        (rson = NewNode()) -> BuildTree(mid + 1, r);
        return (void) (Update());
    }

    void Modify(int l, int r, int p, int x)
    {
        if(l == r) return (void) (val = x);
        int mid = (l + r) >> 1;
        if(p <= mid)
            lson -> Modify(l, mid, p, x);
        else
            rson -> Modify(mid + 1, r, p, x);
        return (void) (Update());
    }

    void Modify(int l, int r, int L, int R, int x)
    {
        if(L == l && R == r)
            return (void) (mark = 1, val = x);
        int mid = (l + r) >> 1;
        this -> PushDown();
        if(R <= mid)
            lson -> Modify(l, mid, L, R, x);
        else if(L > mid)
            rson -> Modify(mid + 1, r, L, R, x);
        else
        {
            lson -> Modify(l, mid, L, mid, x);
            rson -> Modify(mid + 1, r, mid + 1, R, x);
        }
        return (void) (Update());
    }

    int Query(int l, int r, int L, int R)
    {
        if(L == l && R == r) return val;
        int mid = (l + r) >> 1;
        this -> PushDown();
        if(R <= mid) return lson -> Query(l, mid, L, R);
        if(L > mid) return rson -> Query(mid + 1, r, L, R);
        int a = lson -> Query(l, mid, L, mid);
        int b = rson -> Query(mid + 1, r, mid + 1, R);
        return min(a, b);
    }
} seg;

int n, Q;

inline void Modify(int u, int v, int x)
{
    int a = top[u], b = top[v];
    while(a != b)
    {
        if(dep[a] < dep[b])
            swap(a, b), swap(u, v);
        seg.Modify(1, n, pos[a], pos[u], x);
        u = pre[a], a = top[u];
    }
    if(dep[u] < dep[v]) swap(u, v);
    seg.Modify(1, n, pos[v], pos[u], x);
    return ;
}

inline bool isSubtree(int u, int v)
{
    return pos[u] <= pos[v] && last[u] >= last[v];
}

int main(int argc, char **argv)
{
    n = in(), Q = in();
    for(int i = 1; i < n; i ++)
    {
        int u = in(), v = in();
        AddEdge(u, v), AddEdge(v, u);
    }
    DFS1(1, 0), DFS2(1, 1);
    seg.BuildTree(1, n);
    for(int i = 1; i <= n; i ++)
        seg.Modify(1, n, pos[i], in());
    int root = in();
    while(Q --)
    {
        int flag = in();
        if(flag == 1)
            root = in();
        else if(flag == 2)
        {
            int u = in(), v = in(), x = in();
            Modify(u, v, x);
        }
        else
        {
            int u = in();
            if(u == root)
                printf("%d\n", seg.val);
            else
            {
                if(isSubtree(u, root))
                {
                    int sub = -1;
                    for(int i = head[u]; i && sub == -1; i = e[i].next)
                    {
                        int v = e[i].v;
                        if(v == pre[u]) continue ;
                        if(isSubtree(v, root)) sub = v;
                    }
                    int a = seg.Query(1, n, 1, pos[sub] - 1);
                    int b = seg.Query(1, n, last[sub], n);
                    printf("%d\n", min(a, b));
                }
                else
                    printf("%d\n", seg.Query(1, n, pos[u], last[u]));
            }
        }
    }
    return 0;
}
