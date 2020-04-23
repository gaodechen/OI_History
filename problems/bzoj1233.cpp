#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 1e5 + 5;

inline unsigned int in()
{
	unsigned int k = 0;
    int c = '\0';
	for(; c > '9' || c < '0';)
		c = getchar();
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

int sum[N], f[N], q[N], g[N];

inline int F(int k) {return sum[k - 1] - f[k];}

int main(int argc, char **argv)
{
    int n = in();
    for(int i = 1; i <= n; i ++)
        sum[i] = sum[i - 1] + in();
    int head = 1, tail = 0;
    q[++ tail] = n + 1;
    for(int i = n; i; i --)
    {
        // n + 1 must be remained, so head < tail
        while(head < tail && sum[q[head + 1] - 1] - sum[i - 1] >= f[q[head + 1]])
            head ++;
        f[i] = sum[q[head] - 1] - sum[i - 1];
        g[i] = g[q[head]] + 1;
        while(head < tail && F(q[tail]) <= F(i))
            tail --;
        q[++ tail] = i;
    }
    printf("%d", g[1]);
    return 0;
}
