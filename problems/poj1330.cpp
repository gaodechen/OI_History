#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
const int N = 1e4 + 3;

vector<int> e[N];
int T, n, a, b, mark, father[N], anc[N], vis[N], in[N];

inline int Find(int x)
{
	if (x != father[x])
		x = Find(father[x]);
	return father[x];
}

inline void Union(int x, int y)
{
	father[Find(y)] = Find(x);
	return;
}

void LCA(int u)
{
	anc[u] = u;
	for (int i = 0; i < (int)e[u].size(); i++)
	{
		int &v = e[u][i];
		if (!vis[v])
		{
			LCA(v);
			Union(u, v);
			anc[Find(u)] = u;
		}
	}
	vis[u] = 1;
	if (b == u && vis[a])
		printf("%d\n", anc[Find(a)]);
	else if (a == u && vis[b])
		printf("%d\n", anc[Find(b)]);
	return;
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		mark = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			e[i].clear();
			father[i] = i;
			in[i] = vis[i] = 0;
		}
		for (int i = 1; i < n; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			in[v]++;
		}
		scanf("%d%d", &a, &b);
		for (int i = 1; i <= n; i++)
		{
			if (!in[i])
			{
				LCA(i);
				continue;
			}
		}
	}
	return 0;
}
