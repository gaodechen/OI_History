#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <cmath>
#include    <queue>
#include    <vector>

using namespace	std;
typedef long long data;
const int N = 100005;
const data INF = 1e14;

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

int n, m, head[N];

inline void AddEdge(int u, int v)
{
    static int i = 0;
    e[++ i].u = u, e[i].v = v;
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

int pos[N], top[N], sig;

void DFS2(int u, int t)
{
    pos[u] = ++ sig, top[u] = t;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(son[u] == v)
            DFS2(v, t);
        else if(v != pre[u])
            DFS2(v, v);
    }
    return ;
}

int need[N];

struct SegmentTree
{
    typedef SegmentTree Node;

    data sum, mark;
    Node *lson, *rson;

    inline Node *NewNode()
    {
        static Node pool[N << 1], *T = pool;
        return T ++;
    }

    void BuildTree(int l, int r)
    {
        if(l == r) return ;
        int mid = (l + r) >> 1;
        (lson = NewNode()) -> BuildTree(l, mid);
        (rson = NewNode()) -> BuildTree(mid + 1, r);
        return ;
    }

    inline void Update()
    {
        return (void) (sum = lson -> sum + rson -> sum);
    }

    inline void PushDown(int l, int r)
    {
        if(mark == 0) return ;
        int mid = (l + r) >> 1;
        lson -> mark += mark, rson -> mark += mark;
        lson -> sum += mark * (mid - l + 1), rson -> sum += mark * (r - mid);
        return (void) (mark = 0);
    }

    void Add(int l, int r, int L, int R, int x)
    {
        if(l >= L && r <= R)
        {
            sum += (data) (r - l + 1) * x, mark += x;
            return ;
        }
        PushDown(l, r);
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

    data Query(int l, int r, int p)
    {
        if(l == r) return sum;
        int mid = (l + r) >> 1;
        PushDown(l, r);
        if(p <= mid)
            return lson -> Query(l, mid, p);
        return rson -> Query(mid + 1, r, p);
    }
} *root;

inline void Add(int a, int b, data d)
{
    int u = top[a], v = top[b];
    while(u != v)
    {
        if(dep[u] < dep[v]) swap(u, v), swap(a, b);
        root -> Add(1, n, pos[u], pos[a], d);
        a = pre[u], u = top[a];
    }
    if(dep[a] > dep[b]) swap(a, b);
    root -> Add(1, n, pos[a], pos[b], d);
    return ;
}

struct Item
{
    int u, v; data w;

    Item(int u, int v, data w): u(u), v(v), w(w) {}
    Item() {}
} add[N];

inline void DEBUG()
{
    for(int i = 1; i <= n; i ++)
        cout << root -> Query(1, n, pos[i]) << " ";
    cout << endl;
    return ;
}

int ind[N], listL[N], listR[N], ans[N];
data cur[N];

void Bisect(int l, int r, int L, int R)
{
    if(R < L) return ;
    if(l == r)
    {
        for(int i = L; i <= R; i ++)
            ans[ind[i]] = l;
        return ;
    }
    int mid = (l + r) >> 1;
    for(int i = l; i <= mid; i ++)
        Add(add[i].u, add[i].v, add[i].w);
    int posL = 0, posR = 0;
    for(int j = L; j <= R; j ++)
    {
        int i = ind[j];
        data x = root -> Query(1, n, i);
        if(cur[i] + x >= need[i])
            listL[++ posL] = i;
        else
            listR[++ posR] = i, cur[i] += x;
    }
    for(int i = l; i <= mid; i ++)
        Add(add[i].u, add[i].v, -add[i].w);
    for(int i = 0; i < posL; i ++)
        ind[L + i] = listL[i + 1];
    for(int i = 0; i < posR; i ++)
        ind[L + posL + i] = listR[i + 1];
    Bisect(l, mid, L, L + posL - 1);
    Bisect(mid + 1, r, L + posL, R);
    return ;
}

int main(int argc, char **argv)
{
    freopen("relief.in", "r", stdin);
    freopen("relief.out", "w", stdout);
    n = in(), m = in();
    for(int i = 1; i <= n; i ++)
        need[i] = in(), ind[i] = i;
    for(int i = 1; i < n; i ++)
    {
        int u = in(), v = in();
        AddEdge(u, v), AddEdge(v, u);
    }
    DFS1(1, 0), DFS2(1, 1);
    root = root -> NewNode();
    root -> BuildTree(1, n);
    for(int i = 1; i <= m; i ++)
    {
        int u = in(), v = in(), w = in();
        add[i] = Item(u, v, w);
    }
    add[++ m] = Item(1, n, INF);
    Bisect(1, m, 1, n);
    for(int i = 1; i <= n; i ++)
        ans[i] < m ? printf("%d\n", ans[i]) : puts("-1");
    return 0;
}
