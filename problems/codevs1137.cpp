#include <cstdio>
#include <iostream>

using namespace std;
const int N = 1e3 + 5, M = 10007;

int QuickPow(int a, int k)
{
	a %= M;
	int res = 1;
	while (k)
	{
		if (k & 1)
			res = res * a % M;
		a = a * a % M;
		k >>= 1;
	}
	return res;
}

int main()
{
	int q[N][N], a, b, k, n, m;
	scanf("%d%d%d%d%d", &a, &b, &k, &n, &m);
	// q[0] = 1;
	// for( int i = 1; i <= n; i ++ )
	// 	q[i] = q[i-1] * ( k - i + 1 ) / i;
	// printf( "%d\n", q[n] );
	q[1][0] = q[1][1] = 1;
	for (int i = 2; i <= k; i++)
	{
		q[i][0] = 1;
		for (int j = 1; j <= i; j++)
			q[i][j] = (q[i - 1][j - 1] + q[i - 1][j]) % M;
	}
	q[1][1] = 0;
	printf("%d\n", q[k][m] * QuickPow(a, n) % M * QuickPow(b, m) % M);
	return 0;
}
