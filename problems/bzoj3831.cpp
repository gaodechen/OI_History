#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 1e6 + 5;

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

int a[N], f[N], q[N];

inline bool cmp(int h1, int f1, int h2, int f2)
{
    return f1 == f2 ? h1 >= h2 : f1 < f2;
}

int main()
{
    int n = in();
    for(int i = 1; i <= n; i ++)
        a[i] = in();
    int m = in();
    while(m --)
    {
        int k = in(), head, tail;
        f[1] = 0, q[head=tail=0] = 1;
        for(int i = 2; i <= n; i ++)
        {
            while(head < tail && q[head] < i - k)
                head ++;
            f[i] = f[q[head]] + (a[q[head]] <= a[i]);
            while(head < tail && cmp(a[i], f[i], a[q[tail]], f[q[tail]]))
                tail --;
            q[++tail] = i;
        }
        printf("%d\n", f[n]);
    }
    return 0;
}
