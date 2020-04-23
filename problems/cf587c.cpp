#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <vector>

#define     L(u)        u -> lson
#define     R(u)        u -> rson
#define     Q(u)        u -> lson -> val

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

struct Edge {int v, next;} e[N+N];

vector<int> cost[N];
int n, m, q, head[N], dep[N], cnt[N], pre[N][K];

inline void AddEdge(int u, int v)
{
    static int sig = 0;
    e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
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

void DFS(int u, int p)
{
	dep[u] = dep[p] + 1, pre[u][0] = p, root[u] = root[p];
    for(int i = 0; i < (int) cost[u].size(); i ++)
        root[u] = Insert(root[u], 1, m, cost[u][i]);
    cnt[u] = cnt[p] + cost[u].size();
	for(int i = 1; i < K; i ++)
		pre[u][i] = pre[pre[u][i-1]][i-1];
	for(int i = head[u]; i; i = e[i].next)
		if(e[i].v != p)
			DFS(e[i].v, u);
	return ;
}
 
inline int LCA(int u, int v)
{
	if(dep[u] < dep[v])
		swap(u, v);
	int del = dep[u] - dep[v];
	for(int i = 0; i < K; i ++)
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
    if(l == r)
        return l;
    int mid = (l + r) >> 1, size = Q(u) + Q(v) - Q(a) - Q(b), ans;
    if(size >= k)
        ans = Query(L(u), L(v), L(a), L(b), l, mid, k);
    else
        ans = Query(R(u), R(v), R(a), R(b), mid + 1, r, k - size);
    return ans;
}

int main()
{
    root[0] = NewNode(0, NULL, NULL);
    root[0] -> lson = root[0] -> rson = root[0];

    n = in(), m = in(), q = in();
    for(int i = 1; i < n; i ++)
    {
        int u = in(), v = in();
        AddEdge(u, v), AddEdge(v, u);
    }
    for(int i = 1; i <= m; i ++)
    {
        int u = in();
        cost[u].push_back(i);
    }
    DFS(1, 0);
    for(int i = 0; i < q; i ++)
    {
        int u = in(), v = in(), k = in(), p = LCA(u, v);
        vector<int> list;
        int size = cnt[u] + cnt[v] - cnt[p] - cnt[pre[p][0]];
        for(int j = 1; j <= min(k, size); j ++)
        {
            int a = Query(root[u], root[v], root[p], root[pre[p][0]], 1, m, j);
            list.push_back(a);
        }
        printf("%d", (int) list.size());
        for(int j = 0; j < (int) list.size(); j ++)
            printf(" %d", list[j]);
        puts("");
    }
    return 0;
}

