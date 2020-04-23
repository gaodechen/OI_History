#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
typedef long long   data;
typedef pair<int, int> Item;
const   int N = 5e4 + 5;
const   int MOD = 201314;

int n, q, sig, head[N];

struct Edge
{
    int v, next;
} e[N];

struct Element
{
    data ans;
    int l, r, p, t;

    bool operator < (const Element &b) const
    {
        return t < b.t;
    }

    Element(int l = 0, int r = 0, int p = 0, int t = 0)
    {
        this -> t = t, this -> ans = 0;
        this -> l = l, this -> r = r, this -> p = p;
    }
} qry[N+N];

bool cmp(const Element &a, const Element &b)
{
    return a.l < b.l;
}

inline void AddEdge(int u, int v)
{
    e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
    return ;
}

int size[N], pre[N], dep[N];
int tik, pos[N], top[N], son[N];

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
    pos[u] = ++ tik, top[u] = t;
    if(son[u])
        DFS2(son[u], t);
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == son[u] || v == pre[u])
            continue ;
        DFS2(v, v);
    }
    return ;
}

struct Node
{
    int l, r;
    data sum, mark;
    Node *lson, *rson;

    inline Node *NewNode()
    {
        static Node pool[N<<1], *tail = pool;
        return tail ++;
    }

    inline void Update(int d)
    {
        sum += (r - l + 1) * d, mark += d;
        return ;
    }

    inline void PushDown()
    {
        if(mark)
        {
            lson -> Update(mark);
            rson -> Update(mark);
            mark = 0;
        }
        return ;
    }

    inline void PushUp()
    {
        sum = lson -> sum + rson -> sum;
        return ;
    }

    inline void BuildTree(int l, int r)
    {
        this -> l = l, this -> r = r;
        this -> sum = this -> mark = 0;
        if(l != r)
        {
            int mid = (l + r) >> 1;
            (lson = NewNode()) -> BuildTree(l, mid);
            (rson = NewNode()) -> BuildTree(mid + 1, r);
        }
        return ;
    }

    inline void Modify(int L, int R)
    {
        if(L <= l && R >= r)
            return (void) (Update(1));
        PushDown();
        int mid = (l + r) >> 1;
        if(L <= mid)
            lson -> Modify(L, R);
        if(R > mid)
            rson -> Modify(L, R);
        return (void) (PushUp());
    }

    inline data Query(int L, int R)
    {
        if(L <= l && R >= r)
            return sum;
        data sum = 0;
        this -> PushDown();
        int mid = (l + r) >> 1;
        if(L <= mid)
            sum += lson -> Query(L, R);
        if(R > mid)
            sum += rson -> Query(L, R);
        return sum;
    }
} *root = NULL;

inline void Modify(int u)
{
    int x = top[u];
    while(x != 1)
    {
        root -> Modify(pos[x], pos[u]);
        u = pre[x], x = top[u];
    }
    root -> Modify(pos[1], pos[u]);
    return ;
}

inline data Query(int u)
{
    int x = top[u];
    data ans = 0;
    while(x != 1)
    {
        ans += root -> Query(pos[x], pos[u]);
        u = pre[x], x = top[u];
    }
    ans += root -> Query(1, pos[u]);
    return ans % MOD;
}

int main()
{
    scanf("%d%d", &n, &q);
    for(int i = 2, v; i <= n; i ++)
    {
        scanf("%d", &v);
        AddEdge(v + 1, i);
    }
    for(int i = 1; i <= q; i ++)
    {
        int l, r, p;
        scanf("%d%d%d", &l, &r, &p);
        qry[i+i] = Element(++ r, l, ++ p, i + i);
        qry[i+i-1] = Element(l, r, p, i + i - 1);
    }
    DFS1(1, 1), DFS2(1, 1);
    root = root -> NewNode();
    root -> BuildTree(1, n);
    sort(qry + 1, qry + q + q + 1, cmp);
    int t = 0;
    while(qry[t].l == 0)
        t ++;
    for(int i = 1; i <= n; i ++)
    {
        Modify(i);
        while(qry[t].l == i)
        {
            qry[t].ans = Query(qry[t].p);
            t ++;
        }
    }
    sort(qry + 1, qry + q + q + 1);
    for(int i = 1; i <= q + q; i += 2)
        printf("%lld\n", (qry[i+1].ans - qry[i].ans + MOD) % MOD);
    return 0;
}
