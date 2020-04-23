#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int N = 110, INF = 0xfffffff;

int map[N][N], dis[N][N], pre[N][N], path[N], n, m;

int main()
{
	while (scanf("%d%d", &n, &m) == 2)
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				pre[i][j] = i, map[i][j] = INF;
		while (m--)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			if (w < map[u][v])
				map[u][v] = map[v][u] = w;
		}
		memcpy(dis, map, sizeof(map));
		int res = INF, cnt = 0, p;
		for (int k = 1; k <= n; k++)
		{
			for (int i = 1; i < k; i++)
			{
				for (int j = 1; j < i; j++)
				{
					int t = dis[i][j] + map[k][i] + map[k][j];
					if (t < res)
					{
						res = t, cnt = 0, p = j;
						while (p != i)
						{
							path[cnt++] = p;
							p = pre[i][p];
						}
						path[cnt++] = i;
						path[cnt++] = k;
					}
				}
			}
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					if (dis[i][j] > dis[i][k] + dis[k][j])
					{
						dis[i][j] = dis[i][k] + dis[k][j];
						pre[i][j] = pre[k][j];
					}
				}
			}
		}
		if (res == INF)
			printf("No solution.\n");
		else
		{
			printf("%d", path[0]);
			for (int i = 1; i < cnt; i++)
				printf(" %d", path[i]);
			printf("\n");
		}
	}
	return 0;
}
