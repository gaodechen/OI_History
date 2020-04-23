#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e6 + 5;
typedef	long long 	data;

data w[N], f[N];
int n, a, b, c, q[N], head, tail;

inline double slope(int j, int k)
{
    return (double) (f[j] - f[k] + b * (w[k] - w[j]) + a * (w[j] * w[j] - w[k] * w[k])) / (double) (2 * a * (w[j] - w[k]));
}

int main()
{
	scanf("%d%d%d%d", &n, &a, &b, &c);
	for(int i = 1; i <= n; i ++)
		scanf("%lld", &w[i]);
    for(int i = 1; i <= n; i ++)
        w[i] += w[i-1];
	for(int i = 1; i <= n; i ++)
	{
		while(head < tail && slope(q[head+1], q[head]) <= w[i])
			head ++;
        int h = q[head];
        data t = w[i] - w[h];
        f[i] = f[h] + a * t * t + b * t + c;
		while(head < tail && slope(i, q[tail]) <= slope(q[tail], q[tail-1]))
			tail --;
		q[++tail] = i;
	}
    printf("%lld", f[n]);
	return 0;
}
