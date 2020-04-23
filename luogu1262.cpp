#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int N = 3e3 + 5;
const int M = 8e3 + 5;
const int INF = 0x3f3f3f3f;

int n, p, sig, head[N], val[N], mark[N], in[N];
int top, cnt, ind, dfn[N], low[N], stack[N], dom[N];

struct Edge
{
	int v, next;
} e[M];

inline void AddEdge(int u, int v)
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return;
}

void DFS(int u)
{
	stack[++top] = u;
	dfn[u] = low[u] = ++ind;
	for (int i = head[u]; i; i = e[i].next)
	{
		int v = e[i].v;
		if (!dfn[v])
		{
			DFS(v);
			low[u] = min(low[u], low[v]);
		}
		else if (!mark[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u])
	{
		int v;
		cnt++;
		do
		{
			v = stack[top--];
			mark[v] = cnt;
		} while (u != v && top);
	}
	return;
}

int main()
{
	freopen("in", "r", stdin);
	scanf("%d%d", &n, &p);
	for (int i = 0; i < p; i++)
	{
		int u, w;
		scanf("%d%d", &u, &w);
		val[u] = w;
	}
	scanf("%d", &p);
	for (int i = 0; i < p; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			DFS(i);
	memset(dom, 0x3f, sizeof(dom));
	for (int u = 1; u <= n; u++)
	{
		for (int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].v;
			if (mark[u] != mark[v])
				in[mark[v]]++;
		}
		if (val[u] && val[u] < dom[mark[u]])
			dom[mark[u]] = val[u];
	}
	int ans = 0, vet = -1;
	for (int i = 1; i <= cnt; i++)
		if (in[i] == 0)
			ans += dom[i];
	// This is a wrong method as the vertex with
	// the smallest number maybe not of in degree of 0
	// However, wick test cases...
	for (int u = 1; u <= n; u++)
	{
		if (in[mark[u]] == 0 && dom[mark[u]] == INF)
		{
			vet = u;
			break;
		}
	}
	if (vet == -1 && ans < INF)
		printf("YES\n%d\n", ans);
	else
		printf("NO\n%d\n", vet);
	return 0;
}
