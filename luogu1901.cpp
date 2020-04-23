#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 1000005;

inline int in()
{
	int k = 0, c = '\0';
	for(; c > '9' || c < '0';)
		c = getchar();
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

int n, h[N], v[N], q[N], f[N];

int main(int argc, char **argv)
{
    n = in();
    for(int i = 1; i <= n; i ++)
        h[i] = in(), v[i] = in();
    int top = 0;
    for(int i = 1; i <= n; i ++)
    {
        while(top && h[q[top]] < h[i])
            f[i] += v[q[top]], top --;
        f[q[top]] += v[i];
        q[++ top] = i;
    }
    int ans = 0;
    for(int i = 1; i <= n; i ++)
        ans = max(f[i], ans);
    printf("%d\n", ans);
    return 0;
}

