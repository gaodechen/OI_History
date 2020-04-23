#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

#define set(p, k) memset(p, k, sizeof(p))

using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 2e4 + 5, M = 2e5 + 5;

struct Edge
{
	int v, w, next;
} e[M];

struct Status
{
	int u, d;

	Status(int u = 1, int d = 0) : u(u), d(d)
	{
	}

	bool operator<(const Status &b) const
	{
		return d > b.d;
	}
};

priority_queue<Status> q;
int n, m, sig, head[N], d[N][2];

void AddEdge(int u, int v, int w)
{
	e[++sig].v = v, e[sig].w = w;
	e[sig].next = head[u], head[u] = sig;
	return;
}

int Compute()
{
	d[1][0] = 0;
	q.push(Status());
	while (!q.empty())
	{
		Status t = q.top();
		q.pop();
		int u = t.u, x = t.d;
		// Mark
		if (d[u][1] < x)
			continue;
		for (int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].v, w = e[i].w + x;
			if (d[v][0] > w)
			{
				swap(d[v][0], w);
				q.push(Status(v, d[v][0]));
			}
			if (d[v][1] > w && d[v][0] < w)
			{
				d[v][1] = w;
				q.push(Status(v, w));
			}
		}
	}
	return d[n][1];
}

int main()
{
	set(d, INF);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		AddEdge(u, v, w);
	}
	int res = Compute();
	if (res == INF)
		printf("-1\n");
	else
		printf("%d\n", res);
	return 0;
}
