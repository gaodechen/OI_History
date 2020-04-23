#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 9e4 + 5;
const	int K = 17;

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

struct ItemD
{
	int x, p;
	
	bool operator < (const ItemD &b) const
	{
		return x < b.x;
	}
} dic[N<<1];

struct ItemQ {int u, v, k;} q[N];

struct Edge {int v, next;} e[N<<1];

int sig, head[N];

inline void AddEdge(int u, int v)
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
}
	
struct Node
{
	int sum;
	Node *lson, *rson;
};
	
struct SegmentTree
{
    Node *root[N];

	SegmentTree()
    {
        root[0] = NewNode(NULL, NULL, 0);
        root[0] -> lson = root[0] -> rson = root[0];
    };
	
	inline Node *NewNode(Node *a, Node *b, int k)
	{
		static Node pool[N*90], *tail = pool;
		tail -> lson = a, tail -> rson = b, tail -> sum = k;
		return tail ++;
	}

	Node *Insert(Node *p, int l, int r, int k, int x = 1)
	{
        if(p == NULL) p = NewNode(root[0], root[0], 0);
		Node *a = NewNode(p -> lson, p -> rson, p -> sum + x);
		int mid = (l + r) >> 1;
		if(l != r)
		{
			if(k <= mid)
				a -> lson = Insert(p -> lson, l, mid, k, x);
			else
				a -> rson = Insert(p -> rson, mid + 1, r, k, x);
		}
		return a;
	}
} seg1, seg2;

int pre[N][K], dep[N], L[N], R[N];
int n, n_, m, tik, Q, h[N], w[N], w_[N];

void DFS(int u, int p)
{
	L[u] = ++ tik;
	dep[u] = dep[p] + 1, pre[u][0] = p;
	seg1.root[u] = seg1.Insert(seg1.root[p], 1, n, w[u]);
	for(int i = 1; i < K; i ++)
		pre[u][i] = pre[pre[u][i-1]][i-1];
	for(int i = head[u]; i; i = e[i].next)
		if(e[i].v != p)
			DFS(e[i].v, u);
	R[u] = tik;
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

inline int lowbit(int x) {return x & (-x);}

inline void Modify(int p, int k, int x)
{
	for(; p <= n_; p += lowbit(p))
        seg2.root[p] = seg2.Insert(seg2.root[p], 1, n, k, x);
	return ;
}

int cnt1, cnt2;
Node *A[N], *B[N];

inline void Push(int p, int a)
{
    if(a == 0)
    {
        if(seg1.root[p] != seg1.root[0])
            A[++cnt1] = seg1.root[p];
        for(p = L[p]; p; p -= lowbit(p))
            if(seg2.root[p]) A[++cnt1] = seg2.root[p];
    }
    else
    {
        if(seg1.root[p] != seg1.root[0])
            B[++cnt2] = seg1.root[p];
        for(p = L[p]; p; p -= lowbit(p))
            if(seg2.root[p]) B[++cnt2] = seg2.root[p];
    }
    return ;
}

inline int Query(int k, int l, int r)
{
    while(l < r)
    {
        int mid = (l + r) >> 1, sum = 0;
        for(int i = 1; i <= cnt1; i ++)
            sum += A[i] -> rson -> sum;
        for(int i = 1; i <= cnt2; i ++)
            sum -= B[i] -> rson -> sum;
        if(sum >= k)
        {
            for(int i = 1; i <= cnt1; i ++)
                A[i] = A[i] -> rson;
            for(int i = 1; i <= cnt2; i ++)
                B[i] = B[i] -> rson;
            l = mid + 1;
        }
        else
        {
            for(int i = 1; i <= cnt1; i ++)
                A[i] = A[i] -> lson;
            for(int i = 1; i <= cnt2; i ++)
                B[i] = B[i] -> lson;
            r = mid, k -= sum;
        }
    }
    return l;
}

int main(int argc, char **argv)
{
	n_ = in(), Q = in();
	for(int i = 1; i <= n_; i ++)
		dic[++m] = (ItemD) {in(), i};
	for(int i = 1; i < n_; i ++)
	{
		int u = in(), v = in();
		AddEdge(u, v), AddEdge(v, u);
	}
	for(int i = 1; i <= Q; i ++)
	{
		q[i].k = in(), q[i].u = in(), q[i].v = in();
		if(q[i].k == 0)
			dic[++m] = (ItemD) {q[i].v, i + n_};
	}
	sort(dic + 1, dic + m + 1);
	for(int i = 1; i <= m; i ++)
	{
		if(dic[i].x != dic[i-1].x)
			h[++n] = dic[i].x;
		if(dic[i].p <= n_)
			w[dic[i].p] = n;
        else
            w_[dic[i].p-n_] = n;
	}
	DFS(1, 0);
	for(int i = 1; i <= Q; i ++)
	{
		int u = q[i].u, v = q[i].v;
		if(q[i].k == 0)
		{
			Modify(L[u], w[u], -1), Modify(R[u] + 1, w[u], 1);
			w[u] = w_[i];
			Modify(L[u], w[u], 1), Modify(R[u] + 1, w[u], -1);
		}
		else
		{
			int p = LCA(u, v);
			if(dep[u] + dep[v] - (dep[p] << 1) + 1 < q[i].k)
			{
				puts("invalid request!");
				continue ;
			}
            cnt1 = cnt2 = 0;
            Push(u, 0), Push(v, 0), Push(p, 1), Push(pre[p][0], 1);
            int t = Query(q[i].k, 1, n);
            printf("%d\n", h[t]);
		}
	}
	return 0;
}
