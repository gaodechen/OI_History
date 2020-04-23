#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <vector>

using   namespace   std;
const   int N = 1e5 + 5;

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

int n, q, sig, head[N]; 

struct Edge {int v, next;} e[N + N];

inline void AddEdge(int u, int v)
{
    e[++ sig].v = v, e[sig].next = head[u], head[u] = sig;
}

int pre[N], dep[N], son[N], size[N];

void DFS1(int u, int p)
{
    dep[u] = dep[p] + 1, size[u] = 1, pre[u] = p;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v != p)
        {
            DFS1(v, u);
            size[u] += size[v];
            if(size[v] > size[son[u]])
                son[u] = v;
        }
    }
    return ;
}

int tik, pos[N], top[N];

void DFS2(int u, int t)
{
    pos[u] = ++ tik, top[u] = t;
    if(son[u]) DFS2(son[u], t);
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v != pre[u] && v != son[u])
            DFS2(v, v);
    }
    return ;
}

vector<int> list[N];

inline void Modify(int u, int v, int x)
{
    int a = top[u], b = top[v];
    while(a != b)
    {
        if(dep[a] < dep[b])
            swap(a, b), swap(u, v);
        list[pos[a]].push_back(x);
        list[pos[u] + 1].push_back(-x);
        u = pre[a], a = top[u];
    }
    if(dep[u] > dep[v]) swap(u, v);
    list[pos[u]].push_back(x);
    list[pos[v] + 1].push_back(-x);
    return ;
}

struct SegmentTree
{
    struct Node
    {
        int sum, num;
        Node *lson, *rson;

        inline void Update()
        {
            if(lson -> sum > rson -> sum)
                sum = lson -> sum, num = lson -> num;
            else if(lson -> sum == rson -> sum)
                sum = lson -> sum, num = lson -> num;
            else
                sum = rson -> sum, num = rson -> num;
            return ;
        }
    } *root, pool[N << 1], *T;

    inline void Initialize() {root = T = pool, T ++;}
    inline Node *NewNode() {return T ++;}

    void BuildTree(Node *p, int l, int r)
    {
        if(l == r)
            p -> sum = 0, p -> num = l;
        else
        {
            int mid = (l + r) >> 1;
            BuildTree(p -> lson = NewNode(), l, mid);
            BuildTree(p -> rson = NewNode(), mid + 1, r);
            p -> Update();
        }
        return ;
    }

    void Modify(Node *p, int l, int r, int a, int x)
    {
        if(l == r)
            p -> sum += x;
        else
        {
            int mid = (l + r) >> 1;
            if(a <= mid)
                Modify(p -> lson, l, mid, a, x);
            else
                Modify(p -> rson, mid + 1, r, a, x);
            p -> Update();
        }
        return ;
    }
} seg;

int V[N], ans[N];

int main(int argc, char **argv)
{
    while(scanf("%d%d", &n, &q) == 2 && n)
    {
        sig = tik = 0;
        memset(son, 0, sizeof(son));
        memset(head, 0, sizeof(head));
        seg.Initialize();
        int L = 100000;
        seg.BuildTree(seg.root, 1, L);
        for(int i = 1; i < n; i ++)
        {
            int u = in(), v = in();
            AddEdge(u, v), AddEdge(v, u);
        }
        for(int i = 1; i <= n; i ++)
            list[i].clear();
        DFS1(1, 0), DFS2(1, 1);
        while(q --)
        {
            int u = in(), v = in(), x = in();
            Modify(u, v, x);
        }
        for(int i = 1; i <= n; i ++)
            V[pos[i]] = i;
        for(int i = 1; i <= n; i ++)
        {
            int s = list[i].size();
            for(int j = 0; j < s; j ++)
            {
                if(list[i][j] > 0)
                    seg.Modify(seg.root, 1, L, list[i][j], 1);
                else
                    seg.Modify(seg.root, 1, L, -list[i][j], -1);
            }
            if(seg.root -> sum == 0)
                ans[V[i]] = 0;
            else
                ans[V[i]] = seg.root -> num;
        }
        for(int i = 1; i <= n; i ++)
            printf("%d\n", ans[i]);
    }
    return 0;
}

