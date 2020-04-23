#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;
const int N = 1e3 + 5;

int t, n, b, max_, num[N];
map<string, int> table;

struct Item
{
	int p, v;
	bool operator<(const Item &b) const
	{
		return v > b.v;
	}
} e[N][N];

int GetIndex(string s)
{
	if (!table.count(s))
		table[s] = (int)table.size();
	return (int)table.size();
}

bool Check(int k)
{
	int sum = 0;
	for (int i = 1; i <= (int)table.size(); i++)
	{
		int min_ = 0x3f3f3f3f;
		for (int j = 1; j <= num[i]; j++)
		{
			if (e[i][j].v >= k)
				min_ = min(e[i][j].p, min_);
			else
				break;
		}
		sum += min_;
		if (sum > b)
			return false;
	}
	return true;
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		table.clear();
		memset(num, 0, sizeof(num));
		scanf("%d%d", &n, &b);
		for (int i = 1; i <= n; i++)
		{
			char kind[50], name[50];
			scanf("%s%s", kind, name);
			int t = GetIndex(kind);
			num[t]++;
			scanf("%d%d", &e[t][num[t]].p, &e[t][num[t]].v);
			max_ = max(max_, e[t][i].v);
		}
		for (int i = 1; i <= (int)table.size(); i++)
			sort(e[i] + 1, e[i] + num[i] + 1);
		int l = 0, r = max_;
		while (l < r)
		{
			int mid = (l + r + 1) >> 1;
			if (Check(mid))
				l = mid;
			else
				r = mid - 1;
		}
		printf("%d\n", l);
	}
	return 0;
}
