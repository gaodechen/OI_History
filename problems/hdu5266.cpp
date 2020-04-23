#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

#define MID(l, r) (l + r) >> 1
#define lSon(p) p + p
#define rSon(p) p + p + 1

using namespace std;
const int N = 3e5 + 5, K = 20;

vector<int> e[N];
int n, q, pre[N][K], dep[N], node[4 * N];

void BFS(int root)
{
	queue<int> q;
	q.push(root);
	dep[root] = 0;
	pre[root][0] = root;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = 1; i < K; i++)
			pre[u][i] = pre[pre[u][i - 1]][i - 1];
		for (int i = 0; i < (int)e[u].size(); i++)
		{
			int &v = e[u][i];
			if (v == pre[u][0])
				continue;
			pre[v][0] = u;
			dep[v] = dep[u] + 1;
			q.push(v);
		}
	}
	return;
}

int LCA(int a, int b)
{
	if (dep[a] > dep[b])
		swap(a, b);
	int del = dep[b] - dep[a];
	for (int i = 0; del; del >>= 1, i++)
		if (del & 1)
			b = pre[b][i];
	if (a == b)
		return a;
	for (int i = K - 1; i >= 0; i--)
	{
		if (pre[a][i] == pre[b][i])
			continue;
		a = pre[a][i];
		b = pre[b][i];
	}
	return pre[a][0];
}

void BuildTree(int l, int r, int p)
{
	if (l == r)
		node[p] = l;
	else
	{
		int mid = MID(l, r), ls = lSon(p), rs = rSon(p);
		BuildTree(l, mid, ls);
		BuildTree(mid + 1, r, rs);
		node[p] = LCA(node[ls], node[rs]);
	}
	return;
}

int L, R;
int Query(int l, int r, int p)
{
	if (l >= L && r <= R)
		return node[p];
	int res, mid = MID(l, r);
	if (R <= mid)
		res = Query(l, mid, lSon(p));
	else if (L > mid)
		res = Query(mid + 1, r, rSon(p));
	else
		res = LCA(Query(l, mid, lSon(p)), Query(mid + 1, r, rSon(p)));
	return res;
}

int main()
{
	while (scanf("%d", &n) == 1)
	{
		for (int i = 1; i <= n; i++)
			e[i].clear();
		for (int i = 1; i < n; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		BFS(1);
		BuildTree(1, n, 1);
		scanf("%d", &q);
		for (int i = 1; i <= q; i++)
		{
			scanf("%d%d", &L, &R);
			printf("%d\n", Query(1, n, 1));
		}
	}
	return 0;
}
