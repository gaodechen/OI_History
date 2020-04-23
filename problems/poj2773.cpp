#include <cstdio>
#include <iostream>

using namespace std;
const int N = 8e4, M = 1e6 + 5, K = 1e9;

int m, k, tot, tot_, mark[M], prime[N], a[20];

void InitTable()
{
	for (int i = 2; i <= N; i++)
	{
		if (!mark[i])
			prime[tot++] = i;
		for (int j = 0; j < tot; j++)
		{
			if (i * prime[j] > N)
				break;
			mark[i * prime[j]] = 1;
			if (i % prime[j] == 0)
				break;
		}
	}
	return;
}

void GetFactors(int n)
{
	tot_ = 0;
	for (int i = 0; i < tot && prime[i] * prime[i] <= n; i++)
	{
		if (n % prime[i] == 0)
		{
			a[tot_++] = prime[i];
			while (n % prime[i] == 0)
				n /= prime[i];
		}
	}
	if (n > 1)
		a[tot_++] = n;
	return;
}

int f(int n)
{
	int sum = 0;
	for (int i = 1; i < (1 << tot_); i++)
	{
		int t = 1, q = 0;
		for (int j = 0; j < tot_; j++)
			if ((1 << j) & i)
				q++, t *= a[j];
		if (q & 1)
			sum += n / t;
		else
			sum -= n / t;
	}
	return n - sum;
}

int main()
{
	InitTable();
	while (scanf("%d%d", &m, &k) == 2)
	{
		GetFactors(m);
		int l = 1, r = K;
		while (l < r)
		{
			int mid = (l + r) >> 1;
			if (f(mid) < k)
				l = mid + 1;
			else
				r = mid;
		}
		printf("%d\n", l);
	}
	return 0;
}
