#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int N = 1e5 + 5;

int pre[N], flag, tick, u, v;

void Init(int a)
{
	if (!pre[a])
		pre[a] = a, tick++;
	return;
}

int Find(int a)
{
	if (a != pre[a])
		pre[a] = Find(pre[a]);
	return pre[a];
}

void Union(int a, int b)
{
	pre[Find(b)] = Find(a);
	return;
}

int main()
{
	while (1)
	{
		flag = 1, tick = 0;
		memset(pre, 0, sizeof(pre));
		while (scanf("%d%d", &u, &v) == 2)
		{
			if ((u == 0 && v == 0) || u == -1)
				break;
			Init(u), Init(v);
			if (Find(u) == Find(v))
				flag = 0;
			Union(u, v);
		}
		if (u == -1)
			break;
		int tmp = -1;
		for (int i = 1, j = 1; j <= tick; i++)
		{
			if (pre[i])
			{
				j++;
				Find(i);
				if (tmp == -1)
					tmp = pre[i];
				if (pre[i] != tmp)
				{
					flag = 0;
					break;
				}
			}
		}
		printf("%s\n", flag ? "Yes" : "No");
	}
	return 0;
}
