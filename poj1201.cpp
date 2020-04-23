#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;
const int N = 5e4 + 3;
const int INF = 0x7fffffff;

int dis[N], vis[N];
int n, l, r, tick, head[N];

struct Edge
{
	int v, w, next;
} e[N * 3];

void AddEdge(int u, int v, int w)
{
	e[++tick].v = v, e[tick].w = w;
	e[tick].next = head[u], head[u] = tick;
	return;
}

void SPFA(int s)
{
	queue<int> q;
	q.push(s);
	memset(vis, 0, sizeof(vis));
	memset(dis, 128, sizeof(dis));
	vis[s] = 1, dis[s] = 0;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for (int i = head[u]; i; i = e[i].next)
		{
			int &v = e[i].v;
			if (dis[v] < dis[u] + e[i].w)
			{
				dis[v] = dis[u] + e[i].w;
				if (!vis[v])
				{
					q.push(v);
					vis[v] = 1;
				}
			}
		}
	}
	return;
}

int main()
{
	while (scanf("%d", &n) != EOF)
	{
		tick = 0, l = INF, r = -INF;
		memset(head, 0, sizeof(head));
		for (int i = 1; i <= n; i++)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			l = min(l, (++a) - 1);
			r = max(r, ++b);
			AddEdge(a - 1, b, c);
		}
		for (int i = l; i <= r; i++)
		{
			AddEdge(i, i - 1, -1);
			AddEdge(i - 1, i, 0);
		}
		SPFA(l);
		printf("%d\n", dis[r]);
	}
	return 0;
}
