#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
typedef long long   data;
typedef pair<int, int> item;
const   int N = 1e5 + 5;
const   int INF = 0x3f3f3f3f;

int n, q, sig, val[N], head[N];

struct Edge
{
    int v, next;
} e[N+N];

inline void AddEdge(int u, int v)
{
    e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
    return ;
}

int tik, son[N], dep[N], pre[N];
int top[N], pos[N], size[N], seq[N];

void DFS1(int u, int p)
{
    pre[u] = p, size[u] = 1, dep[u] = dep[p] + 1;
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
    top[u] = t, pos[u] = ++ tik, seq[tik] = val[u];
    if(son[u])
        DFS2(son[u], t);
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v != pre[u] && v != son[u])
            DFS2(v, v);
    }
    return ;
}

struct Node
{
    item val;
    int cnt, l, r;
    data sum, mark;
    Node *lson, *rson;

    inline Node *NewNode()
    {
        static Node pool[N<<1], *tail = pool;
        return tail ++;
    }

    inline void Update(data d)
    {
        mark += d;
        sum += (data) (r - l + 1 - cnt - cnt) * d;
        if(val.first != -INF)
            val.first += d;
        return ;
    }

    inline void PushUp()
    {
        sum = lson -> sum + rson -> sum;
        cnt = lson -> cnt + rson -> cnt;
        val = max(lson -> val, rson -> val);
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

    void BuildTree(int l, int r, int *a)
    {
        this -> l = l, this -> r = r;
        if( l == r )
        {
            if(a[l] < 0)
                val = item(a[l], l), cnt = 1;
            else
                val = item(-INF, 0), cnt = 0;
            return (void) (sum = abs(a[l]));
        }
        int mid = (l + r) >> 1;
        (lson = NewNode()) -> BuildTree(l, mid, a);
        (rson = NewNode()) -> BuildTree(mid + 1, r, a);
        return (void) (PushUp());
    }

    void Reverse(int p)
    {
        if(this -> l == this -> r)
        {
            val = item(-INF, 0), cnt = 0;
            return (void) (sum = -sum);
        }
        this -> PushDown();
        int mid = (l + r) >> 1;
        if(p <= mid)
            lson -> Reverse(p);
        else
            rson -> Reverse(p);
        return (void) (PushUp());
    }

    void Add(int L, int R, data d)
    {
        if(L <= l && R >= r)
        {
            item tmp = val;
            while(tmp.first + d >= 0)
            {
                this -> Reverse(tmp.second);
                tmp = val;
            }
            return (void) (Update(d));
        }
        int mid = (l + r) >> 1;
        this -> PushDown();
        if(L <= mid)
            lson -> Add(L, R, d);
        if(R > mid)
            rson -> Add(L, R, d);
        return (void) (PushUp());
    }

    data Query(int L, int R)
    {
        if(L <= l && R >= r)
            return sum;
        this -> PushDown();
        int mid = (l + r) >> 1;
        data r = 0;
        if(L <= mid)
            r += lson -> Query(L, R);
        if(R > mid)
            r += rson -> Query(L, R);
        return r;
    }
} *root = NULL;

inline void Add(int a, int b, int d)
{
    int u = top[a], v = top[b];
    while(u != v)
    {
        if(dep[u] < dep[v])
            swap(u, v), swap(a, b);
        root -> Add(pos[u], pos[a], d);
        a = pre[u];
        u = top[a];
    }
    if(dep[a] > dep[b])
        swap(a, b);
    root -> Add(pos[a], pos[b], d);
    return ;
}

inline data Query(int a, int b)
{
    data r = 0;
    int u = top[a], v = top[b];
    while(u != v)
    {
        if(dep[u] < dep[v])
            swap(u, v), swap(a, b);
        r += root -> Query(pos[u], pos[a]);
        a = pre[u];
        u = top[a];
    }
    if(dep[a] > dep[b])
        swap(a, b);
    r += root -> Query(pos[a], pos[b]);
    return r;
}

int main()
{
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &val[i]);
    for(int i = 1; i < n; i ++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        AddEdge(u, v);
        AddEdge(v, u);
    }
    DFS1(1, 1), DFS2(1, 1);
    root = root -> NewNode();
    root -> BuildTree(1, n, seq);
    while(q --)
    {
        int k, u, v, d;
        scanf( "%d%d%d", &k, &u, &v );
        if(k == 1)
        {
            scanf("%d", &d);
            Add(u, v, d);
        }
        else
        {
            data ans = Query(u, v);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
