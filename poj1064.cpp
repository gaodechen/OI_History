#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
const int N = 1e4 + 5;

int n, k, max_, len[N];

inline bool Check(int l)
{
	int res = 0;
	for (int i = 1; i <= n; i++)
		res += len[i] / l;
	return res >= k;
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
	{
		double tmp;
		scanf("%lf", &tmp);
		len[i] = tmp * 100;
		max_ = max(max_, len[i]);
	}
	int l = 0, r = max_;
	while (l < r)
	{
		int mid = (l + r + 1) / 2;
		if (Check(mid))
			l = mid;
		else
			r = mid - 1;
	}
	printf("%.2lf\n", (double)l / 100.0);
	return 0;
}
