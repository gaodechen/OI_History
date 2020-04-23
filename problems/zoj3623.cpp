#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int T = 1000, K = 35;

int N, L, t[K], l[K], d[T];

int main()
{
	freopen("in", "r", stdin);
	while (scanf("%d%d", &N, &L) == 2)
	{
		memset(d, 0, sizeof(d));
		for (int i = 1; i <= N; i++)
			scanf("%d%d", &t[i], &l[i]);
		// See the time forwards!
		for (int i = 1; i <= N; i++)
			for (int j = 0; j + t[i] < T; j++)
				d[j + t[i]] = max(d[j + t[i]], d[j] + j * l[i]);
		for (int i = 0; i < T; i++)
		{
			if (d[i] >= L)
			{
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}
