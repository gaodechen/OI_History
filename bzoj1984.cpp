#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int N = 100005;
const int INF = 0x3f3f3f3f;

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

struct Edge {int u, v, w, next;} e[N + N];

int n, head[N];

inline void AddEdge(int u, int v, int w)
{
    static int i = 0;
    e[++ i].u = u, e[i].v = v, e[i].w = w;
    e[i].next = head[u], head[u] = i;
    return ;
}

int son[N], pre[N], dep[N], size[N];

void DFS1(int u, int p)
{
    size[u] = 1, pre[u] = p, dep[u] = dep[p] + 1;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == p) continue ;
        DFS1(v, u), size[u] += size[v];
        if(size[v] > size[son[u]])
            son[u] = v;
    }
    return ;
}

int pos[N], top[N], W[N], sig;

void DFS2(int u, int t, int w)
{
    pos[u] = ++ sig, W[sig] = w, top[u] = t;
    if(son[u])
    {
        int temp;
        for(int i = head[u]; i; i = e[i].next) if(e[i].v == son[u])
        {
            temp = e[i].w;
            break ;
        }
        DFS2(son[u], t, temp);
    }
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v != pre[u] && v != son[u])
            DFS2(v, v, e[i].w);
    }
    return ;
}

struct SegmentTree
{
    typedef SegmentTree Node;

    int maxVal, add, cov;
    Node *lson, *rson;

    inline Node *NewNode()
    {
        static Node pool[N << 1], *T = pool;
        return T ++;
    }

    inline void Update()
    {
        return (void) (maxVal = max(lson -> maxVal, rson -> maxVal));
    }

    void BuildTree(int l, int r)
    {
        cov = -1;
        if(l == r) return (void) (maxVal = W[l]);
        int mid = (l + r) >> 1;
        (lson = NewNode()) -> BuildTree(l, mid);
        (rson = NewNode()) -> BuildTree(mid + 1, r);
        return (void) (Update());
    }

    inline void PushDown()
    {
        if(add != 0)
        {
            lson -> maxVal += add;
            rson -> maxVal += add;
            if(lson -> cov != -1)
                lson -> cov += add;
            else
                lson -> add += add;
            if(rson -> cov != -1)
                rson -> cov += add;
            else
                rson -> add += add;
            add = 0;
        }
        if(cov != -1)
        {
            lson -> maxVal = rson -> maxVal = cov;
            lson -> cov = rson -> cov = cov, cov = -1;
        }
        return ;
    }

    void Modify(int l, int r, int p, int x)
    {
        if(l != r) PushDown();
        if(l == r) return (void) (maxVal = x);
        int mid = (l + r) >> 1;
        if(p <= mid)
            lson -> Modify(l, mid, p, x);
        else
            rson -> Modify(mid + 1, r, p, x);
        return (void) (Update());
    }

    void Cover(int l, int r, int L, int R, int x)
    {
        if(l != r) PushDown();
        if(l == L && r == R)
            return (void) (maxVal = cov = x);
        int mid = (l + r) >> 1;
        if(R <= mid)
            lson -> Cover(l, mid, L, R, x);
        else if(L > mid)
            rson -> Cover(mid + 1, r, L, R, x);
        else
        {
            lson -> Cover(l, mid, L, mid, x);
            rson -> Cover(mid + 1, r, mid + 1, R, x);
        }
        return (Update());
    }

    void Add(int l, int r, int L, int R, int x)
    {
        if(l != r) PushDown();
        if(l == L && r == R)
            return (void) (maxVal += x, add = x);
        int mid = (l + r) >> 1;
        if(R <= mid)
            lson -> Add(l, mid, L, R, x);
        else if(L > mid)
            rson -> Add(mid + 1, r, L, R, x);
        else
        {
            lson -> Add(l, mid, L, mid, x);
            rson -> Add(mid + 1, r, mid + 1, R, x);
        }
        return (Update());
    }

    int Query(int l, int r, int L, int R)
    {
        if(l == L && r == R) return maxVal;
        if(l != r) PushDown();
        int mid = (l + r) >> 1;
        if(R <= mid)
            return lson -> Query(l, mid, L, R);
        if(L > mid)
            return rson -> Query(mid + 1, r, L, R);
        int a = lson -> Query(l, mid, L, mid);
        int b = rson -> Query(mid + 1, r, mid + 1, R);
        return max(a, b);
    }
} *seg;

inline void Add(int u, int v, int w)
{
    int a = top[u], b = top[v];
    while(a != b)
    {
        if(dep[a] < dep[b]) swap(a, b), swap(u, v);
        seg -> Add(1, n, pos[a], pos[u], w);
        u = pre[a], a = top[u];
    }
    if(dep[u] < dep[v]) swap(u, v);
    if(pos[v] + 1 <= pos[u])
        seg -> Add(1, n, pos[v] + 1, pos[u], w);
    return ;
}

inline int Query(int u, int v)
{
    int a = top[u], b = top[v], r = -INF;
    while(a != b)
    {
        if(dep[a] < dep[b]) swap(a, b), swap(u, v);
        r = max(r, seg -> Query(1, n, pos[a], pos[u]));
        u = pre[a], a = top[u];
    }
    if(dep[u] < dep[v]) swap(u, v);
    if(pos[v] + 1 <= pos[u])
        r = max(r, seg -> Query(1, n, pos[v] + 1, pos[u]));
    return r;
}

inline void Cover(int u, int v, int w)
{
    int a = top[u], b = top[v];
    while(a != b)
    {
        if(dep[a] < dep[b]) swap(a, b), swap(u, v);
        seg -> Cover(1, n, pos[a], pos[u], w);
        u = pre[a], a = top[u];
    }
    if(dep[u] < dep[v]) swap(u, v);
    if(pos[v] + 1 <= pos[u])
        seg -> Cover(1, n, pos[v] + 1, pos[u], w);
    return ;
}

int main(int argc, char **argv)
{
    n = in();
    for(int i = 1; i < n; i ++)
    {
        int u = in(), v = in(), w = in();
        AddEdge(u, v, w), AddEdge(v, u, w);
    }
    DFS1(1, 0), DFS2(1, 1, 0);
    seg = seg -> NewNode();
    seg -> BuildTree(1, n);
    char cmd[7];
    while(scanf("%s", cmd) == 1 && cmd[0] != 'S')
    {
        if(cmd[0] == 'M')
            printf("%d\n", Query(in(), in()));
        else if(cmd[0] == 'C' && cmd[1] == 'o')
        {
            int u = in(), v = in(), w = in();
            Cover(u, v, w);
        }
        else if(cmd[0] == 'C' && cmd[1] == 'h')
        {
            int k = in() * 2, x = in(), u = e[k].u, v = e[k].v;
            if(dep[u] < dep[v]) swap(u, v);
            seg -> Modify(1, n, pos[u], x);
        }
        else if(cmd[0] == 'A')
        {
            int u = in(), v = in(), w = in();
            Add(u, v, w);
        }
    }
    return 0;
}
